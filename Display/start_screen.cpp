#include "start_screen.h"


StartScreen::StartScreen(int width, int height)
    : selectedIndex(0), screenWidth(width), screenHeight(height) {
    menuItems = {"START GAME", "CONTROLS", "HIGH SCORE", "EXIT"};
}

void StartScreen::update() {
    if (IsKeyPressed(KEY_DOWN)) {
        selectedIndex = (selectedIndex + 1) % menuItems.size();
    } else if (IsKeyPressed(KEY_UP)) {
        selectedIndex = static_cast<int>((selectedIndex - 1 + menuItems.size()) % menuItems.size());
    }
}

bool StartScreen::isOptionSelected() const {
    return IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER);
}

int StartScreen::getSelection() const {
    return selectedIndex;
}

void StartScreen::draw() const {
    ClearBackground(BLACK);

    int winWidth = GetScreenWidth();
    int winHeight = GetScreenHeight();

    // --- Skalierungsfaktoren ---
    int baseUnit = std::min(winWidth, winHeight) / 22;
    int titleSize = static_cast<int>(baseUnit * 1.2);
    int menuFontSize = static_cast<int>(baseUnit * 0.9);
    int pacmanRadius = baseUnit;
    int ghostSize = baseUnit;
    int ghostSpacing = static_cast<int>(baseUnit * 0.5f);

    // --- Gesamthöhe für Zentrierung ---
    int totalContentHeight = static_cast<int>(titleSize + baseUnit * 1.2 + pacmanRadius + baseUnit * 1.0 +
                             (menuFontSize + baseUnit / 4) * static_cast<int>(menuItems.size()));
    int contentStartY = (winHeight - totalContentHeight) / 2;

    // --- Titel ---
    const char* title = "PAC-MAN: ESCAPE THE MAZE";
    int titleX = winWidth / 2 - MeasureText(title, titleSize) / 2;
    int titleY = contentStartY;
    DrawText(title, titleX, titleY, titleSize, YELLOW);

    // --- Pac-Man + Geister gemeinsam zentrieren ---
    float groupWidth = static_cast<float>(pacmanRadius * 2 + ghostSpacing + (ghostSize + ghostSpacing) * 4 - ghostSpacing);
    int groupStartX = static_cast<int>(winWidth / 2 - groupWidth / 2.0f);
    int pacmanX = groupStartX + pacmanRadius;
    int pacmanY = static_cast<int>(titleY + titleSize + baseUnit * 1.2);

    // Pac-Man
    DrawCircleSector(
        Vector2{static_cast<float>(pacmanX), static_cast<float>(pacmanY)},
        static_cast<float>(pacmanRadius),
        30.0f, 330.0f, 32, YELLOW);

    // Geister
    Color ghostColors[4] = { RED, PINK, SKYBLUE, ORANGE };
    int ghostStartX = pacmanX + pacmanRadius + ghostSpacing;
    for (int i = 0; i < 4; i++) {
        int gx = ghostStartX + i * (ghostSize + ghostSpacing);
        int gy = pacmanY;

        DrawRectangle(gx - ghostSize / 2, gy - ghostSize / 4, ghostSize, ghostSize * 3 / 4, ghostColors[i]);
        DrawCircle(gx, gy - ghostSize / 4, ghostSize / 2, ghostColors[i]);

        int eyeOffsetX = ghostSize / 5;
        int eyeOffsetY = ghostSize / 3;
        int eyeRadius = ghostSize / 6;
        int pupilRadius = ghostSize / 12;
        DrawCircle(gx - eyeOffsetX, gy - eyeOffsetY, eyeRadius, WHITE);
        DrawCircle(gx + eyeOffsetX, gy - eyeOffsetY, eyeRadius, WHITE);
        DrawCircle(gx - eyeOffsetX, gy - eyeOffsetY, pupilRadius, BLUE);
        DrawCircle(gx + eyeOffsetX, gy - eyeOffsetY, pupilRadius, BLUE);
    }

    // --- Menü ---
    int menuStartY = static_cast<int>(pacmanY + pacmanRadius + baseUnit * 1.0f);
    for (int i = 0; i < static_cast<int>(menuItems.size()); ++i) {
        Color color = (i == selectedIndex) ? GOLD : LIGHTGRAY;
        int textWidth = MeasureText(menuItems[i].c_str(), menuFontSize);
        int x = winWidth / 2 - textWidth / 2;
        int y = menuStartY + i * (menuFontSize + baseUnit / 4);

        DrawText(menuItems[i].c_str(), x, y, menuFontSize, color);

        if (i == selectedIndex) {
            DrawCircle(
                static_cast<int>(x - menuFontSize),
                static_cast<int>(y + menuFontSize / 2),
                static_cast<float>(baseUnit / 2.5f),
                GOLD
            );
        }
    }

    // --- Hinweistext ---
    int hintFontSize = static_cast<int>(baseUnit * 0.6f);
    const char* hint = "Use UP/DOWN keys - ENTER to select";
    int hintWidth = MeasureText(hint, hintFontSize);
    DrawText(
        hint,
        static_cast<int>(winWidth / 2 - hintWidth / 2),
        static_cast<int>(winHeight - baseUnit * 1.0f),
        hintFontSize,
        DARKGRAY
    );
}

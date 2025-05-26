#include "start.h"
#include "raylib.h"
#include "config.h"

StartScreen::StartScreen(int width, int height)
    : selectedIndex(0), screenWidth(width), screenHeight(height) {
    menuItems = {"START GAME", "CONTROLS", "HIGH SCORE", "EXIT"};
}

void StartScreen::update() {
    if (IsKeyPressed(KEY_DOWN)) {
        selectedIndex = (selectedIndex + 1) % menuItems.size();
    } else if (IsKeyPressed(KEY_UP)) {
        selectedIndex = (selectedIndex - 1 + menuItems.size()) % menuItems.size();
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

    // Title
    const char* title = "PAC-MAN: ESCAPE THE MAZE";
    int titleSize = 30;
    int titleX = screenWidth / 2 - MeasureText(title, titleSize) / 2;
    DrawText(title, titleX, 50, titleSize, YELLOW);

    // Pac-Man-Kopf (Sektor)
    int pacmanX = 105;
    int pacmanY = 150;
    DrawCircleSector((Vector2){(float)pacmanX, (float)pacmanY}, 40, 30, 330, 0, YELLOW);

    // Geister: rot, pink, cyan, orange
    Color ghostColors[4] = { RED, PINK, SKYBLUE, ORANGE };
    int ghostOffsets[4] = { 0, 60, 120, 180 };
    for (int i = 0; i < 4; i++) {
        int gx = 182 + ghostOffsets[i];
        int gy = 150;

        // Rechteckkörper + Halbkreis-Kopf
        DrawRectangle(gx - 20, gy - 10, 40, 30, ghostColors[i]);
        DrawCircle(gx, gy - 10, 20, ghostColors[i]);

        // Augen
        DrawCircle(gx - 7, gy - 15, 5, WHITE);
        DrawCircle(gx + 7, gy - 15, 5, WHITE);
        DrawCircle(gx - 7, gy - 15, 2, BLUE);
        DrawCircle(gx + 7, gy - 15, 2, BLUE);
    }

    // Menüoptionen
    int menuStartY = 220;
    for (int i = 0; i < menuItems.size(); ++i) {
        Color color = (i == selectedIndex) ? GOLD : LIGHTGRAY;
        int fontSize = 30;
        int textWidth = MeasureText(menuItems[i].c_str(), fontSize);
        int x = screenWidth / 2 - textWidth / 2;
        int y = menuStartY + i * 50;

        DrawText(menuItems[i].c_str(), x, y, fontSize, color);

        if (i == selectedIndex) {
            DrawCircle(x - 20, y + fontSize / 2, 6, GOLD);
        }
    }

    // Hinweistext
    DrawText("Use UP/DOWN keys - ENTER to select", screenWidth / 2 - 180, screenHeight - 60, 20, DARKGRAY);
}

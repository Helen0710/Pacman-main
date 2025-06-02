#include "start_screen.h"
#include "raylib.h"
#include "../Board/config.h"

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

    int winWidth = GetScreenWidth();
    int winHeight = GetScreenHeight();

    // Title
    const char* title = "PAC-MAN: ESCAPE THE MAZE";
    int titleSize = CELL_SIZE * 0.75;
    int titleX = winWidth / 2 - MeasureText(title, titleSize) / 2;
    DrawText(title, titleX, winHeight / 12, titleSize, YELLOW);

    // Pac-Man head (centered horizontally)
    int pacmanY = winHeight / 4;
    float pacmanRadius = CELL_SIZE * 1.2f;
    int pacmanX = winWidth / 2 - (CELL_SIZE * 3); // Adjust as needed
    DrawCircleSector(Vector2{(float)pacmanX, (float)pacmanY}, pacmanRadius, 30.0f, 330.0f, 32, YELLOW);

    // Ghosts (centered horizontally)
    Color ghostColors[4] = { RED, PINK, SKYBLUE, ORANGE };
    int ghostSpacing = CELL_SIZE * 2;
    int ghostsStartX = winWidth / 2 - (ghostSpacing * 1.5);
    int ghostsY = pacmanY;
    for (int i = 0; i < 4; i++) {
        int gx = ghostsStartX + i * ghostSpacing;
        int gy = ghostsY;
        DrawRectangle(gx - CELL_SIZE / 2, gy - CELL_SIZE / 4, CELL_SIZE, CELL_SIZE * 3 / 4, ghostColors[i]);
        DrawCircle(gx, gy - CELL_SIZE / 4, CELL_SIZE / 2, ghostColors[i]);
        int eyeOffsetX = CELL_SIZE / 5;
        int eyeOffsetY = CELL_SIZE / 3;
        int eyeRadius = CELL_SIZE / 6;
        int pupilRadius = CELL_SIZE / 12;
        DrawCircle(gx - eyeOffsetX, gy - eyeOffsetY, eyeRadius, WHITE);
        DrawCircle(gx + eyeOffsetX, gy - eyeOffsetY, eyeRadius, WHITE);
        DrawCircle(gx - eyeOffsetX, gy - eyeOffsetY, pupilRadius, BLUE);
        DrawCircle(gx + eyeOffsetX, gy - eyeOffsetY, pupilRadius, BLUE);
    }

    // Menu options (centered vertically)
    int menuStartY = winHeight / 2;
    for (int i = 0; i < menuItems.size(); ++i) {
        Color color = (i == selectedIndex) ? GOLD : LIGHTGRAY;
        int fontSize = CELL_SIZE;
        int textWidth = MeasureText(menuItems[i].c_str(), fontSize);
        int x = winWidth / 2 - textWidth / 2;
        int y = menuStartY + i * (CELL_SIZE + 10);

        DrawText(menuItems[i].c_str(), x, y, fontSize, color);

        if (i == selectedIndex) {
            DrawCircle(x - CELL_SIZE / 2, y + fontSize / 2, CELL_SIZE / 5, GOLD);
        }
    }

    // Hint text (bottom center)
    DrawText("Use UP/DOWN keys - ENTER to select",
             winWidth / 2 - CELL_SIZE * 3,
             winHeight - CELL_SIZE,
             CELL_SIZE / 2, DARKGRAY);
}



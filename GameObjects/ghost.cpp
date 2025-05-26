#include "ghost.h"
#include "../Board/board.h"
#include "../Controls/ghost_controller.h"
#include "../Board/config.h"
#include "../utils.h"

#include "raylib.h"

Ghost::Ghost(int startX, int startY, Controller* ctrl, Color color)
    : Figure(startX, startY, ctrl), ghostcolor(color) {}

bool Ghost::canMoveTo(const Board& board, int x, int y) const {
    // Check if the ghost can move to the specified position
    return board.isWalkableForGhost(x, y);
}

void Ghost::draw() const {
    int centerX = static_cast<int>(px + CELL_SIZE / 2);
    int centerY = static_cast<int>(py + CELL_SIZE / 2);
    int radius = CELL_SIZE / 2 - 2; // Adjust the radius to fit within the cell

    DrawCircle(centerX, centerY - 4, radius, ghostcolor);

    //Body
    DrawRectangle(centerX - radius, centerY - 4, radius * 2, radius, ghostcolor);

    //Waves
    int waveRadius = radius / 3;
    for (int i = -1; i <= 1; ++i) {
        DrawCircle(centerX + i * waveRadius * 2, centerY + radius - 2, waveRadius, ghostcolor);
    }

    //Eyes
    Color eyeWhite = RAYWHITE;
    Color eyeBlack = BLACK;

    int eyeOffsetX = radius / 2;
    int eyeOffsetY = radius / 3;
    int eyeRadius = radius / 3;

    //Left eye
    DrawCircle(centerX - eyeOffsetX, centerY - eyeOffsetY, eyeRadius, eyeWhite);
    DrawCircle(centerX - eyeOffsetX, centerY - eyeOffsetY, eyeRadius / 2, eyeBlack);

    //Right eye
    DrawCircle(centerX + eyeOffsetX, centerY - eyeOffsetY, eyeRadius, eyeWhite);
    DrawCircle(centerX + eyeOffsetX, centerY - eyeOffsetY, eyeRadius / 2, eyeBlack);
}
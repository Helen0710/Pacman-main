#include "pacman.h"
#include "raylib.h"
#include "../Board/config.h"
#include "../Board/board.h"
#include "../utils.h"

PacMan::PacMan(int startX, int startY, Controller* ctrl) : Figure(startX, startY, ctrl) {}

bool PacMan::canMoveTo(const Board& board, int x, int y) const {
    return board.isWalkableForPacman(x, y);
}


void PacMan::draw() const {
    // Calculate center
    int centerX = static_cast<int>(px + CELL_SIZE / 2);
    int centerY = static_cast<int>(py + CELL_SIZE / 2);
    float radius = CELL_SIZE / 2 - 2;

    // Determine mouth angle based on direction
    float startAngle = 30.0f;
    float endAngle = 330.0f;
    Direction currentDir = getCurrentDir();
    if (currentDir == Direction::DOWN) {
        startAngle = 120.0f;
        endAngle = 420.0f;
    } else if (currentDir == Direction::UP) {
        startAngle = 300.0f;
        endAngle = 600.0f;
    } else if (currentDir == Direction::LEFT) {
        startAngle = 210.0f;
        endAngle = 510.0f;
    } else if (currentDir == Direction::RIGHT) {
        startAngle = 30.0f;
        endAngle = 330.0f;
    }

    DrawCircleSector(
        { (float)centerX, (float)centerY },
        radius,
        startAngle,
        endAngle,
        32,
        YELLOW
    );
}
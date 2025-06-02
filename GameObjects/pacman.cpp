#include "pacman.h"
#include "raylib.h"
#include <iostream>


PacMan::PacMan(int startX, int startY, Controller* ctrl, float spd) : Figure(startX, startY, ctrl, spd) {}

bool PacMan::canMoveTo(const CheckPosition& checkPos, int x, int y) const {
    return checkPos.isWalkableForPacman(x, y);
}

void PacMan::update(const CheckPosition& checkPos) {
    
    Figure::update(checkPos); // Call the base class update method

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

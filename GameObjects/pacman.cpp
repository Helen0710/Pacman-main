#include "pacman.h"
#include "raylib.h"
#include <iostream>
#include <cmath>


PacMan::PacMan(int startX, int startY, Controller* ctrl, float spd) : Figure(startX, startY, ctrl, spd) {}

bool PacMan::canMoveTo(const CheckPosition& checkPos, int x, int y) const {
    return checkPos.isWalkableForPacman(x, y);
}


void PacMan::update(const CheckPosition& checkPos) {
    if (state == PacManState::Dying) {
        deathTimer += GetFrameTime();
        if (deathTimer > 1.0f) { // 1 second for the animation
            state = PacManState::Dead;
        }
        return; // Don't move while dying
    }
    if (state == PacManState::Alive) {
        Figure::update(checkPos);
    }
}

void PacMan::startDeathAnimation() {
    state = PacManState::Dying;
    deathTimer = 0.0f; // Reset death timer
    // Optionally, play a sound or trigger an animation here
}


void PacMan::draw() const {
    int centerX = static_cast<int>(px + CELL_SIZE / 2);
    int centerY = static_cast<int>(py + CELL_SIZE / 2) + TOP_MARGIN;
    float radius = CELL_SIZE / 2 - 2;

    if (state == PacManState::Dying) {
        // Animate mouth opening from 60° to 180°
        float progress = deathTimer / 3.0f; // 0 to 1
        float mouthOpen = 60.0f + 300.0f * progress; // 60° to 180°
        float startAngle = mouthOpen;
        float endAngle = 360.0f - mouthOpen;
        Direction currentDir = getCurrentDir();
        if (currentDir == Direction::DOWN) {
            startAngle += 90.0f;
            endAngle += 90.0f;
        } else if (currentDir == Direction::LEFT) {
            startAngle += 180.0f;
            endAngle += 180.0f;
        } else if (currentDir == Direction::UP) {
            startAngle += 270.0f;
            endAngle += 270.0f;
        }
        DrawCircleSector(
            { (float)centerX, (float)centerY },
            radius,
            startAngle,
            endAngle,
            32,
            YELLOW
        );
        return;
    }

    // Normal draw code for Alive state (as before)
    float time = GetTime(); // Raylib function, returns seconds since start
    float mouthOpen = 15.0f + 35.0f * std::fabs(std::sin(time * 8)); // 30° to 50°, speed adjustable

    float startAngle = mouthOpen;
    float endAngle = 360.0f - mouthOpen;

    Direction currentDir = getCurrentDir();
    if (currentDir == Direction::DOWN) {
        startAngle += 90.0f;
        endAngle += 90.0f;
    } else if (currentDir == Direction::LEFT) {
        startAngle += 180.0f;
        endAngle += 180.0f;
    } else if (currentDir == Direction::UP) {
        startAngle += 270.0f;
        endAngle += 270.0f;
    }
    // RIGHT is default (no rotation)

    DrawCircleSector(
        { (float)centerX, (float)centerY },
        radius,
        startAngle,
        endAngle,
        32,
        YELLOW
    );
}

void PacMan::resetForNewGame(int x, int y) {
    setPosition(x, y); // Reset to starting position
    state = PacManState::Alive;
    resetState();

    currentDir = Direction::NONE; // Reset direction to default
}
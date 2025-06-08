#include "ghost.h"
#include "raylib.h"

Ghost::Ghost(int startX, int startY, Controller* ctrl, Color color, float spd)
    : Figure(startX, startY, ctrl, spd), ghostcolor(color) {}

bool Ghost::canMoveTo(const CheckPosition& checkPos, int x, int y) const {
    char tile = checkPos.isWall(x, y) ? '#'  : checkPos.isWalkableForGhost(x, y) ? ' ' : '?';
    bool walkable = checkPos.isWalkableForGhost(x, y);
    //TraceLog(LOG_INFO, "Ghost check (%d,%d): tile='%c', walkable=%d", x, y, tile, walkable);
    return walkable;
}

void Ghost::update(const CheckPosition& checkPos) {
    
    Figure::update(checkPos); // Call the base class update method
}


void Ghost::draw() const {
    int centerX = static_cast<int>(px + CELL_SIZE / 2.0f);
    int centerY = static_cast<int>(py + CELL_SIZE / 2.0f) + TOP_MARGIN;
    int radius = CELL_SIZE / 2 - 2;

    // Draw ghost body rounded top + flat bottom
    DrawCircle(centerX, centerY - 4, radius, ghostcolor);

    DrawRectangle(centerX - radius, centerY - 4, radius * 2, radius, ghostcolor);

    // Draw wavy bottom feet as waves
    int numWaves = 3;
    int waveRadius = radius / numWaves;
    int baseY = centerY + radius - 4;
    for (int i = 0; i < numWaves; ++i) {
        int waveCenterX = centerX - radius + waveRadius + i * 2 * waveRadius;
        DrawCircle(waveCenterX, baseY, waveRadius, ghostcolor);
    }

    // Draw eyes white ovals
    int eyeOffsetX = radius / 2;
    int eyeOffsetY = radius / 3;
    int eyeRadiusX = radius / 3;
    int eyeRadiusY = radius / 2;
    DrawEllipse(
        static_cast<float>(centerX - eyeOffsetX),
        static_cast<float>(centerY - eyeOffsetY),
        static_cast<float>(eyeRadiusX),
        static_cast<float>(eyeRadiusY),
        WHITE
    );
    DrawEllipse(
        static_cast<float>(centerX + eyeOffsetX),
        static_cast<float>(centerY - eyeOffsetY),
        static_cast<float>(eyeRadiusX),
        static_cast<float>(eyeRadiusY),
        WHITE
    );

    // Draw pupils blue, in movement direction
    Direction dir = currentDir;
    int pupilOffsetX = 0, pupilOffsetY = 0;
    int pupilRadius = eyeRadiusX / 2;
    switch (dir.toEnum()) {
        case 0:    pupilOffsetY = -eyeRadiusY/2; break; // UP
        case 1:    pupilOffsetY = eyeRadiusY/2; break;  // DOWN
        case 2:    pupilOffsetX = -eyeRadiusX/2; break; // LEFT
        case 3:    pupilOffsetX = eyeRadiusX/2; break;  // RIGHT
        default: break;
    }
    DrawCircle(centerX - eyeOffsetX + pupilOffsetX, centerY - eyeOffsetY + pupilOffsetY, pupilRadius, BLUE);
    DrawCircle(centerX + eyeOffsetX + pupilOffsetX, centerY - eyeOffsetY + pupilOffsetY, pupilRadius, BLUE);
}

void Ghost::setSpeed(float newSpeed) {
    speed = newSpeed;
}

void Ghost::resetForNewGame(int x, int y) {
    setPosition(x, y);
    currentDir = Direction::NONE; // Reset direction to default
}

GhostController* Ghost::getController() {
    return static_cast<GhostController*>(controller);
}
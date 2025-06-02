#include "points.h"
#include "raylib.h"


Points::Points(const CheckPosition& checkPos) {
    points.resize(LEVEL_HEIGHT, std::vector<bool>(LEVEL_WIDTH, false));
    int count = 0;
    for (int y = 0; y < LEVEL_HEIGHT; ++y) {
        for (int x = 0; x < LEVEL_WIDTH; ++x) {
            if (checkPos.isWalkableForPacman(x,y)) {
                points[y][x] = true;
                count++;
            }
        }
    }
    //TraceLog(LOG_INFO, "Anzahl Punkte: %d", count);
}

void Points::draw() const {
    //TraceLog (LOG_INFO, "draw wurde aufgerufen");
    for (int y = 0; y < LEVEL_HEIGHT; ++y) {
        for (int x = 0; x < LEVEL_WIDTH; ++x) {
            if (points[y][x]) {  // Klein geschrieben, Zugriff auf Member
                DrawCircle(x * CELL_SIZE + CELL_SIZE / 2, y * CELL_SIZE + CELL_SIZE / 2, 3, YELLOW);
            }
        }
    }
}



bool Points::hasRemainingPoints() const {
    for (const auto& row : points) {
        for (bool hasPoint : row) {
            if (hasPoint) return true;
        }
    }
    return false;
}

bool Points::getPoint(int y, int x) const {
    return points[y][x];
}

void Points::setPoint(int y, int x, bool value) {
    points[y][x] = value; // Setze den Punkt auf false, wenn PacMan ihn einsammelt
}
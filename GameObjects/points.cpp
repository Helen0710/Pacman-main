#include "points.h"
#include "raylib.h"
#include "../Board/board.h"

Points::Points(const Board& board) {
    points.resize(LEVEL_HEIGHT, std::vector<bool>(LEVEL_WIDTH, false));
    int count = 0;
    for (int y = 0; y < LEVEL_HEIGHT; ++y) {
        for (int x = 0; x < LEVEL_WIDTH; ++x) {
            if (board.isWalkableForPacman(x,y)) {
                points[y][x] = true;
                count++;
            }
        }
    }
    TraceLog(LOG_INFO, "Anzahl Punkte: %d", count);
}

void Points::draw() const {
    //TraceLog (LOG_INFO, "draw wurde aufgerufen");
    for (int y = 0; y < LEVEL_HEIGHT; ++y) {
        for (int x = 0; x < LEVEL_WIDTH; ++x) {
            if (points[y][x]) {  // Klein geschrieben, Zugriff auf Member
                DrawCircle(x * CELL_SIZE + CELL_SIZE / 2, y * CELL_SIZE + CELL_SIZE / 2, 4, YELLOW);
            }
        }
    }
}

int Points::checkCollision(int y, int x) {
    if (y < 0 || y >= LEVEL_HEIGHT || x < 0 || x >= LEVEL_WIDTH)
        return 0;

    if (points[y][x]) {
        points[y][x] = false;
        return 10;  // Punktwert
    }
    TraceLog (LOG_INFO, "Punktestand %d", points);
    return 0;
}

bool Points::hasRemainingPoints() const {
    for (const auto& row : points) {
        for (bool hasPoint : row) {
            if (hasPoint) return true;
        }
    }
    return false;
}

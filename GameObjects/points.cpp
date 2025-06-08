#include "points.h"



// Constructor: initialize the grid of points
Points::Points(const CheckPosition& checkPos)
    : Item(0, 0, 10) // Dummy values, since Points manages a grid, not a single item
{
    int h = getLevelHeight();
    int w = getLevelWidth();
    points.resize(h, std::vector<bool>(w, false));
    int count = 0;
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            if (checkPos.isWalkableForPacman(x, y) && isPointAllowed(x, y)) {
                points[y][x] = true;
                count++;
            }
        }
    }
    //TraceLog(LOG_INFO, "Anzahl Punkte: %d", count);
}

void Points::draw() const {
    int h = getLevelHeight();
    int w = getLevelWidth();
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            if (points[y][x]) {
                DrawCircle(x * CELL_SIZE + CELL_SIZE / 2, y * CELL_SIZE + CELL_SIZE / 2 + TOP_MARGIN, 3, YELLOW);
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
    return points[wrapY(y)][wrapX(x)];
}

void Points::setPoint(int y, int x, bool value) {
    points[wrapY(y)][wrapX(x)] = value;
}

void Points::resetPoints(const CheckPosition& checkPos) {
    int h = getLevelHeight();
    int w = getLevelWidth();
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            if (checkPos.isWalkableForPacman(x, y) && isPointAllowed(x, y)) {
                points[y][x] = true;
            } else {
                points[y][x] = false;
            }
        }
    }
}

bool Points::isPointAllowed(int x, int y) const {
    // Keine Punkte in der gesamten Portal-Reihe (z.B. Zeile 12/13)
    if (y == 12 || y == 13) { // Passe ggf. an die tatsächliche Portal-Zeile an!
        return false;
    }
    return true;
}

int Points::wrapX(int x) const {
    int w = getLevelWidth();
    return (x + w) % w;
}
int Points::wrapY(int y) const {
    int h = getLevelHeight();
    return (y + h) % h;
}

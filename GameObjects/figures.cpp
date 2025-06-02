#include "figures.h"
#include <cmath>
#include <iostream>

Figure::Figure(int startX, int startY, Controller* ctrl, float spd)
    : gridX(startX),
      gridY(startY),
      px(static_cast<float>(startX) * CELL_SIZE),
      py(static_cast<float>(startY) * CELL_SIZE),
      speed(spd),
      currentDir(Direction::NONE),
      controller(ctrl) {}


bool Figure::nearCenterOfCell() const {
    return (static_cast<int>(px) % CELL_SIZE == 0) &&
           (static_cast<int>(py) % CELL_SIZE == 0);
}

/*
bool Figure::canMoveTo(const CheckPosition& checkPos, int x, int y) const {
    return checkPos.isWalkable(x, y);
}
*/

void Figure::update(const CheckPosition& checkPos) {

    if (nearCenterOfCell()) {
        Direction desiredDir = controller->getNextDirection(gridX, gridY, checkPos);
        int nx = gridX + desiredDir.dx;
        int ny = gridY + desiredDir.dy;
        if (!desiredDir.isNone() && canMoveTo(checkPos, nx, ny)) {
            currentDir = desiredDir;
        }
    }
    
    // get the next position based on current direction
    int nextX = gridX + currentDir.dx;
    int nextY = gridY + currentDir.dy;

    // --------- Portal Logic ---------
    // If the next cell is a portal, teleport to the other portal and return
    if (canMoveTo(checkPos, nextX, nextY) && checkPos.isPortal(nextX, nextY)) {
        for (int x = 0; x < LEVEL_WIDTH; ++x) {
            if (x != nextX && checkPos.isPortal(x, nextY)) {
                gridX = x;
                gridY = nextY;
                px = gridX * CELL_SIZE;
                py = gridY * CELL_SIZE;
                return;
            }
        }
    }

    // Normal movement
    if (canMoveTo(checkPos, nextX, nextY)) {
        px += currentDir.dx * speed;
        py += currentDir.dy * speed;
        if (nearCenterOfCell()) {
            gridX = static_cast<int>(px) / CELL_SIZE;
            gridY = static_cast<int>(py) / CELL_SIZE;
            px = gridX * CELL_SIZE;
            py = gridY * CELL_SIZE;
        }
    } else {
        // Snap to grid if blocked
        px = gridX * CELL_SIZE;
        py = gridY * CELL_SIZE;
    }
}   


int Figure::getX() const {
    return gridX;
}
int Figure::getY() const {
    return gridY;
}

float Figure::getPx() const {
    return px;
}
float Figure::getPy() const {
    return py;
}

Figure::~Figure() {
    delete controller; // Clean up the controller if it was dynamically allocated
}

//get current direction
Direction Figure::getCurrentDir() const {
    return currentDir;
}

void Figure::setPosition(int x, int y) {
    gridX = x;
    gridY = y;
    px = static_cast<float>(x) * CELL_SIZE;
    py = static_cast<float>(y) * CELL_SIZE;
}
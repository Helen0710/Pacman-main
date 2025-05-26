

#include "figures.h"
#include "../Board/config.h"
#include "../utils.h"
#include "../Controls/controller.h"
#include <cmath>

Figure::Figure(int startX, int startY, Controller* ctrl)
    : gridX(startX),
      gridY(startY),
      px(static_cast<float>(startX) * CELL_SIZE),
      py(static_cast<float>(startY) * CELL_SIZE),
      currentDir(Direction::NONE),
      controller(ctrl) {}

void Figure::update(const Board& board) {
    int cx = gridX;
    int cy = gridY;

    // neue Richtung nur, wenn Taste gedrückt wurde
    Direction nextDir = controller->getNextDirection(cx, cy, board);

    if (!nextDir.isNone()) {
        int nx = cx + nextDir.dx;
        int ny = cy + nextDir.dy;

        if (canMoveTo(board, nx, ny)) {
            gridX = nx;
            gridY = ny;

            // Position in Pixeln direkt anpassen
            px = gridX * CELL_SIZE;
            py = gridY * CELL_SIZE;
        }

        currentDir = nextDir;
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
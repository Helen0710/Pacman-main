#include "check_collision.h"
#include <cmath>

bool CheckCollision::isPacmanCollidingWithGhost(const Figure& pacman, const Figure& ghost) {
    // Calculate the distance between PacMan and the ghost
    float dx = pacman.getPx() - ghost.getPx();
    float dy = pacman.getPy() - ghost.getPy();
    float distance = sqrt(dx * dx + dy * dy);

    // Check if the distance is less than the sum of their radii
    return distance < (CELL_SIZE / 2 + CELL_SIZE / 2);
}

bool CheckCollision::isPacmanCollidingWithPoint(const Figure& pacman, Points& points) {
    int y = pacman.getY();
    int x = pacman.getX();
    if (y < 0 || y >= LEVEL_HEIGHT || x < 0 || x >= LEVEL_WIDTH)
        return false;

    if (points.getPoint(y, x)) { // Use accessor method
        points.setPoint(y, x, false);
        return true;
    }
    return false;
}





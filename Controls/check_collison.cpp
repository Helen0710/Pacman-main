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
    if (y < 0 || y >= getLevelHeight() || x < 0 || x >= getLevelWidth())
        return false;

    if (points.getPoint(y, x)) { // Use accessor method
        points.setPoint(y, x, false);
        return true;
    }
    return false;
}

bool CheckCollision::isPacmanCollidingWithFruit(const Figure& pacman, const Item& fruit) {
    // Calculate the distance between PacMan and the fruit
    float dx = pacman.getPx() - fruit.getPx();
    float dy = pacman.getPy() - fruit.getPy();
    float distance = sqrt(dx * dx + dy * dy);

    // Check if the distance is less than the sum of their radii
    return distance < (CELL_SIZE / 2 + CELL_SIZE / 2);
}





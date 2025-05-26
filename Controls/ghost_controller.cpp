#include "ghost_controller.h"
#include "../GameObjects/figures.h" 
#include <vector>

#include <cmath>
#include <algorithm>

// Constructor	
GhostController::GhostController(const PacMan* pac, const Figure* blinky)
    : currentDir(Direction::RIGHT), pacman(pac), blinky(blinky) {}


// Choose the best direction for the ghost to move towards the target
Direction GhostController::chooseBestDirection(int gx, int gy, const Board& board, Position target){
    std::vector<Direction> possibleDirections;

    if(board.isWalkableForGhost(gx, gy -1)) possibleDirections.push_back(Direction::UP);
    if(board.isWalkableForGhost(gx, gy + 1)) possibleDirections.push_back(Direction::DOWN);
    if(board.isWalkableForGhost(gx - 1, gy)) possibleDirections.push_back(Direction::LEFT);
    if(board.isWalkableForGhost(gx + 1, gy)) possibleDirections.push_back(Direction::RIGHT);

    //try not to go backwards unless there is no other option
    if(possibleDirections.size() > 1){
        Direction opposite(- currentDir.dx, - currentDir.dy);
        possibleDirections.erase(std::remove(possibleDirections.begin(), possibleDirections.end(), opposite), possibleDirections.end());
    }

    //choose best direction (towards target)
    Direction bestDir = Direction::NONE;
    float bestDist = std::numeric_limits<float>::max();

    for (const Direction& dir : possibleDirections) {
        int nx = gx + dir.dx;
        int ny = gy + dir.dy;
        // Calculate distance to target
        float dx = static_cast<float>(nx - target.x);
        float dy = static_cast<float>(ny - target.y);
        float dist = std::sqrt(dx * dx + dy * dy);
        
        if (dist < bestDist) {
            bestDist = dist;
            bestDir = dir;
        }
    }

    currentDir = bestDir;
    return bestDir;
}



// BlinkyController
BlinkyController::BlinkyController(const PacMan* pac) : GhostController(pac) {}

Direction BlinkyController::getNextDirection(int gx, int gy, const Board& board) {
    Position target = { pacman->getX(), pacman->getY() };
    return chooseBestDirection(gx, gy, board, target);
}

// PinkyController
PinkyController::PinkyController(const PacMan* pac) : GhostController(pac) {}

Direction PinkyController::getNextDirection(int gx, int gy, const Board& board) {
    int tx = pacman->getX() + 4 * pacman->getCurrentDir().dx;
    int ty = pacman->getY() + 4 * pacman->getCurrentDir().dy;
    Position target = { tx, ty };
    return chooseBestDirection(gx, gy, board, target);

}

// InkyController
InkyController::InkyController(const PacMan* pac, const Figure* blinky) : GhostController(pac, blinky) {}

Direction InkyController::getNextDirection(int gx, int gy, const Board& board) {
    int px = pacman->getX() + 2 * pacman->getCurrentDir().dx;
    int py = pacman->getY() + 2 * pacman->getCurrentDir().dy;

    int bx = blinky->getX();
    int by = blinky->getY();

    int dx = px - bx;
    int dy = py - by;

    Position target = { bx + 2 * dx, by + 2 * dy };
    return chooseBestDirection(gx, gy, board, target);
}

// ClydeController
ClydeController::ClydeController(const PacMan* pac) : GhostController(pac) {}

Direction ClydeController::getNextDirection(int gx, int gy, const Board& board) {
    int dx = pacman->getX() - gx;
    int dy = pacman->getY() - gy;
    float distSquared = static_cast<float>(dx * dx + dy * dy);

    if (distSquared > 64) { // Chase mode
        Position target = { pacman->getX(), pacman->getY() };
        return chooseBestDirection(gx, gy, board, target);
    } else { // Scatter mode
        Position target = { 0, LEVEL_HEIGHT - 1 }; // Example scatter target
        return chooseBestDirection(gx, gy, board, target);
    }
}
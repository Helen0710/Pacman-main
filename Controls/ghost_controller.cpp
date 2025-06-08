#include "ghost_controller.h"


// Constructor	
GhostController::GhostController(const PacMan* pac, const Figure* blinky)
    : currentDir(Direction::RIGHT), pacman(pac), blinky(blinky) {}

Direction GhostController::chooseBestDirection(int gx, int gy, const CheckPosition& checkPos, Position target){
    std::vector<Direction> possibleDirections;

    if(checkPos.isWalkableForGhost(gx, gy -1)) possibleDirections.push_back(Direction::UP);
    if(checkPos.isWalkableForGhost(gx, gy + 1)) possibleDirections.push_back(Direction::DOWN);
    if(checkPos.isWalkableForGhost(gx - 1, gy)) possibleDirections.push_back(Direction::LEFT);
    if(checkPos.isWalkableForGhost(gx + 1, gy)) possibleDirections.push_back(Direction::RIGHT);

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

void GhostController::updateMode( float deltaTime) {
    modeTimer += deltaTime;

    if (mode == GhostMode::SCATTER && modeTimer > GHOST_SCATTER_TIME) {
        mode = GhostMode::CHASE;
        modeTimer = 0.0f;
    } else if (mode == GhostMode::CHASE && modeTimer > GHOST_CHASE_TIME) {
        mode = GhostMode::SCATTER;
        modeTimer = 0.0f;
    }
}

void GhostController::UpdateAllGhostModes(const std::vector<Figure*>& figures, float deltaTime) {
    for (auto* fig : figures) {
        Ghost* ghost = dynamic_cast<Ghost*>(fig);
        if (ghost) {
            ghost->getController()->updateMode(deltaTime);
        }
    }
}

// BlinkyController
// BlinkyController is the ghost that always chases PacMan
// Scatter Mode: Top-right corner
BlinkyController::BlinkyController(const PacMan* pac) : GhostController(pac) {}

Direction BlinkyController::getNextDirection(int gx, int gy, const CheckPosition& checkPos) {
    if (getMode() == GhostMode::SCATTER) {
        Position target = { getLevelWidth() - 1, 0 }; // Top-right
        return chooseBestDirection(gx, gy, checkPos, target);
    }
    Position target = { pacman->getX(), pacman->getY() };
    return chooseBestDirection(gx, gy, checkPos, target);
}

// PinkyController
// PinkyController is the ghost that tries to predict PacMan's next position
// Scatter Mode: Top left corner
PinkyController::PinkyController(const PacMan* pac) : GhostController(pac) {}

Direction PinkyController::getNextDirection(int gx, int gy, const CheckPosition& checkPos) {
    if (getMode() == GhostMode::SCATTER) {
        Position target = { 0, 0 }; // Top-left
        return chooseBestDirection(gx, gy, checkPos, target);
    }
    int tx = pacman->getX() + 4 * pacman->getCurrentDir().dx;
    int ty = pacman->getY() + 4 * pacman->getCurrentDir().dy;
    Position target = { tx, ty };
    return chooseBestDirection(gx, gy, checkPos, target);

}

// InkyController
// InkyController is the ghost that uses Blinky's position to determine its target
// Scatter Mode: Bottom right corner
InkyController::InkyController(const PacMan* pac, const Figure* blinky) : GhostController(pac, blinky) {}

Direction InkyController::getNextDirection(int gx, int gy, const CheckPosition& checkPos) {
    if (getMode() == GhostMode::SCATTER) {
        Position target = { getLevelWidth() - 1, getLevelHeight() - 1 }; // Bottom-right
        return chooseBestDirection(gx, gy, checkPos, target);
    }
    int px = pacman->getX() + 2 * pacman->getCurrentDir().dx;
    int py = pacman->getY() + 2 * pacman->getCurrentDir().dy;

    int bx = blinky->getX();
    int by = blinky->getY();

    int dx = px - bx;
    int dy = py - by;

    Position target = { bx + 2 * dx, by + 2 * dy };
    return chooseBestDirection(gx, gy, checkPos, target);
}

// ClydeController
// ClydeController is the ghost that alternates between chase and scatter modes
// Scatter Mode: Bottom left corner
ClydeController::ClydeController(const PacMan* pac) : GhostController(pac) {}

Direction ClydeController::getNextDirection(int gx, int gy, const CheckPosition& checkPos) {
    int dx = pacman->getX() - gx;
    int dy = pacman->getY() - gy;
    float distSquared = static_cast<float>(dx * dx + dy * dy);

    if (distSquared > 64) { // Chase mode
        Position target = { pacman->getX(), pacman->getY() };
        return chooseBestDirection(gx, gy, checkPos, target);
    } else { // Scatter mode
        Position target = { 0, getLevelHeight() - 1 }; // Bottom-left
        return chooseBestDirection(gx, gy, checkPos, target);
    }
}

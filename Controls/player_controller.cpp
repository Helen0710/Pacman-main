#include "player_controller.h"
#include "raylib.h"
#include <iostream>

PlayerController::PlayerController() : currentDir(Direction::NONE), nextDir(Direction::NONE) {}

Direction PlayerController::getNextDirection(int gridX, int gridY, const CheckPosition& checkPos) {
    if (IsKeyDown(KEY_UP)) nextDir = Direction::UP;
    if (IsKeyDown(KEY_DOWN)) nextDir = Direction::DOWN;
    if (IsKeyDown(KEY_LEFT)) nextDir = Direction::LEFT;
    if (IsKeyDown(KEY_RIGHT)) nextDir = Direction::RIGHT;

    // Check if the next direction is valid
    int nx = gridX + nextDir.dx;
    int ny = gridY + nextDir.dy;
    if (checkPos.isWalkableForPacman(nx, ny)) {

        currentDir = nextDir;
    }
    //std::cout << "PlayerController: Current Position (" << gridX << ", " << gridY << "), Next Direction (" 
              //<< nextDir.dx << ", " << nextDir.dy << ")" << std::endl;

    return currentDir;
}
#include "player_controller.h"
#include "raylib.h"

PlayerController::PlayerController() : currentDir(Direction::NONE), nextDir(Direction::NONE) {}

Direction PlayerController::getNextDirection(int gridX, int gridY, const Board& board) {
    if (IsKeyPressed(KEY_UP)) nextDir = Direction::UP;
    if (IsKeyPressed(KEY_DOWN)) nextDir = Direction::DOWN;
    if (IsKeyPressed(KEY_LEFT)) nextDir = Direction::LEFT;
    if (IsKeyPressed(KEY_RIGHT)) nextDir = Direction::RIGHT;

    // Check if the next direction is valid
    int nx = gridX + nextDir.dx;
    int ny = gridY + nextDir.dy;
    if (board.isWalkableForPacman(nx, ny)) {

        currentDir = nextDir;
    }

    return currentDir;
}
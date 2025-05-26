#pragma once
#include "controller.h"

class PlayerController : public Controller {
    private:
        Direction currentDir;
        Direction nextDir;

    public:
        PlayerController();
        Direction getNextDirection(int gridX, int gridY, const Board& board) override;
};
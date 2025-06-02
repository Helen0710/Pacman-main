#pragma once
#include "controller.h"
#include "../Board/check_position.h"

class PlayerController : public Controller {
    private:
        Direction currentDir;
        Direction nextDir;

    public:
        PlayerController();
        Direction getNextDirection(int gridX, int gridY, const CheckPosition& checkPos) override;
};
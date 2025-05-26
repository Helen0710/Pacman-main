#pragma once
#include "../utils.h"	
#include "../Board/board.h"

class Controller{
    public:
        virtual ~Controller() = default;
        virtual Direction getNextDirection(int gridX, int gridY, const Board& board) = 0;
};
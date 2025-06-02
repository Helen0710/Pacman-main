#pragma once
#include "../utils.h"	
#include "../Board/board.h"
#include "../Board/config.h"
#include "../Board/check_position.h"	

class Controller{
    public:
        virtual ~Controller() = default;
        virtual Direction getNextDirection(int gridX, int gridY, const CheckPosition& checkPos) = 0;

};
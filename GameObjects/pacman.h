#pragma once
#include "../Board/board.h"
#include "figures.h"
#include "../utils.h"

// Direction is already defined in utils.h, so we do not redefine it here.

class PacMan : public Figure{
   

    public:
        PacMan(int startX , int startY, Controller* ctrl);
        void draw() const override;
        bool canMoveTo(const Board& board, int x, int y) const override;

};
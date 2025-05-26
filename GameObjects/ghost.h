#pragma once

#include "figures.h"
#include "raylib.h"
#include "../Controls/controller.h"

class Ghost : public Figure {
    private:
        Color ghostcolor;

    public: 
        Ghost(int startX, int startY, Controller* ctrl, Color color);
        void draw() const override;
        bool canMoveTo(const Board& board, int x, int y) const override;
};
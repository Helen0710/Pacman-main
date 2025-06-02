#pragma once

#include "../Board/board.h"
#include "../Board/config.h"
#include "../Board/check_position.h"

#include "../Controls/controller.h"
#include "../Controls/player_controller.h"

#include "figures.h"
#include "game_objects.h"
#include "../utils.h"

// Direction is already defined in utils.h, so we do not redefine it here.

class PacMan : public Figure{
    private:
        float timeSinceLastMove = 0.0f; // Time since the last move
        float moveInterval = PACMAN_SPEED ; // Interval between moves in seconds
   

    public:
        PacMan(int startX , int startY, Controller* ctrl, float spd);
        void draw() const override;
        bool canMoveTo(const CheckPosition& checkPos, int x, int y) const override;
        void update(const CheckPosition& checkPos) override; // Update method to handle movement and state changes

};
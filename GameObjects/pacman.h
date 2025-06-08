#pragma once

#include "../Board/board.h"
#include "../config.h"
#include "../Board/check_position.h"

#include "../Controls/controller.h"
#include "../Controls/player_controller.h"

#include "figures.h"
#include "game_objects.h"
#include "../utils.h"

enum class PacManState { Alive, Dying, Dead };

class PacMan : public Figure{
    private:
        PacManState state = PacManState::Alive;
        float deathTimer = 0.0f;
        float timeSinceLastMove = 0.0f; // Time since the last move
        float moveInterval = PACMAN_SPEED ; // Interval between moves in seconds
   

    public:
        PacMan(int startX , int startY, Controller* ctrl, float spd);
        void draw() const override;
        bool canMoveTo(const CheckPosition& checkPos, int x, int y) const override;
        void update(const CheckPosition& checkPos) override; // Update method to handle movement and state changes
        void startDeathAnimation();
        PacManState getState() const { return state; } // Getter for the current state
        void resetState() { state = PacManState::Alive; deathTimer = 0.0f; } // Reset to alive state
        void resetForNewGame(int x, int y);

};
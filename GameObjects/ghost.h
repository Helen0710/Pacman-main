#pragma once
#include "raylib.h"

#include "figures.h"
#include "game_objects.h"

#include "../Controls/controller.h"
#include "../Controls/ghost_controller.h"

#include "../Board/check_position.h"
#include "../config.h"

#include "../utils.h"

class GhostController;

class Ghost : public Figure {
    private:
        Color ghostcolor;
    public: 
        Ghost(int startX, int startY, Controller* ctrl, Color color, float spd);
        void draw() const override;
        bool canMoveTo(const CheckPosition& checkPos, int x, int y) const override;
        void update(const CheckPosition& checkPos) override;
        void setSpeed(float newSpeed);
        GhostController* getController();
        void resetForNewGame(int x, int y);
};
#pragma once
#include "game_objects.h"
#include "../config.h"
#include "../Board/check_position.h"
#include "../Controls/check_collision.h"


class Lives {
private:
    int lives;
    float immunityTimer;
    const int maxLives = MAX_LIVES;
    bool immune = false;
public:
    Lives() : lives(maxLives), immunityTimer(0.0f) {}
    void loseLife();
    void reset();
    void update(float deltaTime);
    void draw() const;
    int getLives() const;
    bool isImmune() const;
    bool isGameOver() const;
};
    
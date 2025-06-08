#pragma once
#include "raylib.h"
#include "../config.h"

class Instructions {
public:
    Instructions(int screenWidth, int screenHeight);
    void draw();
    void update(bool& backToMenu);

private:
    int screenWidth;
    int screenHeight;
};


#pragma once
#include "../GameObjects/game_objects.h"
#include "../GameObjects/figures.h"
#include "../GameObjects/points.h"
#include "../Board/check_position.h"
#include "../Board/config.h"

class CheckCollision {
    public:
        // Check if PacMan collides with a ghost
        static bool isPacmanCollidingWithGhost(const Figure& pacman, const Figure& ghost); 

        // Check if PacMan collides with a point
        static bool isPacmanCollidingWithPoint(const Figure& pacman, Points& points);

        // Check if pacman collides with Fruit

    
};
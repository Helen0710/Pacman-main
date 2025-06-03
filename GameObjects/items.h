#pragma once

#include "game_objects.h"
#include "../Board/config.h"
#include "../Board/check_position.h"
#include "../Controls/controller.h"

class CheckPosition; // Forward declaration to avoid circular dependency


class Item : public GameObject {
private:
    int x; // Grid x position
    int y; // Grid y position
    float px; // Pixel x position
    float py; // Pixel y position

    Controller* controller; // Pointer to the controller for the item

    public:
        //Constructor and destructor
        Item(int startX, int startY, Controller* ctrl);
        virtual ~Item() = default; // Virtual destructor for proper cleanup

        //getX, getY, getPx, getPy methods are pure virtual in GameObject
        int getX() const override;
        int getY() const override;
        float getPx() const override;
        float getPy() const override;






};
#pragma once

#include "game_objects.h"
#include "../config.h"

// Base class for all collectible items (points, fruits, etc.)
class Item : public GameObject {
protected:
    int x, y;           // Grid position
    float px, py;       // Pixel position
    int value;          // Score value
    bool active;        // Is the item still available?

public:
    Item(int startX, int startY, int value)
        : x(startX), y(startY), px(startX * CELL_SIZE), py(startY * CELL_SIZE), value(value), active(true) {}

    virtual ~Item() = default;

    int getX() const override { return x; }
    int getY() const override { return y; }
    float getPx() const override { return px; }
    float getPy() const override { return py; }
    int getValue() const { return value; }
    bool isActive() const { return active; }
    void setActive(bool a) { active = a; }

    // Each item must implement its own draw method
    virtual void draw() const override = 0;
};

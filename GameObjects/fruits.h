#pragma once
#include "items.h"
#include "../config.h"
#include "../utils.h"
#include "../Board/check_position.h"
#include "raylib.h"
#include "../Board/check_position.h"
#include <cstdlib>

class Fruit : public Item {
    int type;      // e.g. 0=cherry, 1=strawberry, etc.
    float timer;   // How long the fruit stays visible
    int dotsEaten = 0;
public:
    Fruit(int x, int y, int type, int value)
        : Item(x, y, value), type(type), timer(0.0f) {}
    void draw() const override;
    void update(float deltaTime); // For timer logic
    void spawnWithType(int FruitType, const CheckPosition& checkPos ); // Spawn at a random walkable position
    bool isActive() const { return active; }
    void setActive(bool a) { active = a; }
    int getType() const { return type; }
    void checkAndSpawnFruit(Fruit& fruit, const CheckPosition& checkPos, int dotsEaten, int level);
    static int getFruitTypeForLevel(int level);
    static int getFruitValueForType(int type);  
};
#include "fruits.h"


// Draw the fruit (simple: different color for each type)
void Fruit::draw() const {
    if (!active) return;

    int cx = (int)(px + CELL_SIZE / 2);
    int cy = (int)(py + CELL_SIZE / 2 + TOP_MARGIN);
    float r = CELL_SIZE / 4.0f;

    switch (type) {
        case 0: // Cherry
            DrawCircle(cx - (int)(r/2), cy, (int)r, RED);
            DrawCircle(cx + (int)(r/2), cy, (int)r, RED);
            DrawLine(cx - (int)(r/2), cy - (int)r, cx, cy - (int)(1.5*r), DARKGREEN);
            DrawLine(cx + (int)(r/2), cy - (int)r, cx, cy - (int)(1.5*r), DARKGREEN);
            break;
        case 1: // Strawberry
            DrawCircle(cx, cy, r, RED);
            DrawTriangle(
                { (float)cx, (float)(cy - r) },
                { (float)(cx - r), (float)(cy + r) },
                { (float)(cx + r), (float)(cy + r) },
                MAROON
            );
            DrawCircle(cx, cy - (int)(r/2), (int)(r/3), DARKGREEN); // leaves
            DrawCircle(cx + (int)(r/3), cy - (int)(r/3), 1, YELLOW); // seeds
            DrawCircle(cx - (int)(r/3), cy, 1, YELLOW);
            DrawCircle(cx, cy + (int)(r/3), 1, YELLOW);
            break;
        case 2: // Orange
            DrawCircle(cx, cy, r, ORANGE);
            DrawLine(cx, cy - (int)r, cx, cy - (int)(r*1.5f), DARKGREEN);
            DrawCircle(cx, cy - (int)(r*1.5f), 2, DARKGREEN);
            break;
        case 3: // Apple
            DrawCircle(cx, cy, r, GREEN);
            DrawLine(cx, cy - (int)r, cx, cy - (int)(r*1.5f), BROWN);
            DrawCircle(cx + (int)(r/2), cy - (int)(r*0.8f), 2, DARKGREEN); // leaf
            break;
        case 4: // Melon
            DrawCircle(cx, cy, r, DARKGREEN);
            DrawLine(cx - (int)(r/2), cy, cx + (int)(r/2), cy, GREEN);
            DrawLine(cx, cy - (int)(r/2), cx, cy + (int)(r/2), GREEN);
            break;
        case 5: // Galaxian
            DrawCircle(cx, cy, r, BLUE);
            DrawTriangle(
                { (float)cx, (float)(cy - r) },
                { (float)(cx - r), (float)(cy + r) },
                { (float)(cx + r), (float)(cy + r) },
                YELLOW
            );
            break;
        case 6: // Bell
            DrawCircle(cx, cy, r, GOLD);
            DrawRectangle(cx - (int)(r/2), cy, (int)r, (int)(r/2), GOLD);
            DrawCircle(cx, cy + (int)(r/2), (int)(r/4), DARKGRAY);
            break;
        case 7: { // Key (golden, stylized)
            Color gold = GOLD;
            Color dark = DARKBROWN;

            // Key shaft
            DrawRectangle(cx - (int)(r*0.6f), cy - (int)(r*0.2f), (int)(r*1.2f), (int)(r*0.4f), gold);

            // Key head (circular)
            DrawCircle(cx + (int)(r*0.6f), cy, (int)(r*0.5f), gold);
            DrawCircle(cx + (int)(r*0.6f), cy, (int)(r*0.2f), DARKGRAY); // inner hole

            // Key teeth
            DrawRectangle(cx - (int)(r*0.6f), cy - (int)(r*0.6f), (int)(r*0.2f), (int)(r*0.4f), gold);
            DrawRectangle(cx - (int)(r*0.3f), cy - (int)(r*0.6f), (int)(r*0.2f), (int)(r*0.4f), gold);
            break;
        }

        default: // Fallback
            DrawCircle(cx, cy, CELL_SIZE / 2 - 4, PINK);
            break;
    }
}

// Update the fruit's timer and deactivate when time is up
void Fruit::update(float deltaTime) {
    if (!active) return;
    timer += deltaTime;
    if (timer > 8.0f) { // Fruit stays for 8 seconds
        active = false;
    }
}

// Spawn fruit at a random walkable position with a specific type
void Fruit::spawnWithType(int fruitType, const CheckPosition& checkPos) {
    // Try up to 100 times to find a walkable spot
    for (int tries = 0; tries < 100; ++tries) {
        int randX = rand() % getLevelWidth();
        int randY = rand() % getLevelHeight();
        if (checkPos.isWalkableForPacman(randX, randY)) {
            x = randX;
            y = randY;
            px = x * CELL_SIZE;
            py = y * CELL_SIZE;
            type = fruitType;
            value = getFruitValueForType(fruitType);
            active = true;
            timer = 0.0f;
            return;
        }
    }
    // If no spot found, don't spawn
    active = false;
}

// Check and spawn fruit based on dots eaten and level
void Fruit::checkAndSpawnFruit(Fruit& fruit, const CheckPosition& checkPos, int dotsEaten, int level) {
    if (!fruit.isActive() && (dotsEaten == 70 || dotsEaten == 170)) {
        int fruitType = Fruit::getFruitTypeForLevel(level);
        fruit.spawnWithType(fruitType, checkPos);
    }
}

// Pac-Man fruit table (original mapping)
int Fruit::getFruitTypeForLevel(int level) {
    if (level == 1) return 0; // Cherry
    if (level == 2) return 1; // Strawberry
    if (level == 3 || level == 4) return 2; // Orange
    if (level == 5 || level == 6) return 3; // Apple
    if (level == 7 || level == 8) return 4; // Melon
    if (level == 9 || level == 10) return 5; // Galaxian
    if (level == 11 || level == 12) return 6; // Bell
    return 7; // Key (level 13+)
}

//Fruit values
int Fruit::getFruitValueForType(int type) {
    switch(type){
        case 0: return 100; //Cherry
        case 1: return 300; //Strawberry
        case 2: return 500; //Orange
        case 3: return 700; //Apple
        case 4: return 1000; //Melon
        case 5: return 2000; // Galaxian
        case 6: return 3000; //Bell
        case 7: return 5000; //Key
        default: return 100;
    }
}


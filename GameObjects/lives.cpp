#include "lives.h"
#include "raylib.h"


// should display three lives in form of three pacman figures in the botom left corner of the screen
// should be able to update the lives when pacman dies
    // use check_collision to check if pacman collides with a ghost
    // if yes, decrease the lives by one and make Pacman immune for a short time
    // if not, do nothing
    //if lives are 0, end the game and display a game over on the game screen
//extras play sound or animation when a life is lost

// loseLife method to decrease lives and set immunity
void Lives::loseLife() {
    if (lives > 0) {
        lives--;
        immune = true;
        immunityTimer = 2.0f; // Set immunity for 2 seconds
    }
}

// reset method to restore lives and immunity
void Lives::reset() {
    lives = maxLives;
    immune = false;
    immunityTimer = 0.0f;
}

// update method to handle immunity timer
void Lives::update(float deltaTime) {
    if (immune) {
        immunityTimer -= deltaTime;
        if (immunityTimer <= 0.0f) {
            immune = false; // Immunity ends
        }
    }
}

// draw method to display lives and immunity status
void Lives::draw() const {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    for (int i = 0; i < lives; ++i) {
        int x = 20 + i * (CELL_SIZE + 10); // Position each life with some spacing
        int y = screenHeight - BOTTOM_MARGIN + 10; // Bottom left corner
        DrawCircle(x + CELL_SIZE / 2, y + CELL_SIZE / 2, CELL_SIZE / 2, YELLOW); // Draw PacMan as a circle
        if (immune) {
            // Flash PacMan during immunity
            if (static_cast<int>(immunityTimer * 10) % 2 == 0) {
                DrawCircle(x + CELL_SIZE / 2, y + CELL_SIZE / 2, CELL_SIZE / 2, DARKGRAY); // Draw gray circle to indicate immunity
            }
        }
    }
}

// getLives method to return the current number of lives
int Lives::getLives() const {
    return lives;
}

// isImmune method to check if PacMan is currently immune
bool Lives::isImmune() const {
    return immune;
}

// isGameOver method to check if the game is over
bool Lives::isGameOver() const {
    return lives <= 0;
}





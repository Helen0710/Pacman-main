#include "game.h"

void Game::resetCharacterPositions() {
    pacman->setPosition(pacmanStartInitial.x, pacmanStartInitial.y);
    blinky->setPosition(blinkyStartInitial.x, blinkyStartInitial.y);
    pinky->setPosition(pinkyStartInitial.x, pinkyStartInitial.y);
    inky->setPosition(inkyStartInitial.x, inkyStartInitial.y);
    clyde->setPosition(clydeStartInitial.x, clydeStartInitial.y);
}

void Game::resetGhostSpeeds(float speed) {
    blinky->setSpeed(speed);
    pinky->setSpeed(speed);
    inky->setSpeed(speed);
    clyde->setSpeed(speed);
}



bool Game::updatePacmanDeath() {
    pacman->update(*checkPos); // advances deathTimer

    if (pacman->getState() == PacManState::Dead) {
        lives->loseLife();
        if (lives->isGameOver()) {
            state = GameState::GameOver;
        } else {
            resetCharacterPositions();
            pacman->resetState();
        }
        return true; // Animation finished
    }
    return false; // Animation still running
}

void Game::updatePacmanAndHandleCollisions(float deltaTime) {
    // --- Normal update and collision logic ---
    for (auto* fig : figures) {
        fig->update(*checkPos);

        if (fig == pacman && pacman->getState() == PacManState::Alive) {
            if (CheckCollision::isPacmanCollidingWithPoint(*pacman, *point)) {
                score += 10;
                 dotsEaten++;
            }

            // Collision with ghosts
            for (auto* other : figures) {
                 if (other != pacman &&
                    CheckCollision::isPacmanCollidingWithGhost(*pacman, *other)) {
                        if (!lives->isImmune()) {
                            pacman->startDeathAnimation();
                        }
                    }
            }
        }
    }
}

void Game::handleFruitLogic(float deltaTime){
     // Fruit spawn logic (call as member function)
    fruit->checkAndSpawnFruit(*fruit, *checkPos, dotsEaten, level);

    fruit->update(deltaTime);
    if (fruit->isActive() &&
        CheckCollision::isPacmanCollidingWithFruit(*pacman, *fruit)) {
        score += fruit->getValue();
        // Popup setup
        fruitPopupValue = fruit->getValue();
        fruitPopupTimer = 1.0f; // show for 1 second
        fruitPopupX = static_cast<int>(pacman->getPx());
        fruitPopupY = static_cast<int>(pacman->getPy() + TOP_MARGIN);
        fruit->setActive(false);
    }
}

//Level Logic
bool Game::checkAndHandleLevelUp(){
    if (!point->hasRemainingPoints()) {
        if (level >= 13){
            state = GameState::Won;
            return true;
        }
        level++;
        int speedIndex = std::min((level - 1) / 2, (int)NUM_SPEEDS - 1);
        ghostSpeed = GHOST_SPEEDS[speedIndex];

        point->resetPoints(*checkPos);

        resetCharacterPositions();
        resetGhostSpeeds(ghostSpeed);

        pacman->resetState();
        fruit->setActive(false);
        dotsEaten = 0;

        levelTransitionTimer = 0.0f;
        state = GameState::LevelTransition;

        return true;
    }
    return false;
}

void Game::handleGameOver() {
     drawGameOver();
    UpdateMusicStream(game_over);
    if (IsKeyPressed(KEY_ENTER)) {
        state = GameState::StartScreen;
        userManager->saveScore(score, "scores.txt");
        userManager->reset();
        lives->reset();
        point->resetPoints(*checkPos);
        fruit->setActive(false);
        dotsEaten = 0;
        level = 1;
        ghostSpeed = GHOST_SPEEDS[0]; // Reset ghost speed
    }

    resetCharacterPositions();

}


void Game::handleGameWon() {

    drawYouWon();

    if (IsKeyPressed(KEY_ENTER)) {
        state = GameState::StartScreen;
        userManager->saveScore(score, "scores.txt");
        userManager->reset();
        lives->reset();
        point->resetPoints(*checkPos);
        fruit->setActive(false);
        dotsEaten = 0;
        level = 1;
        ghostSpeed = GHOST_SPEEDS[0];
        resetCharacterPositions();
    }
}

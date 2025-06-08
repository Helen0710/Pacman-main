
#include "raylib.h"
#include "game.h"

void Game::drawGameScene() {
    board->draw();
    for (auto* fig : figures) fig->draw();
    point->draw();
    lives->draw();
    fruit->draw();
    DrawText(TextFormat("Score: %d", score), 20, 20, 30, YELLOW);

    // Level-Anzeige unten rechts
    int levelFontSize = 24;
    const char* levelText = TextFormat("Level: %d", level);
    int levelTextWidth = MeasureText(levelText, levelFontSize);
    DrawText(levelText, screenWidth - levelTextWidth - 20, screenHeight - levelFontSize - 20, levelFontSize, YELLOW);

    // Fruit-Popup
    if (fruitPopupTimer > 0.0f) {
        DrawText(
            TextFormat("+%d", fruitPopupValue),
            fruitPopupX,
            fruitPopupY - static_cast<int>(40 * (1.0f - fruitPopupTimer)),
            32,
            ORANGE
        );
    }
}


void Game::drawPacmanDeath() {
    board->draw();
    for (auto* fig : figures) fig->draw();
    point->draw();
    lives->draw();
    DrawText(TextFormat("Score: %d", score), 20, 20, 30, YELLOW);
}


void Game::drawLevelTransition() {
    board->draw();
    point->draw();
    lives->draw();
    DrawText(TextFormat("Score: %d", score), 20, 20, 30, YELLOW);

    int overlayFontSize = 48;
    const char* overlayText = TextFormat("Level %d", level);
    int textWidth = MeasureText(overlayText, overlayFontSize);
    DrawRectangle(0, screenHeight/2 - 60, screenWidth, 120, Fade(BLACK, 0.7f));
    DrawText(
        overlayText,
        screenWidth/2 - textWidth/2,
        screenHeight/2 - overlayFontSize/2,
        overlayFontSize,
        YELLOW
    );
}

void Game::drawScoreboard() {
    ClearBackground(BLACK);
    DrawText("HIGHSCORES", screenWidth / 2 - 100, 40, 30, YELLOW);

    auto highscores = userManager->loadScores("scores.txt");
    scoreboard->SetScores(highscores);
    scoreboard -> drawScore();
    int y = 100;

    DrawText("Press Enter to return to Start Screen", 100, y + 30, 20, WHITE);
}

void Game::drawGameOver() {
    DrawText("GAME OVER", screenWidth / 2 - 100, screenHeight / 2 - 20, 40, RED);
    DrawText("Press Enter to return to Start Screen", screenWidth / 2 - 180, screenHeight / 2 + 40, 20, WHITE);
}

void Game::drawYouWon() {
    DrawText("YOU WON!", screenWidth / 2 - 100, screenHeight / 2 - 20, 40, GREEN);
    DrawText("Press Enter to return to Start Screen", screenWidth / 2 - 180, screenHeight / 2 + 40, 20, WHITE);
}
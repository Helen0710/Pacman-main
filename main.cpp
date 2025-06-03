#include "master_header.h"
#include "raylib.h"
#include <vector>
#include <math.h>

enum class GameState {
    StartScreen,
    Playing,
    Scoreboard,
    GameOver,
    UserInput
};

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "PacMan - TSA/TSL2429");
    SetTargetFPS(60);

    Board board;
    CheckPosition checkPos(board);
    Points point(checkPos);
   int score;

    StartScreen startScreen(SCREEN_WIDTH, SCREEN_HEIGHT);
    Scoreboard scoreboard(SCREEN_WIDTH, SCREEN_HEIGHT);

    UserManager userManager;
    Lives lives;
    lives.reset();


    // Get start positions
    Position pacmanStart, blinkyStart, pinkyStart, inkyStart, clydeStart;
    board.getStartPositions(pacmanStart, blinkyStart, pinkyStart, inkyStart, clydeStart);
    Position pacmanStartInitial = pacmanStart;
    Position blinkyStartInitial = blinkyStart;
    Position pinkyStartInitial  = pinkyStart;
    Position inkyStartInitial   = inkyStart;
    Position clydeStartInitial  = clydeStart;


    // Create figures
    std::vector<Figure*> figures;
    PacMan* pacman = new PacMan(pacmanStart.x, pacmanStart.y, new PlayerController(), PACMAN_SPEED);
    figures.push_back(pacman);

    Ghost* blinky = new Ghost(blinkyStart.x, blinkyStart.y, new BlinkyController(pacman), RED, GHOST_SPEED);
    Ghost* pinky = new Ghost(pinkyStart.x, pinkyStart.y, new PinkyController(pacman), GHOST_PINK, GHOST_SPEED);
    Ghost* inky = new Ghost(inkyStart.x, inkyStart.y, new InkyController(pacman, blinky), GHOST_CYAN, GHOST_SPEED);
    Ghost* clyde = new Ghost(clydeStart.x, clydeStart.y, new ClydeController(pacman), GHOST_ORANGE, GHOST_SPEED);
    
    figures.push_back(blinky);
    figures.push_back(pinky);
    figures.push_back(inky);
    figures.push_back(clyde);

    GameState state = GameState::StartScreen;

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(BLACK);

        switch (state) {
            case GameState::StartScreen:
                startScreen.update();
                startScreen.draw();
                pacman-> resetState(); 

                if (startScreen.isOptionSelected()) {
                    int choice = startScreen.getSelection();
                    if (choice == 0) {
                        state = GameState::UserInput;
                    } else if (choice == 2) {
                        state = GameState::Scoreboard;
                    } else if (choice == 3) {
                        CloseWindow();
                        return 0;
                    }
                }
                break;
            case GameState::UserInput:
                score = 0;
                userManager.inputName();
                userManager.drawNameInput();

                if (userManager.isNameEntered() && !userManager.getCurrentUser().empty()) {
                    scoreboard.AddUser(userManager.getCurrentUser());
                    state = GameState::Playing;
                }
                break;
            case GameState::Playing: {
                float deltaTime = GetFrameTime();
                // Update ghost modes
                for (auto* fig : figures) {
                    Ghost* ghost = dynamic_cast<Ghost*>(fig);
                    if (ghost) {
                        ghost->getController()->updateMode(deltaTime);
                    }
                }

                lives.update(deltaTime);
                  // --- PacMan Death Animation Handling ---
                if (pacman->getState() == PacManState::Dying) {
                    pacman->update(checkPos); // advances deathTimer
                    board.draw();
                    for (auto* fig : figures) fig->draw();
                    point.draw();
                    lives.draw();
                    DrawText(TextFormat("Score: %d", score), 20, 20, 30, YELLOW);
                    // Wait until animation is done
                    if (pacman->getState() == PacManState::Dead) {
                        lives.loseLife();
                        if (lives.isGameOver()) {
                            TraceLog(LOG_ERROR, "PacMan has no lives left! Game Over.");
                            state = GameState::GameOver;
                        } else {
                            // Reset positions after losing a life
                            pacman->setPosition(pacmanStartInitial.x, pacmanStartInitial.y);
                            blinky->setPosition(blinkyStartInitial.x, blinkyStartInitial.y);
                            pinky->setPosition(pinkyStartInitial.x, pinkyStartInitial.y);
                            inky->setPosition(inkyStartInitial.x, inkyStartInitial.y);
                            clyde->setPosition(clydeStartInitial.x, clydeStartInitial.y);
                            pacman->resetState(); // set PacMan back to Alive
                        }
                    }
                    break; // skip the rest of the Playing logic while dying/dead
                }

                // --- Normal update and collision logic ---

                // Update figures and handle collisions
                for (auto* fig : figures) {
                    fig->update(checkPos);

                    if (fig == pacman && pacman->getState() == PacManState::Alive) {
                        if (CheckCollision::isPacmanCollidingWithPoint(*pacman, point)) {
                            score += 10;
                            TraceLog(LOG_INFO, "Punkte: %d", score);
                        }

                        // Collision with ghosts
                        for (auto* other : figures) {
                            if (other != pacman &&
                                CheckCollision::isPacmanCollidingWithGhost(*pacman, *other)) {
                                  if (!lives.isImmune()) {
                                    pacman->startDeathAnimation(); // Start dying animation
                                    // Do NOT lose life or reset here!
                                }
                            }
                        }
                    }
                }

                board.draw();
                for (auto* fig : figures) fig->draw();
                point.draw();
                lives.draw();
                

                break;
            }

           case GameState::Scoreboard: {
            ClearBackground(BLACK);
            DrawText("HIGHSCORES", SCREEN_WIDTH / 2 - 100, 40, 30, YELLOW);

            auto highscores = userManager.loadScores("scores.txt");
            int y = 100;
            for (const auto& entry : highscores) {
                std::string text = entry.first + " - " + std::to_string(entry.second);
                DrawText(text.c_str(), 100, y, 20, GREEN);
                y += 30;
            }

            DrawText("Drücke ENTER, um zum Hauptmenü zurückzukehren", 100, y + 30, 20, WHITE);

            if (IsKeyPressed(KEY_ENTER)) {
                state = GameState::StartScreen;
                
            }
            break;
        }


        case GameState::GameOver:
                DrawText("GAME OVER", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 20, 40, RED);
                DrawText("Drücke ENTER zum Zurückkehren", SCREEN_WIDTH / 2 - 180, SCREEN_HEIGHT / 2 + 40, 20, WHITE);
                
                if (IsKeyPressed(KEY_ENTER)) {
                    state = GameState::StartScreen;
                    userManager.saveScore(score, "scores.txt");  
                    userManager.reset();
                    lives.reset(); // Reset lives for the next game
                    point.resetPoints(checkPos);
                }

                // Reset positions 
                pacman->setPosition(pacmanStartInitial.x, pacmanStartInitial.y);
                blinky->setPosition(blinkyStartInitial.x, blinkyStartInitial.y);
                pinky->setPosition(pinkyStartInitial.x, pinkyStartInitial.y);
                inky->setPosition(inkyStartInitial.x, inkyStartInitial.y);
                clyde->setPosition(clydeStartInitial.x, clydeStartInitial.y);
                break;
        }

        EndDrawing();
    }

    // Clean up
    for (auto* fig : figures) {
        delete fig;
    }

    CloseWindow();
    return 0;
}





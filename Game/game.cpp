#include "game.h"

Game::Game()
    : board(nullptr), lives(nullptr), fruit(nullptr), checkPos(nullptr), point(nullptr),
      score(0), dotsEaten(0), level(1), ghostSpeed(0.0f),
      startScreen(nullptr), scoreboard(nullptr), userManager(nullptr),
      pacman(nullptr), blinky(nullptr), pinky(nullptr), inky(nullptr), clyde(nullptr), instructions(nullptr),
      state(GameState::StartScreen)
{}

Game::~Game() {
    for (auto* fig : figures) delete fig;
    delete board;
    delete lives;
    delete fruit;
    delete checkPos;
    delete point;
    delete startScreen;
    delete scoreboard;
    delete userManager;
    delete instructions;
    CloseWindow();
}

void Game::init() {
    // Load level, set up window, etc.
    loadLevelData();

    setupWindow();

    initGameObjects();

    initCharacters();

    initMusic();

    resetGameState();

    state = GameState::StartScreen;
}

void Game::run() {
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        switch (state) {
            case GameState::StartScreen:
                startScreen->update();
                startScreen->draw();
                pacman->resetState();

                if (startScreen->isOptionSelected()) {
                    int choice = startScreen->getSelection();
                    if (choice == 0) {
                        state = GameState::UserInput;
                    }
                    else if (choice == 1) {
                        state = GameState::Instruction;
                    } else if (choice == 2) {
                        state = GameState::Scoreboard;
                    } else if (choice == 3) {
                        CloseWindow();
                        return;
                    }
                }
                break;

            case GameState::UserInput:
                score = 0;
                userManager->inputName();
                userManager->drawNameInput();

                if (userManager->isNameEntered() && !userManager->getCurrentUser().empty()) {
                    scoreboard->AddUser(userManager->getCurrentUser());
                    state = GameState::Playing;
                }
                break;

            case GameState::Playing: {
                float deltaTime = GetFrameTime();
                UpdateMusicStream(main_music);
                // Update ghost modes
                GhostController::UpdateAllGhostModes(figures, deltaTime);

                // Update lives immunity timer
                lives->update(deltaTime);

                // --- PacMan Death Animation Handling ---
                if (pacman->getState() == PacManState::Dying) {
                    drawPacmanDeath();
                    updatePacmanDeath();
                    EndDrawing();
                    continue;
                }

                // --- Normal update and collision logic ---
                updatePacmanAndHandleCollisions(deltaTime);

                //Fruit Logic
                handleFruitLogic(deltaTime);

                //Draw the whole Game
                drawGameScene();

                // Draw fruit points popup if active
                if (fruitPopupTimer > 0.0f) {
                    fruitPopupTimer -= GetFrameTime();
                }

                // Level up logic
                if (checkAndHandleLevelUp()){
                    break;
                }
                
                break;
            }

            case GameState::LevelTransition: {
                levelTransitionTimer += GetFrameTime();

                // Draw the board and overlay
                drawLevelTransition();

                if (levelTransitionTimer > LEVEL_TRANSITION_TIME) { 
                 state = GameState::Playing;
                }
                break;
            }

            case GameState::Scoreboard: {
                drawScoreboard();

                if (IsKeyPressed(KEY_ENTER)) {
                    state = GameState::StartScreen;
                }
                break;
            }

            case GameState::GameOver:
                handleGameOver();
                break;

            case GameState::Won:
                handleGameWon();
                break;
            case GameState::Instruction:
             bool backToMenu = false;
            instructions->draw();
            instructions->update(backToMenu);
            if (backToMenu) {
               state = GameState::StartScreen;
            }
            break;
        }

        EndDrawing();
    }
}
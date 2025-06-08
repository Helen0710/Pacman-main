#pragma once
#include "../master_header.h"
#include "raylib.h"

enum class GameState {
    StartScreen,
    Playing,
    Scoreboard,
    GameOver,
    UserInput,
    LevelTransition,
    Won, 
    Instruction 
};

class Game {
public:
    Game();
    ~Game();

    void init();
    void run();

private:
    // All your game state variables as members:
    int screenWidth, screenHeight;
    float levelTransitionTimer = LEVEL_TRANSITION_TIME;
    float fruitPopupTimer = 0.0f;
    int fruitPopupValue = 0;
    int fruitPopupX = 0, fruitPopupY = 0;


    Board* board;
    Lives* lives;
    Fruit* fruit;
    CheckPosition* checkPos;
    Points* point;

    int score, dotsEaten, level;
    float ghostSpeed;

    StartScreen* startScreen;
    Scoreboard* scoreboard;
    Instructions* instructions;
    UserManager* userManager;
    Position pacmanStart, blinkyStart, pinkyStart, inkyStart, clydeStart;
    Position pacmanStartInitial, blinkyStartInitial, pinkyStartInitial, inkyStartInitial, clydeStartInitial;

    std::vector<Figure*> figures;

    PacMan* pacman;
    Ghost* blinky;
    Ghost* pinky;
    Ghost* inky;
    Ghost* clyde;

    Music main_music ;
    Music game_over ;

    GameState state;

    //Drawing Functions
    void drawGameScene();
    void drawLevelTransition();
    void drawScoreboard();
    void drawGameOver();
    void drawPacmanDeath();
    void drawYouWon();

    //Update Logic
    void resetCharacterPositions();
    void resetGhostSpeeds(float speed);
    bool updatePacmanDeath();
    void updatePacmanAndHandleCollisions(float deltaTime);
    void handleFruitLogic(float deltaTime);
    bool checkAndHandleLevelUp();
    void handleGameOver();

    //Init functions
    void loadLevelData();
    void setupWindow();
    void initGameObjects();
    void initCharacters();
    void initMusic();
    void resetGameState();

    void handleGameWon();




};
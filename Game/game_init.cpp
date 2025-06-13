#include "game.h"

void Game::loadLevelData() {
    if (!loadLevelFromFile("../Board/level.txt")) {
        TraceLog(LOG_ERROR, "Failed to load level data from file.");
        exit(-1);
    }
}

void Game::setupWindow() {
    screenWidth = getLevelWidth() * CELL_SIZE;
    screenHeight = getLevelHeight() * CELL_SIZE + TOP_MARGIN + BOTTOM_MARGIN;
    InitWindow(screenWidth, screenHeight, "PacMan - TSA/TSL2429");
    SetTargetFPS(60);

}

void Game::initGameObjects() {
    board = new Board();
    lives = new Lives();
    fruit = new Fruit(0, 0, 0, 0);
    fruit->setActive(false);
    lives->reset();

    checkPos = new CheckPosition(*board);
    point = new Points(*checkPos);

    instructions = new Instructions(screenWidth, screenHeight);
    startScreen = new StartScreen(screenWidth, screenHeight);
    scoreboard = new Scoreboard(screenWidth, screenHeight);
    scoreboard->LoadScores("scores.txt");
    userManager = new UserManager();
}

void Game::initCharacters() {
    board->getStartPositions(pacmanStart, blinkyStart, pinkyStart, inkyStart, clydeStart);
    point->setPoint(pacmanStart.y, pacmanStart.x, false);

    pacmanStartInitial = pacmanStart;
    blinkyStartInitial = blinkyStart;
    pinkyStartInitial  = pinkyStart;
    inkyStartInitial   = inkyStart;
    clydeStartInitial  = clydeStart; 

    pacman = new PacMan(pacmanStart.x, pacmanStart.y, new PlayerController(), PACMAN_SPEED);
    blinky = new Ghost(blinkyStart.x, blinkyStart.y, new BlinkyController(pacman), RED, GHOST_SPEEDS[0]);
    pinky = new Ghost(pinkyStart.x, pinkyStart.y, new PinkyController(pacman), GHOST_PINK, GHOST_SPEEDS[0]);
    inky = new Ghost(inkyStart.x, inkyStart.y, new InkyController(pacman, blinky), GHOST_CYAN, GHOST_SPEEDS[0]);
    clyde = new Ghost(clydeStart.x, clydeStart.y, new ClydeController(pacman), GHOST_ORANGE, GHOST_SPEEDS[0]);

    figures.push_back(pacman);
    figures.push_back(blinky);
    figures.push_back(pinky);
    figures.push_back(inky);
    figures.push_back(clyde);
}

void Game::initMusic(){
    InitAudioDevice();
   main_music = LoadMusicStream("pacman_main.wav");
   game_over = LoadMusicStream("game_over.wav");
   PlayMusicStream(main_music);
   PlayMusicStream(game_over);

}
void Game::resetGameState() {
    score = 0;
    dotsEaten = 0;
    level = 1;
    ghostSpeed = GHOST_SPEEDS[2];
}

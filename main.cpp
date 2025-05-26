#include "master_header.h"
#include "raylib.h"


int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "PacMan - TSA/TSL2429");
    SetTargetFPS(10);


    Board board;
    Points point (board);
    int score = 0; 
    
    StartScreen startScreen (SCREEN_WIDTH, SCREEN_HEIGHT); 
    // Get start positions from the board
    Position pacmanStart, blinkyStart, pinkyStart, inkyStart, clydeStart;
    board.getStartPositions(pacmanStart, blinkyStart, pinkyStart, inkyStart, clydeStart);

    // Create figures
    std::vector<Figure*> figures;
    PacMan* pacman = new PacMan(pacmanStart.x, pacmanStart.y, new PlayerController());
    figures.push_back(pacman);

    Ghost* blinky = new Ghost(blinkyStart.x, blinkyStart.y, new BlinkyController(pacman), RED);
    figures.push_back(blinky);

    Ghost* pinky = new Ghost(pinkyStart.x, pinkyStart.y, new PinkyController(pacman), GHOST_PINK);
    figures.push_back(pinky);

    Ghost* inky = new Ghost(inkyStart.x, inkyStart.y, new InkyController(pacman, blinky), GHOST_CYAN);
    figures.push_back(inky);

    Ghost* clyde = new Ghost(clydeStart.x, clydeStart.y, new ClydeController(pacman), GHOST_ORANGE);
    figures.push_back(clyde);

    bool gameStarted = false; 
    // Main game loop
    while (!WindowShouldClose()) {
        BeginDrawing();

        if (!gameStarted)
        {
            startScreen.update(); 
            startScreen.draw();
            if(startScreen.isOptionSelected())
            {
                int choice = startScreen.getSelection (); 
                if (choice == 0) gameStarted = true ; 
                else if (choice == 3) break; 
            }
        }
        else {

        
        ClearBackground(BLACK);

        // Update all figures
        for (auto* fig : figures) {
            fig->update(board);
        
        
        // Draw board and figures
       

    // Punkte nur bei PacMan prüfen
        if (fig == pacman) {
            int gained = point.checkCollision(pacman->getY(), pacman->getX());
            if (gained > 0) {
                score += gained;
                TraceLog(LOG_INFO, "Score: %d", score);
            }
        }
    }

        board.draw();
        for (auto* fig : figures) {
            fig->draw();
            
        }
        point.draw();}
        //DrawText("PacMan - TSA/TSL2429", 10, 10, 20, RED);
        EndDrawing();
    }

    CloseWindow();
    return 0;
    	
}


/*
int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "PacMan - TSA/TSL24");
    SetTargetFPS(60);

    Board board;

    Position pacmanStart, blinkyStart, pinkyStart, inkyStart, clydeStart;
    board.getStartPositions( pacmanStart, blinkyStart, pinkyStart, inkyStart, clydeStart);

    
    std::vector<Figure*> figures;

    PacMan* pacman = new PacMan(pacmanStart.x, pacmanStart.y, new PlayerController());
    figures.push_back(pacman);

    //Blinky (chaser)
    Ghost* blinky = new Ghost(blinkyStart.x, blinkyStart.y, new BlinkyController(pacman), RED);
    figures.push_back(blinky);

    //Pinky (ambusher)
    Ghost* pinky = new Ghost(pinkyStart.x, pinkyStart.y, new PinkyController(pacman), GHOST_PINK);
    figures.push_back(pinky);

    //Inky (vector)
    Ghost* inky = new Ghost(inkyStart.x, inkyStart.y, new InkyController(pacman, blinky), GHOST_CYAN);
    figures.push_back(inky);

    //Clyde (fleeing)
    Ghost* clyde = new Ghost(clydeStart.x, clydeStart.y, new ClydeController(pacman), GHOST_ORANGE);
    figures.push_back(clyde);


    // Main game loop
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        for (auto* fig : figures){
            fig->update(board);
        }


        board.draw();

        for (auto* fig : figures){
            fig->draw();
        }

        DrawText("PacMan - TSA/TSL24", 10, 10, 20, RED);


        EndDrawing();
    }

    CloseWindow();
    return 0;
}
*/
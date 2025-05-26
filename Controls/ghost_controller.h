#pragma once
#include "controller.h"
#include "../GameObjects/pacman.h"
#include "../utils.h"
#include <vector>
#include <cstdlib>
#include <ctime>

class GhostController : public Controller {
    protected:
        Direction currentDir;
        const PacMan * pacman; // Pointer to PacMan for ghost behavior
        const Figure* blinky; //for Inky

        Direction chooseBestDirection(int gx, int gy, const Board& board, Position target);
        
    public:
        GhostController(const PacMan* pac, const Figure* blinky = nullptr);
        virtual Direction getNextDirection(int gridX, int gridY, const Board& board) override = 0;

};
        

//Blinky, Pinky, Inky, Clyde

// Blinky: Red, always chases and follows PacMan 
class BlinkyController : public GhostController {
    public: 
        BlinkyController(const PacMan* pac);
        Direction getNextDirection(int gx, int gy, const Board& board) override;
};

// Pinky: Pink, 4 cells in front of PacMan
class PinkyController : public GhostController {
    public: 
        PinkyController(const PacMan* pac);
        Direction getNextDirection(int gx, int gy, const Board& board) override;
};

// Inky: Cyan, mirrors Blinky's position
class InkyController : public GhostController {
    public: 
        InkyController(const PacMan* pac, const Figure* blinky);
        Direction getNextDirection(int gx, int gy, const Board& board) override;
};


// Clyde: Orange, alternates between chasing and fleeing from PacMan
class ClydeController : public GhostController {
    public: 
        ClydeController(const PacMan* pac);
        Direction getNextDirection(int gx, int gy, const Board& board) override;
};  
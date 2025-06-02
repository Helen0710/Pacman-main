#pragma once
#include "controller.h"
#include "../GameObjects/pacman.h"
#include "../Board/check_position.h"
#include "../utils.h"
#include <vector>
#include <cstdlib>
#include <ctime>

enum class GhostMode { SCATTER, CHASE};

class GhostController : public Controller {
    protected:
        GhostMode mode = GhostMode::CHASE; // Default mode is CHASE
        float modeTimer = 0.0f;
        Direction currentDir;
        const PacMan * pacman; // Pointer to PacMan for ghost behavior
        const Figure* blinky; //for Inky

        Direction chooseBestDirection(int gx, int gy, const CheckPosition& checkPos, Position target);
        
    public:
        GhostController(const PacMan* pac, const Figure* blinky = nullptr);
        virtual Direction getNextDirection(int gridX, int gridY, const CheckPosition& checkPos) override = 0;
        void updateMode(float deltaTime); // Update the ghost's mode based on time
        GhostMode getMode() const { return mode; } // Get the current mode of the ghost

};
        

//Blinky, Pinky, Inky, Clyde

// Blinky: Red, always chases and follows PacMan 
class BlinkyController : public GhostController {
    public: 
        BlinkyController(const PacMan* pac);
        Direction getNextDirection(int gx, int gy, const CheckPosition& checkPos) override;
};

// Pinky: Pink, 4 cells in front of PacMan
class PinkyController : public GhostController {
    public: 
        PinkyController(const PacMan* pac);
        Direction getNextDirection(int gx, int gy, const CheckPosition& checkPos) override;
};

// Inky: Cyan, mirrors Blinky's position
class InkyController : public GhostController {
    public: 
        InkyController(const PacMan* pac, const Figure* blinky);
        Direction getNextDirection(int gx, int gy, const CheckPosition& checkPos) override;
};


// Clyde: Orange, alternates between chasing and fleeing from PacMan
class ClydeController : public GhostController {
    public: 
        ClydeController(const PacMan* pac);
        Direction getNextDirection(int gx, int gy, const CheckPosition& checkPos) override;
};  
#pragma once
#include "../Board/board.h"
#include "../Board/config.h"
#include "../utils.h"
#include "level.h"


class CheckPosition {
    
    public: 
    CheckPosition(const Board& board);
        
    // Prüft, ob Zelle begehbar ist (z. B. für Bewegung)
    bool isWalkable(int x, int y) const;
    bool isWalkableForPacman(int x, int y) const;
    bool isWalkableForGhost(int x, int y) const;
    bool isWall(int x, int y) const;
    bool isCoin(int x, int y) const;
    bool isPortal(int x, int y) const;


    //bool isValidPosition(int y, int x) const;

    private:
        char grid[LEVEL_HEIGHT][LEVEL_WIDTH + 1]; // +1 for null terminator
       
};
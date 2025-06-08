#pragma once
#include "../Board/board.h"
#include "../config.h"
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
    bool isPortal(int x, int y) const;


    //bool isValidPosition(int y, int x) const;

    private:
        std::vector<std::vector<char>> grid; // 2D-Array als Zeichenkette, z.B. "##########"
        int wrapX(int x) const;
        int wrapY(int y) const;
       
};
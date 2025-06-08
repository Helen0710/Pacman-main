
#pragma once

#include <vector>
#include "../utils.h"    // enthält Position struct
#include "../config.h"  // enthält BOARD_WIDTH, BOARD_HEIGHT
#include "level.h"   // enthält LEVEL_HEIGHT, LEVEL_WIDTH und levelData
#include "raylib.h"            // falls draw() Raylib nutzt
#include <string>    // für std::string


class Board {
public:
    Board();  // Initialisiert das Grid mit EMPTY

    // Zeichnet das Spielfeld
    void draw() const;
    char getCharAt(int y, int x) const;

 
    void getStartPositions(Position& pacmanStart,
                        Position& blinkyStart,
                        Position& pinkyStart,
                        Position& inkyStart,
                        Position& clydeStart);

private:
    //std::vector<std::vector<CellType>> grid;
    std::vector<std::string> grid;  // Spielfeld als 2D-Array von Zeichen
};

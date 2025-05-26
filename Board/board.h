
#pragma once

#include <vector>
#include "../utils.h"    // enthält Position struct
#include "config.h"  // enthält BOARD_WIDTH, BOARD_HEIGHT
#include "raylib.h"            // falls draw() Raylib nutzt

// Zelltypen im Spielfeld
enum CellType {
    EMPTY = ' ',
    WALL = '#',
    COIN = '.',

    // Optional: POWERUP, GHOST_DOOR, etc.
};

class Board {
public:
    Board();  // Initialisiert das Grid mit EMPTY

    // Lädt das Level aus levelData[] und setzt Startpositionen
    /*void loadFromLevelData(const char* levelData[], int height,
                           Position& pacmanStart,
                           Position& blinkyStart,
                           Position& pinkyStart,
                           Position& inkyStart,
                           Position& clydeStart);
                           */

    // Gibt den Zelltyp an einer Position zurück
    //CellType getCell(int x, int y) const;

    bool isWall(int x, int y) const;
    bool isCoin(int x, int y) const;


    // Zeichnet das Spielfeld
    void draw() const;

    // Prüft, ob Zelle begehbar ist (z. B. für Bewegung)
    bool isWalkable(int x, int y) const;
    bool isWalkableForPacman(int x, int y) const;
    bool isWalkableForGhost(int x, int y) const;

    bool isValidPosition(int y, int x) const;

    void getStartPositions(Position& pacmanStart,
                        Position& blinkyStart,
                        Position& pinkyStart,
                        Position& inkyStart,
                        Position& clydeStart);

private:
    //std::vector<std::vector<CellType>> grid;
    char grid[LEVEL_HEIGHT][LEVEL_WIDTH + 1]; // +1 for null terminator 
};
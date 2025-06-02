#include "check_position.h"
#include <iostream>

// Konstruktor: Initialisiert das Grid mit den Werten aus dem Board
CheckPosition::CheckPosition(const Board& board) {
    for (int y = 0; y < LEVEL_HEIGHT; ++y) {
        for (int x = 0; x < LEVEL_WIDTH +1; ++x) {
            grid[y][x] = board.getCharAt(y, x);
        }
    }
}

// Prüft, ob Position begehbar ist
bool CheckPosition::isWalkable(int x, int y) const {
    char title = grid[y][x];
    return (title == EMPTY || title == COIN || title == PACMAN || title == BLINKY || title == PINKY || title == INKY || title == CLYDE || title == TUNNEL || title == PORTAL);
}

bool CheckPosition::isWall(int x, int y) const {
    if(x < 0 || x >= LEVEL_WIDTH || y < 0 || y >= LEVEL_HEIGHT) {
        return true; // Randbehandlung: außerhalb = keine Wand
    }
    return grid[y][x] == WALL;
}

bool CheckPosition::isCoin(int x, int y) const {
    return grid[y][x] == COIN;
}

// For PacMan
bool CheckPosition::isWalkableForPacman(int x, int y) const {
    // std::cout << "CheckPosition: isWalkableForPacman called at (" << x << ", " << y << ")" << std::endl;
    return grid[y][x] == EMPTY || grid[y][x] == COIN || grid[y][x] == PACMAN || grid[y][x] == PORTAL; // PacMan can't walk on TUNNEL
   
}

// For Ghosts
bool CheckPosition::isWalkableForGhost(int x, int y) const {
    char title = grid[y][x];
    //TraceLog(LOG_INFO, "isWalkableForGhost: x=%d, y=%d, tile=%c", x, y, title);
    return title == EMPTY || title == COIN || title == TUNNEL || title == PORTAL || title == PACMAN || title == BLINKY || title == PINKY || title == INKY || title == CLYDE;
}


bool CheckPosition::isPortal(int x, int y) const {
    return grid[y][x] == PORTAL;
}
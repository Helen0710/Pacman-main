#include "check_position.h"
#include <iostream>

// Konstruktor: Initialisiert das Grid mit den Werten aus dem Board
CheckPosition::CheckPosition(const Board& board) {
    grid.resize(getLevelHeight(), std::vector<char>(getLevelWidth()));
    for (int y = 0; y < getLevelHeight(); ++y) {
        const char* row = getLevelRow(y);
        for (int x = 0; x < getLevelWidth(); ++x) {
            grid[wrapY(y)][wrapX(x)] = row[x];
    }
}
}

// Prüft, ob Position begehbar ist
bool CheckPosition::isWalkable(int x, int y) const {
    char title = grid[wrapY(y)][wrapX(x)];
    return (title == EMPTY || title == COIN || title == PACMAN || title == BLINKY || title == PINKY || title == INKY || title == CLYDE || title == TUNNEL || title == PORTAL);
}

bool CheckPosition::isWall(int x, int y) const {
    char title = grid[wrapY(y)][wrapX(x)];
    if(x < 0 || x >= getLevelWidth() || y < 0 || y >= getLevelHeight()) {
        return true; // Randbehandlung: außerhalb = keine Wand
    }
    return title == WALL;
}

// For PacMan
bool CheckPosition::isWalkableForPacman(int x, int y) const {
    char title = grid[wrapY(y)][wrapX(x)];
    // std::cout << "CheckPosition: isWalkableForPacman called at (" << x << ", " << y << ")" << std::endl;
    return title == EMPTY || title == COIN || title == PACMAN || title == PORTAL; // PacMan can't walk on TUNNEL
   
}

// For Ghosts
bool CheckPosition::isWalkableForGhost(int x, int y) const {
    char title = grid[wrapY(y)][wrapX(x)];
    //TraceLog(LOG_INFO, "isWalkableForGhost: x=%d, y=%d, tile=%c", x, y, title);
    return title == EMPTY || title == COIN || title == TUNNEL || title == PORTAL || title == PACMAN || title == BLINKY || title == PINKY || title == INKY || title == CLYDE;
}


bool CheckPosition::isPortal(int x, int y) const {
    return grid[wrapY(y)][wrapX(x)] == PORTAL;
}

int CheckPosition::wrapX(int x) const {
    int w = getLevelWidth();
    return (x % w + w) % w; // Wrap around horizontally
}

int CheckPosition::wrapY(int y) const {
    int h = getLevelHeight();
    return (y % h + h) % h; // Wrap around vertically
}
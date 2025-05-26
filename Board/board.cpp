#include "board.h"
#include "level.h"  // enthält levelData
#include "raylib.h"

// Konstruktor: Initialisiert das Spielfeld with EMPTY
Board::Board() {
    for (int y = 0; y < LEVEL_HEIGHT; ++y) {
        for (int x = 0; x < LEVEL_WIDTH; ++x) {
            grid[y][x] = levelData[y][x];
        }
        grid[y][LEVEL_WIDTH] = '\0'; // Optional, for C-string compatibility
    }
}



// Prüft, ob Position begehbar ist
bool Board::isWalkable(int x, int y) const {
    char title = grid[y][x];
    return (title == ' ' || title == '.' || title == 'P' || title == 'B' || title == 'Y' || title == 'I' || title == 'C');
}

bool Board::isValidPosition(int y, int x) const { 
    return grid[y][x] != WALL;
}

bool Board::isWall(int x, int y) const {
    if(x < 0 || x >= LEVEL_WIDTH || y < 0 || y >= LEVEL_HEIGHT) {
        return true; // Randbehandlung: außerhalb = keine Wand
    }
    return grid[y][x] == '#';
}

bool Board::isCoin(int x, int y) const {
    return grid[y][x] == '.';
}

void Board::getStartPositions(Position& pacmanStart,
                              Position& blinkyStart,
                              Position& pinkyStart,
                              Position& inkyStart,
                              Position& clydeStart) {
    for (int row = 0; row < LEVEL_HEIGHT; ++row) {
        for (int col = 0; col < LEVEL_WIDTH; ++col) {
            char tile = grid[row][col];
            switch (tile) {
                case 'P':
                    pacmanStart = {col, row};
                    grid[row][col] = '.'; // Now safe to modify!
                    break;
                case 'B':
                    blinkyStart = {col, row};
                    grid[row][col] = '.';
                    break;
                case 'Y':
                    pinkyStart = {col, row};
                    grid[row][col] = '.';
                    break;
                case 'I':
                    inkyStart = {col, row};
                    grid[row][col] = '.';
                    break;
                case 'C':
                    clydeStart = {col, row};
                    grid[row][col] = '.';
                    break;
            }
        }
    }
                                    

}

// Zeichnet das Spielfeld
void Board::draw() const {
    for (int y = 0; y < LEVEL_HEIGHT; ++y) {
        for (int x = 0; x < LEVEL_WIDTH; ++x) {
            int px = x * CELL_SIZE;
            int py = y * CELL_SIZE;

            switch (levelData[y][x]) {
                case '#':
                    DrawRectangle(px, py, CELL_SIZE, CELL_SIZE, DARKBLUE);
                    break;
                case '.':
                    DrawCircle(px + CELL_SIZE / 2, py + CELL_SIZE / 2, CELL_SIZE / 6, YELLOW);
                    break;
                default:
                    break;
            }
        }
    }
}

// For PacMan
bool Board::isWalkableForPacman(int x, int y) const {
    return grid[y][x] == ' ' || grid[y][x] == '.'; // PacMan can't walk on TUNNEL
}

// For Ghosts
bool Board::isWalkableForGhost(int x, int y) const {
    return grid[y][x] == ' ' || grid[y][x] == '.' || grid[y][x] == TUNNEL;
}





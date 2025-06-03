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

char Board::getCharAt(int y, int x) const {
    if (y >= 0 && y < LEVEL_HEIGHT && x >= 0 && x < LEVEL_WIDTH) {
        return grid[y][x];
    }
    return '#'; // Return '#' for out-of-bounds access, indicating a wall
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
                case PACMAN:
                    pacmanStart = {col, row};
                    grid[row][col] = '.'; // Now safe to modify!
                    break;
                case BLINKY:
                    blinkyStart = {col, row};
                    grid[row][col] = '.';
                    break;
                case PINKY:
                    pinkyStart = {col, row};
                    grid[row][col] = '.';
                    break;
                case INKY:
                    inkyStart = {col, row};
                    grid[row][col] = '.';
                    break;
                case CLYDE:
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
            int py = y * CELL_SIZE + TOP_MARGIN; // Add top margin for scoreboard

            switch (levelData[y][x]) {
                case WALL:
                    DrawRectangle(px, py, CELL_SIZE, CELL_SIZE, DARKBLUE);
                    break;
                case COIN:
                    DrawCircle(px + CELL_SIZE / 2, py + CELL_SIZE / 2, CELL_SIZE / 6, YELLOW);
                    break;
                case TUNNEL:
                    DrawRectangle(px, py + CELL_SIZE / 2 - 4, CELL_SIZE, 8, PINK);
                    break;
                default:
                    break;
            }
        }
    }
}

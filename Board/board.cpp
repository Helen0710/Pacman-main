#include "board.h"
#include "level.h"
#include "raylib.h"
#include <vector>
#include <string>

// Konstruktor: Initialisiert das Spielfeld mit den geladenen Daten
Board::Board() {
    int h = getLevelHeight();
    int w = getLevelWidth();
    grid.resize(h);
    for (int y = 0; y < h; ++y) {
        grid[y] = getLevelRow(y); // Kopiert die Zeile als std::string
    }
}

char Board::getCharAt(int y, int x) const {
    int h = getLevelHeight();
    int w = getLevelWidth();
    if (y >= 0 && y < h && x >= 0 && x < w) {
        return grid[y][x];
    }
    return '#'; // Out-of-bounds = Wand
}

void Board::getStartPositions(Position& pacmanStart,
                              Position& blinkyStart,
                              Position& pinkyStart,
                              Position& inkyStart,
                              Position& clydeStart) {
    int h = getLevelHeight();
    int w = getLevelWidth();
    for (int row = 0; row < h; ++row) {
        for (int col = 0; col < w; ++col) {
            char tile = grid[row][col];
            switch (tile) {
                case PACMAN:
                    pacmanStart = {col, row};
                    grid[row][col] = '.'; // Feld leeren
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
    int h = getLevelHeight();
    int w = getLevelWidth();
    for (int y = 0; y < h; ++y) {
        const std::string& row = grid[y];
        for (int x = 0; x < w; ++x) {
            char tile = row[x];
            int px = x * CELL_SIZE;
            int py = y * CELL_SIZE + TOP_MARGIN;

            switch (tile) {
                case WALL:
                    DrawRectangle(px, py, CELL_SIZE, CELL_SIZE, DARKBLUE);
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


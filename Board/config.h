#pragma once

#include "level.h"

const int CELL_SIZE = 20; // Size of each cell in pixels
const int SCREEN_WIDTH = LEVEL_WIDTH * CELL_SIZE; // Width of the window in pixels
const int SCREEN_HEIGHT = LEVEL_HEIGHT* CELL_SIZE; // Height of the window in pixels

#define GHOST_PINK Color{ 255, 192, 203, 255 } // Pink color for Pinky 
#define GHOST_ORANGE Color{ 255, 165, 0, 255 } // Orange color for Clyde
#define GHOST_CYAN Color{ 0, 255, 255, 255 } // Cyan color for Inky


constexpr char TUNNEL = '-'; // Tunnel character


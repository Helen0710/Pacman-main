#pragma once

#include "level.h"

const int CELL_SIZE = 40; // Size of each cell in pixels
const int SCREEN_WIDTH = LEVEL_WIDTH * CELL_SIZE; // Width of the window in pixels
const int SCREEN_HEIGHT = LEVEL_HEIGHT* CELL_SIZE; // Height of the window in pixels

const float GHOST_SPEED = 2.0f; // Speed of the ghosts in seconds per move must be a divisor of cell_size
const float PACMAN_SPEED = 4.0f; // Speed of PacMan in seconds per move must be a divisor of cell_size

const float GHOST_SCATTER_TIME = 8.0; // Time in seconds for scatter mode
const float GHOST_CHASE_TIME = 20.0f; // Time in seconds for chase mode


#define GHOST_PINK Color{ 255, 192, 203, 255 } // Pink color for Pinky 
#define GHOST_ORANGE Color{ 255, 165, 0, 255 } // Orange color for Clyde
#define GHOST_CYAN Color{ 0, 255, 255, 255 } // Cyan color for Inky
#define LIGHTBLUE Color{ 173, 216, 230, 255 } // Light blue color for ghost eyes


constexpr char TUNNEL = '-'; // Tunnel character
constexpr char WALL = '#'; // Wall character
constexpr char PORTAL = '!'; // Portal character
constexpr char EMPTY = ' '; // Empty space character
constexpr char PACMAN = 'P'; // PacMan character
constexpr char BLINKY = 'B'; // Blinky character
constexpr char PINKY = 'Y'; // Pinky character
constexpr char INKY = 'I'; // Inky character
constexpr char CLYDE = 'C'; // Clyde character
constexpr char COIN = '.'; // Coin character



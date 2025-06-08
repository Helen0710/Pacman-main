#pragma once

#include "Board/level.h"

const int CELL_SIZE = 32; // Size of each cell in pixels
constexpr int TOP_MARGIN = 60; // Margin at the top of the screen for the scoreboard
constexpr int BOTTOM_MARGIN = 60; // Margin at the bottom of the screen for the scoreboard
const int SCREEN_WIDTH = getLevelWidth() * CELL_SIZE;// Width of the window in pixels
const int SCREEN_HEIGHT = getLevelHeight() * CELL_SIZE + TOP_MARGIN + BOTTOM_MARGIN; // Height of the window in pixels


const float GHOST_SPEEDS[] = {2.0f, 2.0f, 4.0f, 8.0f}; // Speed of the ghosts in seconds per move must be a divisor of cell_size
const float NUM_SPEEDS = sizeof(GHOST_SPEEDS) / sizeof(GHOST_SPEEDS[0]); // Number of different ghost speeds
const float PACMAN_SPEED = 4.0f; // Speed of PacMan in seconds per move must be a divisor of cell_size

const float LEVEL_TRANSITION_TIME = 1.0f; // Time in seconds for level transition

const float GHOST_SCATTER_TIME = 5.0f; // Time in seconds for scatter mode
const float GHOST_CHASE_TIME = 15.0f; // Time in seconds for chase mode

const float MAX_LIVES = 3; // Maximum number of lives for PacMan


#define GHOST_PINK Color{ 255, 192, 203, 255 } // Pink color for Pinky 
#define GHOST_ORANGE Color{ 255, 165, 0, 255 } // Orange color for Clyde
#define GHOST_CYAN Color{ 0, 255, 255, 255 } // Cyan color for Inky
#define LIGHTBLUE Color{ 173, 216, 230, 255 } // Light blue color for ghost eyes

#define GHOST_HOUSE_LEFT 12
#define GHOST_HOUSE_RIGHT 17
#define GHOST_HOUSE_TOP 11
#define GHOST_HOUSE_BOTTOM 13
#define PORTAL_ROW 13


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



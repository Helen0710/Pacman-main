#pragma once
#include "../Board/config.h"
#include "../utils.h"
#include "../Controls/controller.h"

class Board;

class Figure {
    protected:
        float px, py;
        int gridX, gridY; // Position in the grid
  

        Direction currentDir; // Current direction of the figure

        Controller* controller; // Pointer to the controller for the figure
        
        

    public:
        Figure(int startX, int startY, Controller* ctrl);
        virtual ~Figure(); // Virtual destructor for proper cleanup

        virtual void update(const Board& board); 
        virtual void draw() const = 0; // Pure virtual function for drawing the figure
        virtual bool canMoveTo(const Board& board, int x, int y) const = 0; // Check if the figure can move to a specific position

        int getX() const; // Get the x position in the grid
        int getY() const; // Get the y position in the grid

        float getPx() const; // Get the x position in pixels
        float getPy() const; // Get the y position in pixels

        Direction getCurrentDir() const; // Get the current direction of the figure
};

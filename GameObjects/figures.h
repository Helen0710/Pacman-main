#pragma once
#include "../config.h"
#include "../utils.h"
#include "../Controls/controller.h"
#include "../Board/check_position.h" 
#include "game_objects.h"   

class CheckPosition; // Forward declaration to avoid circular dependency


class Figure: public GameObject {
    protected:
        float px, py;
        int gridX, gridY; // Position in the grid
        float speed; // Speed of the figure in pixels per second
  

        Direction currentDir, desiredDir; // Current direction of the figure

        Controller* controller; // Pointer to the controller for the figure

        

    public:
        Figure(int startX, int startY, Controller* ctrl, float spd);
        virtual ~Figure(); // Virtual destructor for proper cleanup

        virtual void update(const CheckPosition& checkPos) = 0; 
        virtual bool canMoveTo(const CheckPosition& checkPos, int x, int y) const = 0; // Check if the figure can move to a specific position

        int getX() const override; // Get the x position in the grid
        int getY() const override; // Get the y position in the grid

        float getPx() const override; // Get the x position in pixels
        float getPy() const override; // Get the y position in pixels

        void move(const CheckPosition& checkPos); // Move the figure based on the controller's input and check position

        Direction getCurrentDir() const; // Get the current direction of the figure
        bool nearCenterOfCell() const; // Check if the figure is at the center of a cell
        void setPosition(int x, int y); // Set the position of the figure in the grid
};

#pragma once

class GameObject {
    public:
        virtual ~GameObject() = default; // Virtual destructor for proper cleanup
       
        virtual void draw() const = 0; // Draw method to render the object
        
        virtual int getX() const = 0; // Get the x position in the grid
        virtual int getY() const = 0; // Get the y position in the grid
        virtual float getPx() const = 0; // Get the x position in pixels
        virtual float getPy() const = 0; // Get the y position in pixels


};
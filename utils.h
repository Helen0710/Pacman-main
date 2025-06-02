#pragma once

struct Position {
    int x, y;
};

struct Direction {
    int dx, dy;
    Direction(int x = 0, int y = 0) : dx(x), dy(y) {}

    bool operator==(const Direction& other) const {
        return dx == other.dx && dy == other.dy;
    }

    bool operator!=(const Direction& other) const {
        return !(*this == other);
    }

    bool isNone() const {
        return dx == 0 && dy == 0;
    }

    
    static const Direction NONE;
    static const Direction UP;
    static const Direction DOWN;
    static const Direction LEFT;
    static const Direction RIGHT;

    int toEnum() const {
        if (*this == UP) return 0; // UP
        if (*this == DOWN) return 1;  // DOWN
        if (*this == LEFT) return 2; // LEFT
        if (*this == RIGHT) return 3;  // RIGHT
        return -1; // NONE or invalid
    }
    
};




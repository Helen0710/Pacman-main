#pragma once
#include <vector>
#include "../Board/board.h"
#include "../Board/check_position.h"


class Points {
private:
    std::vector<std::vector<bool>> points;

public:
    Points(const CheckPosition& checkPos);
    void draw() const;
    bool hasRemainingPoints() const;

    //Accessor for points
    bool getPoint(int y, int x) const;
    void setPoint(int y, int x, bool value);
    void resetPoints(const CheckPosition& checkPos); // Reset all points based on the current board state
};

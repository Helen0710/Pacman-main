#pragma once
#include <vector>
#include "../Board/board.h"

class Points {
private:
    std::vector<std::vector<bool>> points;

public:
    Points(const Board& board);
    void draw() const;
    int checkCollision(int y, int x);
    bool hasRemainingPoints() const;
};

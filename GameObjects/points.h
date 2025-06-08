#pragma once
#include "raylib.h"
#include "items.h"
#include "../config.h"
#include "../Board/check_position.h"
#include <vector>

class Points : public Item {
public:
    Points(const CheckPosition& checkPos); // <-- match cpp!
    void draw() const override;
    bool hasRemainingPoints() const;
    bool getPoint(int y, int x) const;
    void setPoint(int y, int x, bool value);
    void resetPoints(const CheckPosition& checkPos);

private:
    std::vector<std::vector<bool>> points;
    bool isPointAllowed(int x, int y) const;
    int wrapX(int x) const;
    int wrapY(int y) const;
};

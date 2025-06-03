#include "items.h"
#include "raylib.h"

Item::Item(int startX, int startY, Controller* ctrl)
    : x(startX), y(startY), px(startX * CELL_SIZE), py(startY * CELL_SIZE), controller(ctrl) {}

int Item::getX() const {
    return x;
}
int Item::getY() const {
    return y;
}
float Item::getPx() const {
    return px;
}
float Item::getPy() const {
    return py;
}
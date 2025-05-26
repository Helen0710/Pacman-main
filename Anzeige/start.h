#pragma once
#include "raylib.h"
#include <string>
#include <vector>

class StartScreen {
private:
    std::vector<std::string> menuItems;
    int selectedIndex;
    int screenWidth;
    int screenHeight;

public:
    StartScreen(int width, int height);
    void update();
    void draw() const;
    int getSelection() const;
    bool isOptionSelected() const;
    void DrawStartScreen(bool showPrompt = true);
};

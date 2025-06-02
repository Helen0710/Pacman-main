#pragma once
#include "raylib.h"
#include <vector>
#include <string>
#include <unordered_map>

class Scoreboard {
private:
    std::vector<std::string> menuItems;
    int screenWidth;
    int screenHeight;
    std::unordered_map<std::string, int> scores;
    std::string currentUser;
    bool showInput = true;
    char nameBuffer[32] = { 0 };
public: 
    Scoreboard(int width, int height);
    void LoadScores(const std::string& filename);
    void SaveScores(const std::string& filename);
    void AddUser(const std::string& username);
    void IncreaseScore(const std::string& username, int amount);
    int GetScore(const std::string& username);
    void drawScore();
     


};

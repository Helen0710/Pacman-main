#pragma once
#include "raylib.h"

#include "../config.h"

#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

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
   void SetScores(const std::vector<std::pair<std::string, int>>& newScores);
    void drawScore();
     


};
#include "scoreboard.h"
#include "raylib.h"
#include "config.h"
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <cstring>

Scoreboard::Scoreboard(int width, int height)
    : screenWidth(width), screenHeight(height) {
    menuItems = {"Start Game", "Load Scores", "Save Scores", "Exit"};
    currentUser = "";
    showInput = true;
    memset(nameBuffer, 0, sizeof(nameBuffer)); // Initialize nameBuffer to empty
}

void Scoreboard::LoadScores(const std::string& filename) {
    scores.clear();
    std::ofstream datei (filename);
    if (!datei) {
        TraceLog(LOG_ERROR, "Could not open file %s for reading", filename.c_str());
        return;
    }
    std::ifstream in(filename);
    std::string line;
    while (std::getline(in, line)) {
        std::istringstream ss(line);
        std::string name;
        int score;
        if (ss >> name >> score) {
            scores[name] = score;
        }
    }
}

void Scoreboard::SaveScores(const std::string& filename) {
    std::ofstream out(filename);
    for (auto& [name, score] : scores) {
        out << name << " " << score << "\n";
    }
}

void Scoreboard::AddUser(const std::string& username) {
    currentUser = username;
    if (scores.find(username) == scores.end()) {
        scores[username] = 0;
    }
}

void Scoreboard::IncreaseScore(const std::string& username, int amount) {
    scores[username] += amount;
}

int Scoreboard::GetScore(const std::string& username) {
    return scores[username];
}

void Scoreboard::drawScore() {
    ClearBackground(BLACK);

    DrawText("Scoreboard", 20, 20, 30, WHITE);

    int y = 60;
    for (auto& [name, score] : scores) {
        DrawText(TextFormat("%s: %d", name.c_str(), score), 20, y, 20, YELLOW);
        y += 30;
    }

    if (showInput) {
        DrawText("Enter name:", 20, y + 10, 20, WHITE);
        DrawText(nameBuffer, 200, y + 10, 20, WHITE);
        if (IsKeyPressed(KEY_ENTER)) {
            AddUser(nameBuffer);
            showInput = false;
        } else {
            int key = GetCharPressed();
            if (key > 0 && strlen(nameBuffer) < 31) {
                int len = strlen(nameBuffer);
                nameBuffer[len] = (char)key;
                nameBuffer[len + 1] = '\0';
            }
            if (IsKeyPressed(KEY_BACKSPACE)) {
                int len = strlen(nameBuffer);
                if (len > 0) nameBuffer[len - 1] = '\0';
            }
        }
    }

}

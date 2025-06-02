#include "UserManager.h"
#include "raylib.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstring>

UserManager::UserManager() {
    nameBuffer[0] = '\0';
    nameEntered = false;
}

void UserManager::inputName() {
    if (!nameEntered) {
        int key = GetCharPressed();

        while (key > 0) {
            if (std::strlen(nameBuffer) < sizeof(nameBuffer) - 1) {
                int len = std::strlen(nameBuffer);
                nameBuffer[len] = (char)key;
                nameBuffer[len + 1] = '\0';
            }
            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE)) {
            int len = std::strlen(nameBuffer);
            if (len > 0) nameBuffer[len - 1] = '\0';
        }

        if (IsKeyPressed(KEY_ENTER) && std::strlen(nameBuffer) > 0) {
            currentUser = std::string(nameBuffer);
            nameEntered = true;
        }
    }
}

std::string UserManager::getCurrentUser() const {
    return currentUser;
}

bool UserManager::isNameEntered() const {
    return nameEntered;
}

void UserManager::drawNameInput() {
    DrawText("Bitte gib deinen Namen ein und drücke ENTER:", 100, 200, 20, WHITE);
    DrawText(nameBuffer, 100, 250, 30, YELLOW);
}

void UserManager::saveScore(int score, const std::string& filename) {
    std::ofstream file(filename, std::ios::app); // append mode
    if (file.is_open()) {
        file << currentUser << " " << score << "\n";
        file.close();
    }
}

std::vector<std::pair<std::string, int>> UserManager::loadScores(const std::string& filename) {
    std::vector<std::pair<std::string, int>> scores;
    std::ifstream file(filename);
    std::string name;
    int score;

    while (file >> name >> score) {
        scores.emplace_back(name, score);
    }

    // Optional: Sortiere nach Score absteigend
    std::sort(scores.begin(), scores.end(), [](auto& a, auto& b) {
        return a.second > b.second;
    });

    return scores;
}

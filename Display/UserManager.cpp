#include "UserManager.h"
#include "raylib.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstring>
#include <map>

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
    std::map<std::string, int> bestScores;

    // Bestehende Scores einlesen
    std::ifstream inFile(filename);
    std::string name;
    int existingScore;
    while (inFile >> name >> existingScore) {
        bestScores[name] = std::max(bestScores[name], existingScore);
    }
    inFile.close();

    // Aktuellen Score speichern, wenn er besser ist
    if (score > bestScores[currentUser]) {
        bestScores[currentUser] = score;
    }

    // Neue Liste speichern
    std::ofstream outFile(filename, std::ios::trunc); // Überschreiben
    for (const auto& pair : bestScores) {
        outFile << pair.first << " " << pair.second << "\n";
    }
}




void UserManager::reset() {
    currentUser.clear();
    nameEntered = false;
}



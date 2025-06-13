#include "scoreboard.h"


Scoreboard::Scoreboard(int width, int height)
    : screenWidth(width), screenHeight(height) {
    menuItems = {"Start Game", "Load Scores", "Save Scores", "Exit"};
    currentUser = "";
    showInput = true;
    memset(nameBuffer, 0, sizeof(nameBuffer)); // Initialize nameBuffer to empty
}

void Scoreboard::LoadScores(const std::string& filename) {
    scores.clear();
    std::ifstream in(filename);
    if (!in) {
        TraceLog(LOG_ERROR, "Could not open file %s for reading", filename.c_str());
        return;
    }
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

    // Sortiere nach Punktzahl absteigend
    std::vector<std::pair<std::string, int>> sortedScores(scores.begin(), scores.end());
    std::sort(sortedScores.begin(), sortedScores.end(),
              [](const auto& a, const auto& b) { return a.second > b.second; });

    int y = 60;
    int rank = 1;
    for (const auto& [name, score] : sortedScores) {
        Color color = YELLOW;
        std::string prefix;

        switch (rank) {
            case 1: prefix = "🥇 "; color = GOLD; break;
            case 2: prefix = "🥈 "; color = LIGHTGRAY; break;
            case 3: prefix = "🥉 "; color = ORANGE; break;
            default: prefix = std::to_string(rank) + ". "; break;
        }

        std::string display = prefix + name + ": " + std::to_string(score);
        if (name == currentUser) {
            DrawText(display.c_str(), 20, y, 22, GREEN); // aktueller Spieler grün markieren
        } else {
            DrawText(display.c_str(), 20, y, 20, color);
        }

        y += 30;
        ++rank;
    }

}
void Scoreboard::SetScores(const std::vector<std::pair<std::string, int>>& newScores) {
    scores.clear();
    for (const auto& [name, score] : newScores) {
        scores[name] = score;
    }
}
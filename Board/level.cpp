#include "level.h"
#include <vector>
#include <string>
#include <fstream>
#include <cstring>
#include <algorithm>

std::vector<std::string> levelDataVec;
int levelWidth = 0;
int levelHeight = 0;

bool loadLevelFromFile(const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    std::vector<std::string> lines;
    std::string line;
    int maxWidth = 0;
    while (std::getline(file, line)) {
        // Remove trailing \r (for Windows files)
        if (!line.empty() && line.back() == '\r') line.pop_back();
        lines.push_back(line);
        maxWidth = std::max(maxWidth, (int)line.length());
    }
    file.close();

    if (lines.empty()) return false;

    // Check all lines have the same length
    for (const auto& l : lines) {
        if ((int)l.length() != maxWidth) {
            // Malformed level: not all lines same length
            return false;
        }
    }

    // Store
    levelDataVec = lines;
    levelHeight = (int)lines.size();
    levelWidth = maxWidth;
    return true;
}

int getLevelHeight() {
    return levelHeight;
}

int getLevelWidth() {
    return levelWidth;
}

const char* getLevelRow(int row) {
    if (row < 0 || row >= levelHeight) return nullptr;
    return levelDataVec[row].c_str();
}



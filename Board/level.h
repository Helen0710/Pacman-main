#pragma once

#include <string>
#include <vector>


bool loadLevelFromFile(const char* filename);
int getLevelHeight();
int getLevelWidth();
const char* getLevelRow(int row);


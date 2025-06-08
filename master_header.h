#pragma once

#include "raylib.h"
#include "Board/board.h"
#include "Board/level.h"
#include "Board/check_position.h"

#include "GameObjects/pacman.h"
#include "GameObjects/ghost.h"
#include "GameObjects/figures.h"
#include "GameObjects/game_objects.h"
#include "GameObjects/points.h"
#include "GameObjects/items.h"
#include "GameObjects/lives.h"
#include "GameObjects/fruits.h"

#include "Controls/player_controller.h"
#include "Controls/controller.h"
#include "Controls/ghost_controller.h"
#include "Controls/check_collision.h"

#include "Display/start_screen.h"
#include "Display/scoreBoard.h"
#include "Display/UserManager.h"
#include "Display/instructions.h"

#include "config.h"

#include <vector>
#include <math.h>
#include <algorithm>
#include <iostream>
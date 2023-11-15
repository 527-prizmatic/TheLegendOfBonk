#pragma once
#include <stdio.h>
#include <stdlib.h>

#include "tools.h"
#include "map.h"

#define SAVE_PATH "..\\saves\\"

void save_map(char _map[H_MAP_T][W_MAP_T], sfVector2f _player_pos, int _inv[4]);
void load_map(char _map[H_MAP_T][W_MAP_T], sfVector2f* _player_pos, int _inv[4]);
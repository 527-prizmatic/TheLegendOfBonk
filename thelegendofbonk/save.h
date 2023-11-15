#pragma once
#include <stdio.h>
#include <stdlib.h>

#include "tools.h"
#include "map.h"

#define SAVE_PATH "..\\saves\\"

/* Saves a few data to an external save file for future retrieval.
*  \param _map - A tilemap
*  \param _player_pos - The player character's in-world coordinates
*  \param _inv - The player character's inventory */
void save_map(char _map[H_MAP_T][W_MAP_T], sfVector2f _player_pos, int _inv[4]);


/* Loads a few data from an external save file.
*  \param _map - A tilemap
*  \param _player_pos - A pointer to the player character's in-world coordinates
*  \param _inv - The player character's inventory */
void load_map(char _map[H_MAP_T][W_MAP_T], sfVector2f* _player_pos, int _inv[4]);
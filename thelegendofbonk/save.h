#pragma once
#include <stdio.h>
#include <stdlib.h>

#include "tools.h"
#include "map.h"
#include "SFML/Audio.h"

#define SAVE_PATH "..\\saves\\"

/// Saves data to an external save file for future retrieval, including the game world, the player's coordinates and inventory, and the music volume.
/// \param _map - A tilemap
/// \param _props - A propmap
/// \param _player_pos - The player character's in-world coordinates
/// \param _inv - The player character's inventory
/// \param _inv - A BGM object
void save_map(char _map[H_MAP_T][W_MAP_T], char _props[H_MAP_T][W_MAP_T], sfVector2f _player_pos, int _inv[4], sfMusic* _mus);

/// Loads data from an external save file, including the game world, the player's coordinates and inventory, and the music volume.
/// \param _map - A tilemap
/// \param _props - A propmap
/// \param _player_pos - A pointer to the player character's in-world coordinates
/// \param _inv - The player character's inventory
/// \param _inv - A pointer to a BGM object
void load_map(char _map[H_MAP_T][W_MAP_T], char _props[H_MAP_T][W_MAP_T], sfVector2f* _player_pos, int _inv[4], sfMusic* _mus);

/// Loads data from a "default" save file, overriding the previously saved game.
/// \param _map - A tilemap
/// \param _props - A propmap
/// \param _player_pos - A pointer to the player character's in-world coordinates
/// \param _inv - The player character's inventory
/// \param _inv - A pointer to a BGM object
void load_new_map(char _map[H_MAP_T][W_MAP_T], char _props[H_MAP_T][W_MAP_T], sfVector2f* _player_pos, int _inv[4], sfMusic* _mus);
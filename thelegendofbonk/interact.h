#pragma once
#include "tools.h"
#include "map.h"

typedef struct {
	sfVector2f chestPosition;
	int id;
}Chest;

Chest chestArray[3];

void interactTilePos(char _map[H_MAP_T][W_MAP_T]);


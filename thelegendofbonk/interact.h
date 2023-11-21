#pragma once
#include "tools.h"
#include "map.h"
#include "player.h"

typedef struct {
	sfVector2f chestPosition;
	int id;
}Chest;

Chest chestArray[5]; 
int chestCpt;

void interactTilePos(char _map[H_MAP_T][W_MAP_T]);
int canInteract();

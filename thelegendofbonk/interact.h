#pragma once
#include "tools.h"
#include "map.h"
#include "player.h"

typedef struct {
	sfVector2f chestPosition;
	int id;
}Chest;

typedef struct {
	sfVector2f pnjPosition;
	char* txt;
	int id;
}PNJ;

PNJ pnjArray[10];
int pnjCpt;
Chest chestArray[16];
int chestCpt;

void interactTilePos(char _map[H_MAP_T][W_MAP_T]);
int canInteract();

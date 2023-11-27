#pragma once

#include "SFML/Audio.h"
#include "tools.h"
#include "map.h"
#include "player.h"

/// Data type to hold in-world chest objects
typedef struct {
	int spriteId;
	sfVector2f chestPosition;
	int id;
	char flagOpen;
} Chest;

/// Data type to hold in-world NPC objects
typedef struct {
	sfVector2f pnjPosition;
	char txt[256];
	int id;
} NPC;

NPC npcArray[10];
Chest chestArray[16];
int chestCpt;
int lampCpt;

/// Tests the entire tilemap for chests or NPCs, and fills the data-holding arrays accordingly.
void interactTilePos(char _map[H_MAP_T][W_MAP_T], char _props[H_MAP_T][W_MAP_T], sfMusic* _m);

/// Checks whether the player is currently standing near an object they can interact with, and returns the found object's ID (or -1 if nothing is in range).
int canInteract();

#include <stdio.h>
#include <stdlib.h>

#include "tools.h"
#include "map.h"
#include "save.h"

void save_map(char _map[H_MAP_T][W_MAP_T], sfVector2f _player_pos, int _inv[4]) {
	FILE* f = fopen(SAVE_PATH"game.sav", "wb+");
	if (f == NULL) {
		printf("Error: unable to open save file\n");
		return;
	}

	fwrite(_map, sizeof(char), H_MAP_T * W_MAP_T, f);
	fwrite(&_player_pos, sizeof(sfVector2f), 1, f);
	fwrite(_inv, sizeof(int), 4, f);

	fclose(f);
}

void load_map(char _map[H_MAP_T][W_MAP_T], sfVector2f* _player_pos, int _inv[4]) {
	FILE* f = fopen(SAVE_PATH"game.sav", "rb");
	if (f == NULL) {
		printf("Error: unable to open save file\n");
		return;
	}

	fread(_map, sizeof(char), H_MAP_T * W_MAP_T, f);
	fread(_player_pos, sizeof(sfVector2f), 1, f);
	fread(_inv, sizeof(int), 4, f);

	fclose(f);
}
#include <stdio.h>
#include <stdlib.h>

#include "tools.h"
#include "map.h"
#include "save.h"
#include "SFML/Audio.h"

void save_map(char _map[H_MAP_T][W_MAP_T], char _props[H_MAP_T][W_MAP_T], sfVector2f _player_pos, int _inv[4], sfMusic* _mus) {
	FILE* f = fopen(SAVE_PATH"game.sav", "wb+");
	float vol = sfMusic_getVolume(_mus);
	if (f == NULL) {
		printf("Error: unable to open save file\n");
		return;
	}

	fwrite(_map, sizeof(char), H_MAP_T * W_MAP_T, f);
	fwrite(_props, sizeof(char), H_MAP_T * W_MAP_T, f);
	fwrite(&_player_pos, sizeof(sfVector2f), 1, f);
	fwrite(_inv, sizeof(int), 4, f);
	fwrite(&vol, sizeof(int), 1, f);

	fclose(f);
}

void load_map(char _map[H_MAP_T][W_MAP_T], char _props[H_MAP_T][W_MAP_T], sfVector2f* _player_pos, int _inv[4], sfMusic* _mus) {
	FILE* f = fopen(SAVE_PATH"game.sav", "rb");
	float vol = 0.0f;
	if (f == NULL) {
		printf("Error: unable to open save file\n");
		return;
	}

	fread(_map, sizeof(char), H_MAP_T * W_MAP_T, f);
	fread(_props, sizeof(char), H_MAP_T * W_MAP_T, f);
	fread(_player_pos, sizeof(sfVector2f), 1, f);
	fread(_inv, sizeof(int), 4, f);
	fread(&vol, sizeof(float), 1, f);
	sfMusic_setVolume(_mus, vol);
	fclose(f);
}

void load_new_map(char _map[H_MAP_T][W_MAP_T], char _props[H_MAP_T][W_MAP_T], sfVector2f* _player_pos, int _inv[4], sfMusic* _mus) {
	FILE* f = fopen(SAVE_PATH"default.sav", "rb");
	float vol = 0.0f;
	if (f == NULL) {
		printf("Error: unable to open save file\n");
		return;
	}

	fread(_map, sizeof(char), H_MAP_T * W_MAP_T, f);
	fread(_props, sizeof(char), H_MAP_T * W_MAP_T, f);
	fread(_player_pos, sizeof(sfVector2f), 1, f);
	fread(_inv, sizeof(int), 4, f);
	fread(&vol, sizeof(float), 1, f);
	sfMusic_setVolume(_mus, vol);
	fclose(f);
	remove(SAVE_PATH"game.sav");
}
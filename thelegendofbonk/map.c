#include "map.h"

void initMapNull(char _map[H_MAP_T][W_MAP_T]) {
	for (int i = 0; i < H_MAP_T; i++) {
		for (int j = 0; j < W_MAP_T; j++) {
			_map[i][j] = 0;
		}
	}
}

void initMapRandom(char _map[H_MAP_T][W_MAP_T]) {
	for (int i = 0; i < H_MAP_T; i++) {
		for (int j = 0; j < W_MAP_T; j++) {
			// Pourquoi modulo 4 ?
			_map[i][j] = rand() % 4;
		}
	}
}
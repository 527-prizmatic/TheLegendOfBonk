#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <math.h>

#include "map.h"

int main() {
	srand((unsigned int)time(NULL));
	char tilemap[H_MAP_T][W_MAP_T];

	initMapRandom(tilemap);

	for (int i = 0; i < H_MAP_T; i++) {
		for (int j = 0; j < W_MAP_T; j++) {
			printf("%d ", tilemap[i][j]);
		}
		printf("\n");
	}

	return 1;
}
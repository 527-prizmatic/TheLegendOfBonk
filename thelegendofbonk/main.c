#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <math.h>
#include "SFML/Graphics.h"

#include "tools.h"
#include "map.h"
#include "render.h"
#include "textures.h"
#include "player.h"

#define TICKSPEED 30

int main() {
	initTools();
	char tilemap[H_MAP_T][W_MAP_T];
	initMapRandom(tilemap);
	sfRenderWindow* window = initRender();

	for (int i = 0; i < H_MAP_T; i++) {
		for (int j = 0; j < W_MAP_T; j++) {
			printf("%d ", tilemap[i][j]);
		}
		printf("\n");
	}

	//INIT
	initPlayer();

	sfEvent event;
	float tick = 0.0f;

	// Game loop
	while (sfRenderWindow_isOpen(window)) {
		restartClock();

		tick += getDeltaTime();
		if (tick >= 1.0f / TICKSPEED) {
			tick = 0.0f;
			while (sfRenderWindow_pollEvent(window, &event)) {
				if (event.type == sfEvtClosed) sfRenderWindow_close(window);
			}

			// Player updates
			updatePlayer();

			// Rendering
			sfRenderWindow_clear(window, sfBlack);
			renderMap(tilemap, window);
			displayPlayer(window);
			sfRenderWindow_display(window);
		}
	}

	return 1;
}
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

int main() {
	char tilemap[H_MAP_T][W_MAP_T];
	initMapRandom(tilemap);
	sfRenderWindow* window = render_init();


	for (int i = 0; i < H_MAP_T; i++) {
		for (int j = 0; j < W_MAP_T; j++) {
			printf("%d ", tilemap[i][j]);
		}
		printf("\n");
	}

	//INIT
	initPlayer();

	sfEvent event;
	while (sfRenderWindow_isOpen(window))
	{
		
		while (sfRenderWindow_pollEvent(window, &event))
		{
			if (event.type == sfEvtClosed)
				sfRenderWindow_close(window);
		}

		//UPDATE
		updatePlayer();

		//DRAW
		sfRenderWindow_clear(window, sfBlack);
		displayPlayer(window); 
		sfRenderWindow_display(window);
	}


	return 1;
}
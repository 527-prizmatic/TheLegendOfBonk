#include "render.h"
#include "tools.h"

sfRenderWindow* render_init() {
	sfVideoMode mode = { 800, 600, 32 };
<<<<<<< HEAD
    sfRenderWindow* window = sfRenderWindow_create(mode, "TheLegendOfBonk", sfResize | sfClose, NULL);
    sfEvent event;

	initPlayer();  

	while (sfRenderWindow_isOpen(window))
	{
		while (sfRenderWindow_pollEvent(window, &event))
		{
			if (event.type == sfEvtClosed)
				sfRenderWindow_close(window);
		}

      sfRenderWindow_clear(window, sfBlack);
	  displayPlayer(window);  
	  
      sfRenderWindow_display(window);
	  
	}
}


=======
    sfRenderWindow* _w = sfRenderWindow_create(mode, "TheLegendOfBonk", sfResize | sfClose, NULL);
	return _w;
}

void render_map(char _map[H_MAP_T][W_MAP_T]) {

	sfRectangleShape* tile = sfRectangleShape_create();
	sfTexture* tilesheet = sfTexture_createFromFile(TEXTURE_PATH"tilemap_poc.png", NULL);
	for (int i = 0; i < H_MAP_T; i++) {
		for (int j = 0; j < W_MAP_T; j++) {

		}
	}
}
>>>>>>> nucleus

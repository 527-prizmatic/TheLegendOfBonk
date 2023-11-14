#include "render.h"
#include "tools.h"

sfRenderWindow* render_init() {
	sfVideoMode mode = { 800, 600, 32 };

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


#include "render.h"
#include "tools.h"
#include "textures.h"

#include "SFML/Graphics.h"

// Global variables for rendering purposes
sfTexture* tilesheet;
sfSprite* tile;

sfRenderWindow* initRender() {
	sfVideoMode mode = { 800, 600, 32 };
    sfRenderWindow* _w = sfRenderWindow_create(mode, "TheLegendOfBonk", sfResize | sfClose, NULL);
	tilesheet = sfTexture_createFromFile(TEXTURE_PATH"tilemap_poc.png", NULL);
	tile = sfSprite_create();
	return _w;
}

void renderMap(char _map[H_MAP_T][W_MAP_T], sfRenderWindow* _w) {
	sfSprite_setTexture(tile, tilesheet, sfFalse);
	for (int i = 0; i < H_MAP_T; i++) {
		for (int j = 0; j < W_MAP_T; j++) {
			sfSprite_setPosition(tile, (sfVector2f) { i * 32, j * 32 });
			char zz = _map[i][j];
			sfIntRect zzz = textureFromId(zz);
			sfSprite_setTextureRect(tile, zzz);
			sfRenderWindow_drawSprite(_w, tile, NULL);
		}
	}
}


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
	sfSprite_setScale(tile, (sfVector2f){ TILE_PX / 32, TILE_PX / 32 });
	return _w;
}

void renderMap(char _map[H_MAP_T][W_MAP_T], sfRenderWindow* _w) {
	sfSprite_setTexture(tile, tilesheet, sfFalse);
	for (int i = 0; i < W_MAP_T; i++) {
		for (int j = 0; j < H_MAP_T; j++) {
			sfSprite_setPosition(tile, (sfVector2f) { i * TILE_PX, j * TILE_PX});
			sfSprite_setTextureRect(tile, textureFromId(_map[j][i]));
			sfRenderWindow_drawSprite(_w, tile, NULL);
		}
	}
}


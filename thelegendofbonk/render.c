#include "render.h"
#include "tools.h"
#include "textures.h"
#include "player.h"

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

sfView* initView() {
	sfView* _v = sfView_create();
	sfFloatRect rectView = { 400.f, 300.f, 800.f, 600.f };
	sfView_setSize(_v, (sfVector2f){ 800, 600 });
	sfView_reset(_v, rectView);
	sfView_setCenter(_v, (sfVector2f) { 400, 300 });
	return _v;
}

void updateView(sfRenderWindow* _w, sfView* _v, sfVector2f _pos) {
	_pos.x += 24;
	_pos.y += 24;

	if(_pos.x < 400) _pos.x = 400;
    if(_pos.y < 300) _pos.y = 300;
	if(_pos.x > W_MAP_PX - 400) _pos.x = W_MAP_PX - 400;
    if(_pos.y > H_MAP_PX - 300) _pos.y = H_MAP_PX - 300;

	sfView_setCenter(_v, _pos);
	sfRenderWindow_setView(_w, _v);
    
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


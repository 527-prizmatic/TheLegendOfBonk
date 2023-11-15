#include "render.h"
#include "tools.h"
#include "textures.h"

#include "SFML/Graphics.h"

// Global variables for rendering purposes
sfTexture* tilesheet;
sfSprite* tile;

sfView* view ;
sfVector2f posView; 

sfRenderWindow* initRender() {
	sfVideoMode mode = { 800, 600, 32 };
    sfRenderWindow* _w = sfRenderWindow_create(mode, "TheLegendOfBonk", sfResize | sfClose, NULL);
	tilesheet = sfTexture_createFromFile(TEXTURE_PATH"tilemap_poc.png", NULL);
	tile = sfSprite_create();
	sfSprite_setScale(tile, (sfVector2f){ TILE_PX / 32, TILE_PX / 32 });
	return _w;
}

void initView(sfRenderWindow* _w) {
	view = sfView_create();
	posView = (sfVector2f){ 400, 300 };
	sfFloatRect rectView = { 400.f, 300.f, 800.f, 600.f };
	sfView_setSize(view, (sfVector2f){ 800, 600 });
	//sfView_setCenter(view, (sfVector2f){ 350, 350}); 
	sfView_reset(view, rectView);
	sfView_setCenter(view,posView); 
	sfRenderWindow_setView(_w, view);
}

void updateView(sfRenderWindow* _w, sfVector2f _pos) {

	if(_pos.x < 400) _pos.x = 400;
    if(_pos.y < 300) _pos.y = 300;
	if(_pos.x > 8000 - 400) _pos.x = 8000 - 400;
    if(_pos.y > 6000 - 300) _pos.y = 6000 - 300;

	sfView_setCenter(view, _pos);
	sfRenderWindow_setView(_w, view);
    
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


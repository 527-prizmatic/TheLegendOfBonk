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
	tilesheet = sfTexture_createFromFile(TEXTURE_PATH"tilesheet.png", NULL);
	tile = sfSprite_create();
	sfSprite_setScale(tile, (sfVector2f){ SCALE, SCALE });
	return _w;
}

sfView* initGameView() {
	sfView* _v = sfView_create();
	sfFloatRect rectView = { 400.f, 300.f, 800.f, 600.f };
	sfView_setSize(_v, (sfVector2f){ 800, 600 });
	sfView_reset(_v, rectView);
	sfView_setCenter(_v, (sfVector2f) { 400, 300 });
	return _v;
}

sfView* initEditorView() {
	sfView* _v = sfView_create();
	sfFloatRect rectView = { 600.f, 450.f, 1200.f, 900.f };
	sfView_setSize(_v, (sfVector2f) { 1200, 900 });
	sfView_reset(_v, rectView);
	sfView_setCenter(_v, (sfVector2f) { 600, 450 });
	return _v;
}

void updateView(sfRenderWindow* _w, sfView* _v, sfVector2f _pos) {
	_pos.x += 32;
	_pos.y += 40;

	if(_pos.x < 400) _pos.x = 400;
    if(_pos.y < 300) _pos.y = 300;
	if(_pos.x > W_MAP_PX - 400) _pos.x = W_MAP_PX - 400;
    if(_pos.y > H_MAP_PX - 300) _pos.y = H_MAP_PX - 300;

	sfView_setCenter(_v, _pos);
	sfRenderWindow_setView(_w, _v);
}

void renderMap(char _map[H_MAP_T][W_MAP_T], sfRenderWindow* _w, sfVector2f _pos) {
	int render_top = 0;
	int render_bottom = 0;
	int render_left = 0;
	int render_right = 0;

	if (gameState == GAME) {
		render_top = max(0, trunc((_pos.y - 400) / TILE_PX));
		render_bottom = min(H_MAP_T - 1, trunc((_pos.y + 400) / TILE_PX));
		render_left = max(0, trunc((_pos.x - 500) / TILE_PX));
		render_right = min(W_MAP_T - 1, trunc((_pos.x + 500) / TILE_PX));
	}
	else if (gameState == EDITOR) {
		render_top = max(0, trunc((_pos.y - 550) / TILE_PX));
		render_bottom = min(H_MAP_T - 1, trunc((_pos.y + 550) / TILE_PX));
		render_left = max(0, trunc((_pos.x - 700) / TILE_PX));
		render_right = min(W_MAP_T - 1, trunc((_pos.x + 700) / TILE_PX));
	}

	sfSprite_setTexture(tile, tilesheet, sfFalse);
	for (int i = render_left; i <= render_right; i++) {
		for (int j = render_top; j <= render_bottom; j++) {
			sfSprite_setPosition(tile, (sfVector2f) { i * TILE_PX, j * TILE_PX});
			sfSprite_setTextureRect(tile, textureFromId(_map[j][i]));
			sfRenderWindow_drawSprite(_w, tile, NULL);
		}
	}
}


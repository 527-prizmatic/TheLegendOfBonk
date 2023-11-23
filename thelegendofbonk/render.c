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
	tilesheet = sfTexture_createFromFile(TEXTURE_PATH"tilesheet_v2.png", NULL);
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

sfView* initMinimapView() {
	sfView* _v = sfView_create();
	sfFloatRect rectView = { 0.f, 0.f, W_MAP_PX, H_MAP_PX };
	sfView_setSize(_v, vector2f(W_MAP_PX, H_MAP_PX));
	sfView_reset(_v, rectView);
	sfView_setCenter(_v, vector2f(W_MAP_PX / 2, H_MAP_PX / 2));
	sfView_setViewport(_v, (sfFloatRect) { 0.025f, 0.025f, 0.25f, 0.25f });
	return _v;
}

sfView* initCreditsView() {
	sfView* _v = sfView_create();
	sfFloatRect rectView = { 400.f, 300.f, 800.f, 600.f };
	sfView_setSize(_v, (sfVector2f) { 800, 600 });
	sfView_reset(_v, rectView);
	sfView_setCenter(_v, (sfVector2f) { 400, 300 });
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

void renderMap(char _map[H_MAP_T][W_MAP_T], sfRenderWindow* _w, sfVector2f _pos, char _fg, char _minimap) {
	sfSprite_setTexture(tile, tilesheet, sfFalse);

	int render_top = 0;
	int render_bottom = 0;
	int render_left = 0;
	int render_right = 0;

	if (_minimap == 1) {
		render_top = 0;
		render_bottom = H_MAP_T;
		render_left = 0;
		render_right = W_MAP_T;
	}
	else if (gameState == GAME) {
		render_top = (int) max(0, trunc((_pos.y - 400) / TILE_PX));
		render_bottom = (int) min(H_MAP_T - 1, trunc((_pos.y + 400) / TILE_PX));
		render_left = (int) max(0, trunc((_pos.x - 500) / TILE_PX));
		render_right = (int) min(W_MAP_T - 1, trunc((_pos.x + 500) / TILE_PX));
	}
	else if (gameState == EDITOR) {
		render_top = (int) max(0, trunc((_pos.y - 550) / TILE_PX));
		render_bottom = (int) min(H_MAP_T - 1, trunc((_pos.y + 550) / TILE_PX));
		render_left = (int) max(0, trunc((_pos.x - 700) / TILE_PX));
		render_right = (int) min(W_MAP_T - 1, trunc((_pos.x + 700) / TILE_PX));
	}

	for (int i = render_left; i <= render_right; i++) {
		for (int j = render_top; j <= render_bottom; j++) {
			if (_map[j][i] >= 64) { if (_fg != -1 && ((isForeground(_map[j][i]) && _fg == 0) || (!isForeground(_map[j][i]) && _fg == 1))) continue; }
			sfSprite_setPosition(tile, (sfVector2f) { (float)i * TILE_PX, (float)j * TILE_PX });
			sfSprite_setTextureRect(tile, textureFromId(_map[j][i]));
			sfRenderWindow_drawSprite(_w, tile, NULL);
		}
	}
}

void renderMinimap(sfRenderWindow* _w, sfView* _v, char _map[H_MAP_T][W_MAP_T], char _props[H_MAP_T][W_MAP_T]) {
	const sfView* v_origin = sfRenderWindow_getDefaultView(_w);

	sfRectangleShape* minimapFrame = initRectangle(vector2f(.025f * 800 - 5, .025f * 600 - 5), vector2f(.25f * 800 + 10, .25f * 600 + 10));
	sfRectangleShape_setFillColor(minimapFrame, sfColor_fromRGBA(0, 0, 0, 128));

	sfRenderWindow_setView(_w, sfRenderWindow_getDefaultView(_w));
	sfRenderWindow_drawRectangleShape(_w, minimapFrame, NULL);
	sfRenderWindow_setView(_w, _v);
	renderMap(_map, _w, sfView_getCenter(_v), 1, 1);
	renderMap(_props, _w, sfView_getCenter(_v), -1, 1);
	renderPlayerOnMinimap(_w);

	sfRenderWindow_setView(_w, v_origin);
}

void renderEditorUI(sfRenderWindow* _w, sfView* _v, int _mode, sfFont* _font) {
	char editorUIInfo[] = "1 to place Terrain   |   2 to place Props";
	sfText* textEditorInfo = initText(_font, 30, vector2f(72.0f, 11.0f));
	sfText_setString(textEditorInfo, editorUIInfo);

	sfRenderWindow_setView(_w, sfRenderWindow_getDefaultView(_w));

	// Displays dark overlay to hide the map while picking a tile
	sfRectangleShape* overlay = initRectangle(vector2f(0.f, 0.f), vector2f(1200, 900));
	sfRectangleShape_setFillColor(overlay, sfColor_fromRGBA(0, 0, 0, 128));
	sfRenderWindow_drawRectangleShape(_w, overlay, NULL);

	sfRenderWindow_drawText(_w, textEditorInfo, NULL);


	// Renders all available tiles
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 5; j++) {
			sfSprite_setPosition(tile, (sfVector2f) { i * TILE_PX + 16.f, j * TILE_PX + 64.f });
			if (textureFromId(j * 12 + i + 64 * _mode).width == 0 && (j * 12 + i) != 0 && (j * 12 + i) != 64) break;
			sfSprite_setTextureRect(tile, textureFromId(j * 12 + i + 64 * _mode));
			sfRenderWindow_drawSprite(_w, tile, NULL);
		}
	}
	sfRenderWindow_setView(_w, _v);
}

void renderPlayerOnMinimap(sfRenderWindow* _w) {
	sfRectangleShape* marker = initRectangle(playerPos, vector2f(64, 64));
	sfRectangleShape_setFillColor(marker, sfRed);
	sfRenderWindow_drawRectangleShape(_w, marker, NULL);
}

void renderCredit(sfRenderWindow* _w, sfView* _v, sfFont* _font, char _name[], char _role[], char _posX, char _posY)
{
	sfText* textName = initText(_font, 30, vector2f(_posX, _posY));
	sfText_setString(textName, _name);
	sfRenderWindow_drawText(_w, textName, NULL);

	sfText* textRole = initText(_font, 20, vector2f(_posX, _posY + 30));
	sfText_setString(textRole, _role);
	sfRenderWindow_drawText(_w, textRole, NULL);
}

void swapLamp(char _map[H_MAP_T][W_MAP_T], char _flagNight)
{
	for (int i = 0; i < H_MAP_T; i++) {
		for (int j = 0; j < W_MAP_T; j++) {
			if (_map[i][j] == 81 && _flagNight) _map[i][j] = 101;
			else if (_map[i][j] == 101 && !_flagNight) _map[i][j] = 81;
		}
	}
}

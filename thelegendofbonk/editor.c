#include "SFML/Graphics.h"
#include <stdlib.h>
#include <stdio.h>

#include "editor.h"
#include "tools.h"
#include "map.h"
#include "render.h"
#include "textures.h"

void updateEditorView(sfRenderWindow* _w, sfView* _v) {
	float camMoveSpeed = 700.0f;
	sfVector2f viewPos = sfView_getCenter(_v);

	if (sfKeyboard_isKeyPressed(KEY_UP)) viewPos.y -= camMoveSpeed * TICK_TIME;
	if (sfKeyboard_isKeyPressed(KEY_DOWN)) viewPos.y += camMoveSpeed * TICK_TIME;
	if (sfKeyboard_isKeyPressed(KEY_LEFT)) viewPos.x -= camMoveSpeed * TICK_TIME;
	if (sfKeyboard_isKeyPressed(KEY_RIGHT)) viewPos.x += camMoveSpeed * TICK_TIME;

	if (viewPos.x < 600) viewPos.x = 600;
	if (viewPos.y < 450) viewPos.y = 450;
	if (viewPos.x > W_MAP_PX - 600) viewPos.x = W_MAP_PX - 600;
	if (viewPos.y > H_MAP_PX - 450) viewPos.y = H_MAP_PX - 450;

	sfView_setCenter(_v, viewPos);
}

void changeTile(sfRenderWindow* _w, sfView* _v, char _map[H_MAP_T][W_MAP_T], char _prop[H_MAP_T][W_MAP_T], char _id) {
	sfVector2f mouseCursor = sfRenderWindow_mapPixelToCoords(_w, sfMouse_getPosition(_w), _v);
	sfVector2i pos = { (int)mouseCursor.x / TILE_PX, (int)mouseCursor.y / TILE_PX };
	if (_id == 91 && chestCpt > 3) {
		printf("Amount max of chest reach ! (max 4)");
		return;
	}
	if (isMouseWithinWindow(_w)) {
		if (_id < 64) _map[pos.y][pos.x] = _id;
		else _prop[pos.y][pos.x] = _id;
	}
}
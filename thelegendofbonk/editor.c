#include "SFML/Graphics.h"
#include <stdlib.h>
#include <stdio.h>

#include "editor.h"
#include "tools.h"
#include "map.h"

void updateEditorView(sfRenderWindow* _w, sfView* _v) {
	float camMoveSpeed = 100.0f;
	sfVector2f viewPos = sfView_getCenter(_v);
	printf("z");

	if (sfKeyboard_isKeyPressed(KEY_UP)) viewPos.y -= camMoveSpeed * TICK_TIME;
	if (sfKeyboard_isKeyPressed(KEY_DOWN)) viewPos.y += camMoveSpeed * TICK_TIME;
	if (sfKeyboard_isKeyPressed(KEY_LEFT)) viewPos.x -= camMoveSpeed * TICK_TIME;
	if (sfKeyboard_isKeyPressed(KEY_RIGHT)) viewPos.x += camMoveSpeed * TICK_TIME;

	if (viewPos.x < 400) viewPos.x = 400;
	if (viewPos.y < 300) viewPos.y = 300;
	if (viewPos.x > W_MAP_PX - 400) viewPos.x = W_MAP_PX - 400;
	if (viewPos.y > H_MAP_PX - 300) viewPos.y = H_MAP_PX - 300;

}
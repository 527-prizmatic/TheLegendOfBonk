#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <math.h>
#include "SFML/Graphics.h"

#include "map.h"
#include "render.h"
#include "textures.h"
#include "player.h"
#include "dialogBox.h"
#include "tools.h"
#include "inventory.h"

#define TICKSPEED 30

int main() {
	initTools();
	char tilemap[H_MAP_T][W_MAP_T];
	initMapRandom(tilemap);
	sfRenderWindow* window = initRender();
	sfView* view = initView();
	
	// Variable DIALOG BOX
	sfFont* font = initFont();
	sfText* sfTxt = initText();
	sfRectangleShape* dialogBox = initRectangle();
	initDialogBox(sfTxt, font, dialogBox);

	//Variable INVENTORY
	int inventory[4] = { 0, 0, 0, 0 };
	sfSprite* inventorySprite = initSprite();
	sfSprite* keySprite = initSprite();
	initInventory(inventorySprite, keySprite);
	char str[] = "The\nLegend\nof\nBonk";

	for (int i = 0; i < H_MAP_T; i++) {
		for (int j = 0; j < W_MAP_T; j++) {
			printf("%d ", tilemap[i][j]);
		}
		printf("\n");
	}

	//INIT
	initPlayer();
	initView(window);
	sfEvent event;
	float tick = 0.0f;

	// Game loop
	while (sfRenderWindow_isOpen(window)) {
		restartClock();

		tick += getDeltaTime();
		if (tick >= 1.0f / TICKSPEED) {
			tick = 0.0f;
			while (sfRenderWindow_pollEvent(window, &event)) {
				if (event.type == sfEvtClosed) sfRenderWindow_close(window);
			}

			// Updates
			updatePlayer(tilemap);
			updateView(window, view, playerPos);
			updateDialogBox(str, sizeof(str), sfTxt, dialogBox);
			updateInventory(inventory, keySprite);

			// Rendering
			sfRenderWindow_clear(window, sfBlack);
			sfRenderWindow_setView(window, view);
			renderMap(tilemap, window);
			displayPlayer(window);
			displayDialogBox(window, sfTxt, dialogBox);
			displayInventory(window, inventorySprite, keySprite);
			sfRenderWindow_display(window);

			if (sfKeyboard_isKeyPressed(sfKeyK) && sfKeyboard_isKeyPressed(sfKeyLControl)) save_map(tilemap, playerPos, inventory);
			if (sfKeyboard_isKeyPressed(sfKeyL) && sfKeyboard_isKeyPressed(sfKeyLControl)) load_map(tilemap, &playerPos, inventory);
		}
	}

	sfRenderWindow_close(window);
	return 1;
}
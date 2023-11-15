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
	
	// Variable DIALOG BOX
	sfFont* font = initFont();
	sfText* sfTxt = initText();
	sfRectangleShape* dialogBox = initRectangle();
	initDialogBox(sfTxt, font, dialogBox);
	char str[] = "Hugo Micelli\nEvan Valette";

	//Variable INVENTORY
	sfSprite* inventorySprite = initSprite();
	initInventory(inventorySprite);

	for (int i = 0; i < H_MAP_T; i++) {
		for (int j = 0; j < W_MAP_T; j++) {
			printf("%d ", tilemap[i][j]);
		}
		printf("\n");
	}

	//INIT
	int inventory[4] = { 0, 0, 0, 0 };
	initPlayer();
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
			updatePlayer();
			updateInventory(inventory);
			updateDialogBox(str, sizeof(str), sfTxt, dialogBox);

			// Rendering
			sfRenderWindow_clear(window, sfBlack);
			renderMap(tilemap, window);
			displayPlayer(window);
			displayDialogBox(window, sfTxt, dialogBox);
			displayInventory(window, inventorySprite);
			sfRenderWindow_display(window);
		}
	}

	return 1;
}
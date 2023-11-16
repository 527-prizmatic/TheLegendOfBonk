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
#include "save.h"

#define TICKSPEED 30

// TODO MUSIC BONEY M RASPUTIN

int main() {
	initTools();
	char tilemap[H_MAP_T][W_MAP_T];
	initMapNull(tilemap);

	sfRenderWindow* window = initRender();
	sfView* view = initView();
	
	// Variable DIALOG BOX
	sfFont* font = sfFont_createFromFile(TEXTURE_PATH"3Dventure.ttf");
	sfText* sfTxt_db = sfText_create();
	sfText* sfTxt_g = sfText_create();
	sfText* sfTxt_q = sfText_create();

	sfRectangleShape* dialogBox = sfRectangleShape_create();
	initDialogBox(sfTxt_db, font, 30, dialogBox);
	sfRectangleShape* buttonGame = sfRectangleShape_create();
	initDialogBox(sfTxt_g, font, 30, buttonGame);
	sfRectangleShape* buttonQuit = sfRectangleShape_create();
	initDialogBox(sfTxt_q, font, 30, buttonQuit);

	// Variable INVENTORY
	int inventory[4] = { 0, 0, 0, 0 };
	sfSprite* inventorySprite = sfSprite_create();
	sfSprite* keySprite = sfSprite_create();
	initInventory(inventorySprite, keySprite);

	sfText* sfTxt_c = sfText_create();
	sfRectangleShape* buttonCraft = sfRectangleShape_create();
	initDialogBox(sfTxt_c, font, 20, buttonCraft);

	char str[] = "The\nLegend\nof\nBonk";
	char game[] = "GAME";
	char quit[] = "QUIT";
	char craft[] = "CRAFT !";

	/*for (int i = 0; i < H_MAP_T; i++) {
		for (int j = 0; j < W_MAP_T; j++) {
			printf("%d ", tilemap[i][j]);
		}
		printf("\n");
	}*/

	//INIT
	initPlayer();
	initView(window);
	sfEvent event;
	float tick = 0.0f;

	GameState gameState = MENU;

	// Game loop
	while (sfRenderWindow_isOpen(window)) {
		while (sfRenderWindow_pollEvent(window, &event)) {
			if (event.type == sfEvtClosed) sfRenderWindow_close(window);
		}
		restartClock();
		sfRenderWindow_clear(window, sfBlack);

		if (gameState == MENU) {
			sfRenderWindow_clear(window, sfBlack);
			updateDialogBox(str, sizeof(str), sfTxt_db, dialogBox, (sfVector2f) { 50.0f, 50.0f }, DEFAULT_DIALOG_SIZE);
			updateDialogBox(game, sizeof(game), sfTxt_g, buttonGame, (sfVector2f) { 500.0f, 500.0f }, DEFAULT_DIALOG_SIZE);
			updateDialogBox(quit, sizeof(quit), sfTxt_q, buttonQuit, (sfVector2f) { 600.0f, 500.0f }, DEFAULT_DIALOG_SIZE);

			displayDialogBox(window, sfTxt_db, dialogBox, sfFalse);
			displayDialogBox(window, sfTxt_g, buttonGame, sfFalse);
			displayDialogBox(window, sfTxt_q, buttonQuit, sfFalse);
			sfRenderWindow_display(window);

			while (sfRenderWindow_pollEvent(window, &event)) {
				if (event.type == sfEvtMouseButtonPressed && event.mouseButton.button == sfMouseLeft) {
					if (isClicked(window, buttonGame)) {
						gameState = GAME;
						load_map(tilemap, &playerPos, inventory);
					}
					else if (isClicked(window, buttonQuit)) gameState = QUIT;
				}
			}
		}
		else if (gameState == GAME) {
			tick += getDeltaTime();
			if (tick >= 1.0f / TICKSPEED) 
			{
				tick = 0.0f;
				// Updates
				updatePlayer(tilemap);
				updateView(window, view, playerPos);
				updateDialogBox(craft, sizeof(craft), sfTxt_c, buttonCraft, (sfVector2f) { 430.0f, 480.0f }, (sfVector2f) { 0.0f, 30.0f });

				// Rendering
				renderMap(tilemap, window);
				displayInventory(window, inventory, inventorySprite, keySprite);
				if (inventory[0] && inventory[1] && inventory[2] && inventory[3])
				{
					displayDialogBox(window, sfTxt_c, buttonCraft, sfTrue);
				}
				sfRenderWindow_setView(window, view);
				displayPlayer(window);
				sfRenderWindow_display(window);

				if (sfKeyboard_isKeyPressed(sfKeyK) && sfKeyboard_isKeyPressed(sfKeyLControl)) save_map(tilemap, playerPos, inventory);
				if (sfKeyboard_isKeyPressed(sfKeyL) && sfKeyboard_isKeyPressed(sfKeyLControl)) load_map(tilemap, &playerPos, inventory);
				if (sfKeyboard_isKeyPressed(sfKeyEscape)) {
					save_map(tilemap, playerPos, inventory);
					gameState = MENU;
				}
			}

			while (sfRenderWindow_pollEvent(window, &event))
			{
				if (event.type == sfEvtMouseButtonPressed && event.mouseButton.button == sfMouseLeft) {
					if (isClicked(window, buttonCraft))
					{
						for (int i = 0; i < 4; i++)
						{
							inventory[i] = 0;
						}
						inventory[0] = 2;
					}
				}
			}
		}
		else if (gameState == QUIT) break;
	}

	sfRenderWindow_close(window);
	printf("gbye");
	return 1;
}
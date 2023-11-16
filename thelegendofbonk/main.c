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
	initDialogBox(sfTxt_db, font, dialogBox);
	sfRectangleShape* buttonGame = sfRectangleShape_create();
	initDialogBox(sfTxt_g, font, buttonGame);

	sfSprite* buttonPlay = sfSprite_create();
	sfSprite* buttonQuiT = sfSprite_create();
	sfTexture* buttonTexture = sfTexture_createFromFile(TEXTURE_PATH"play.png", NULL);
	sfTexture* buttonTexture2 = sfTexture_createFromFile(TEXTURE_PATH"quit.png", NULL);
	sfSprite_setTexture(buttonPlay, buttonTexture, sfFalse); 
	sfSprite_setScale(buttonPlay, (sfVector2f) { 3.5f, 3.5f }); 
	sfSprite_setPosition(buttonPlay, (sfVector2f) { 200.0f, 350.0f });
	sfSprite_setTexture(buttonQuiT, buttonTexture2, sfFalse);
	sfSprite_setScale(buttonQuiT, (sfVector2f) { 3.5f, 3.5f });
	sfSprite_setPosition(buttonQuiT, (sfVector2f) { 400.0f, 350.0f });
	
	sfRectangleShape* buttonQuit = sfRectangleShape_create();
	initDialogBox(sfTxt_q, font, buttonQuit);

	// Inventory handling
	int inventory[4] = { 0, 0, 0, 0 };
	sfSprite* inventorySprite = sfSprite_create();
	sfSprite* keySprite = sfSprite_create();
	sfText* craftText = sfText_create();
	sfRectangleShape* craftButton = sfRectangleShape_create();
	initInventory(inventorySprite, keySprite, craftButton, craftText);

	char str[] = "The\nLegend\nof\nBonk";
	char game[] = "GAME";
	char quit[] = "QUIT";

	initPlayer();
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
			updateDialogBox(str, sizeof(str), sfTxt_db, dialogBox, (sfVector2f) { 320.0f, 150.0f });
			updateDialogBox(game, sizeof(game), sfTxt_g, buttonGame, (sfVector2f) { 225.0f, 350.0f });
			updateDialogBox(quit, sizeof(quit), sfTxt_q, buttonQuit, (sfVector2f) { 430.0f, 350.0f });
			displayDialogBox(window, sfTxt_db, dialogBox);
			displayDialogBox(window, sfTxt_g, buttonGame);
			displayDialogBox(window, sfTxt_q, buttonQuit);
			sfRenderWindow_drawSprite(window, buttonPlay, NULL);
			sfRenderWindow_drawSprite(window, buttonQuiT, NULL);
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
			if (tick >= TICK_TIME) {
				tick = 0.0f;
				// Updates
				updatePlayer(tilemap);
				updateView(window, view, playerPos);

				// Rendering
				sfRenderWindow_setView(window, view);
				renderMap(tilemap, window, sfView_getCenter(view));
				displayPlayer(window);
				displayInventory(window, inventory, inventorySprite, keySprite, craftButton, craftText);
				sfRenderWindow_display(window);

				if (sfKeyboard_isKeyPressed(sfKeyK) && sfKeyboard_isKeyPressed(sfKeyLControl)) save_map(tilemap, playerPos, inventory);
				if (sfKeyboard_isKeyPressed(sfKeyL) && sfKeyboard_isKeyPressed(sfKeyLControl)) load_map(tilemap, &playerPos, inventory);
				if (sfKeyboard_isKeyPressed(sfKeyEscape)) {
					save_map(tilemap, playerPos, inventory);
					gameState = MENU;
				}
			}
		}
		else if (gameState == QUIT) break;
	}

	sfRenderWindow_close(window);
	printf("gbye");
	return 1;
}
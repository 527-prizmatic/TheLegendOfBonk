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
	initDialogBox(sfTxt_db, font, 30, dialogBox);
	sfRectangleShape* buttonGame = sfRectangleShape_create();
	initDialogBox(sfTxt_g, font, 30, buttonGame);
	sfRectangleShape* buttonQuit = sfRectangleShape_create();
	initDialogBox(sfTxt_q, font, 30, buttonQuit);

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
	
	// Inventory handling
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
			updateDialogBox(str, sizeof(str), sfTxt_db, dialogBox, (sfVector2f) { 50.0f, 50.0f }, DEFAULT_DIALOG_SIZE);
			updateDialogBox(game, sizeof(game), sfTxt_g, buttonGame, (sfVector2f) { 500.0f, 500.0f }, DEFAULT_DIALOG_SIZE);
			updateDialogBox(quit, sizeof(quit), sfTxt_q, buttonQuit, (sfVector2f) { 600.0f, 500.0f }, DEFAULT_DIALOG_SIZE);
			displayDialogBox(window, sfTxt_db, dialogBox, sfFalse);
			displayDialogBox(window, sfTxt_g, buttonGame, sfFalse);
			displayDialogBox(window, sfTxt_q, buttonQuit, sfFalse);
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
				updateDialogBox(craft, sizeof(craft), sfTxt_c, buttonCraft, (sfVector2f) { 430.0f, 480.0f }, (sfVector2f) { 0.0f, 30.0f });

				// Rendering
				displayInventory(window, inventory, inventorySprite, keySprite);
				if (inventory[0] && inventory[1] && inventory[2] && inventory[3])
				{
					displayDialogBox(window, sfTxt_c, buttonCraft, sfTrue);
				}
				
				sfRenderWindow_setView(window, view);
				renderMap(tilemap, window, sfView_getCenter(view));
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
						if (inventory[0] && inventory[1] && inventory[2] && inventory[3]) {
							for (int i = 0; i < 4; i++)
							{
								inventory[i] = 0;
							}
							inventory[0] = 2;
						}
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
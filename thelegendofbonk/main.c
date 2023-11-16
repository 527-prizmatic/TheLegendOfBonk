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

	sfRectangleShape* buttonPlay = sfRectangleShape_create();
	initDialogBox(sfTxt_g, font, buttonPlay);

    sfRectangleShape* buttonQuit = sfRectangleShape_create();
	initDialogBox(sfTxt_q, font, buttonQuit); 

	sfRectangleShape* buttonEdit = sfRectangleShape_create();
	initDialogBox(sfTxt_q, font, buttonEdit);




	sfSprite* spritePlay = sfSprite_create();
	sfSprite* spriteQuit = sfSprite_create();
	sfSprite* spriteEdit = sfSprite_create();
	sfTexture* buttonTexture = sfTexture_createFromFile(TEXTURE_PATH"play.png", NULL);
	sfTexture* buttonTexture2 = sfTexture_createFromFile(TEXTURE_PATH"quit.png", NULL);
	sfTexture* buttonTexture3 = sfTexture_createFromFile(TEXTURE_PATH"edit.png", NULL);
	sfSprite_setTexture(spritePlay, buttonTexture, sfFalse); 
	sfSprite_setScale(spritePlay, (sfVector2f) { 3.5f, 3.5f }); 
	sfSprite_setPosition(spritePlay, (sfVector2f) { 200.0f, 350.0f });

	sfSprite_setTexture(spriteQuit, buttonTexture2, sfFalse);
	sfSprite_setScale(spriteQuit, (sfVector2f) { 3.5f, 3.5f });
	sfSprite_setPosition(spriteQuit, (sfVector2f) { 400.0f, 350.0f });

	sfSprite_setTexture(spriteEdit, buttonTexture3, sfFalse);
	sfSprite_setScale(spriteEdit, (sfVector2f) { 3.5f, 3.5f });
	sfSprite_setPosition(spriteEdit, (sfVector2f) { 330.0f, 450.0f });
	
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
	char edit[] = "EDIT";

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
			updateDialogBox(game, sizeof(game), sfTxt_g, buttonPlay, (sfVector2f) { 225.0f, 350.0f });
			updateDialogBox(quit, sizeof(quit), sfTxt_q, buttonQuit, (sfVector2f) { 430.0f, 350.0f });
			updateDialogBox(quit, sizeof(edit), sfTxt_q, buttonEdit, (sfVector2f) { 330.0f, 450.0f });
			sfRenderWindow_drawSprite(window, spritePlay, NULL);
			sfRenderWindow_drawSprite(window, spriteQuit, NULL);
            sfRenderWindow_drawSprite(window, spriteEdit, NULL);
			sfRenderWindow_display(window);

			while (sfRenderWindow_pollEvent(window, &event)) {
				if (event.type == sfEvtMouseButtonPressed && event.mouseButton.button == sfMouseLeft) {
					if (isClicked(window, buttonPlay)) {
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
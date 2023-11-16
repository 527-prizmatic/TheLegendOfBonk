#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <math.h>
#include "SFML/Graphics.h"
#include "SFML/Audio.h"

#include "map.h"
#include "render.h"
#include "textures.h"
#include "player.h"
#include "dialogBox.h"
#include "tools.h"
#include "inventory.h"
#include "save.h"
#include "editor.h"

// TODO MUSIC BONEY M RASPUTIN

int main() {
	initTools();
	char tilemap[H_MAP_T][W_MAP_T];
	initMapNull(tilemap);

	sfRenderWindow* window = initRender();
	sfView* viewGame = initGameView();
	sfView* viewEditor = initEditorView();
	
	// ---MENU PRINCIPAL---
	sfFont* font = sfFont_createFromFile(TEXTURE_PATH"3Dventure.ttf");
	sfText* sfTxt_db = sfText_create();
	sfText* sfTxt_g = sfText_create();
	sfText* sfTxt_q = sfText_create();

	sfRectangleShape* dialogBox = sfRectangleShape_create();
	initDialogBox(sfTxt_db, font, 30, dialogBox);
	sfRectangleShape* buttonPlay = sfRectangleShape_create();
	initDialogBox(sfTxt_g, font, 30, buttonPlay);
	sfRectangleShape* buttonEdit = sfRectangleShape_create();
	initDialogBox(sfTxt_g, font, 30, buttonEdit);
	sfRectangleShape* buttonQuit = sfRectangleShape_create();
	initDialogBox(sfTxt_q, font, 30, buttonQuit);

	// Visuel -MENU PRINCIPAL-
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

	sfText* sfTxt_menuButton = sfText_create();
	sfText* sfTxt_optionButton = sfText_create();
	sfText* sfTxt_quitButton = sfText_create();

	sfRectangleShape* pauseMenuButton = sfRectangleShape_create();
	initDialogBox(sfTxt_menuButton, font, 30, pauseMenuButton);
	sfRectangleShape* pauseOptionButton = sfRectangleShape_create();
	initDialogBox(sfTxt_optionButton, font, 30, pauseOptionButton);
	sfRectangleShape* pauseQuitButton = sfRectangleShape_create();
	initDialogBox(sfTxt_quitButton, font, 30, pauseQuitButton);

	/* VISUEL BOUTON MENU OPTION
	sfSprite* spriteMenuButtonPlay = sfSprite_create();
	sfSprite* spriteMenuButtonOption = sfSprite_create();
	sfSprite* spriteMenuButtonQuit= sfSprite_create();
	sfTexture* menuButtonPlayTexture = sfTexture_createFromFile(TEXTURE_PATH"play.png", NULL);
	sfTexture* menuButtonOptionTexture = sfTexture_createFromFile(TEXTURE_PATH"quit.png", NULL);
	sfTexture* menuButtonQuitTexture = sfTexture_createFromFile(TEXTURE_PATH"edit.png", NULL);

	sfSprite_setTexture(spriteMenuButtonPlay, menuButtonPlayTexture, sfFalse);
	sfSprite_setScale(spriteMenuButtonPlay, (sfVector2f) { 3.5f, 3.5f });
	sfSprite_setPosition(spriteMenuButtonPlay, (sfVector2f) { 200.0f, 350.0f });
	sfSprite_setTexture(spriteMenuButtonOption, menuButtonOptionTexture, sfFalse);
	sfSprite_setScale(spriteMenuButtonOption, (sfVector2f) { 3.5f, 3.5f });
	sfSprite_setPosition(spriteMenuButtonOption, (sfVector2f) { 400.0f, 350.0f });
	sfSprite_setTexture(menuButtonQuitTexture, menuButtonQuitTexture, sfFalse);
	sfSprite_setScale(menuButtonQuitTexture, (sfVector2f) { 3.5f, 3.5f });
	sfSprite_setPosition(menuButtonQuitTexture, (sfVector2f) { 330.0f, 450.0f });
	*/

	//Background
	sfTexture* backgroundTexture = sfTexture_createFromFile(TEXTURE_PATH"background.png", NULL);
	sfSprite* backgroundSprite = sfSprite_create();
	sfSprite_setTexture(backgroundSprite, backgroundTexture, sfFalse);
	sfSprite_setScale(backgroundSprite, (sfVector2f) { 1.0f, 1.0f });
	sfSprite_setPosition(backgroundSprite, (sfVector2f) { 0.0f, 0.0f });


	
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
	char edit[] = "EDIT";
	char craft[] = "CRAFT !";

	char tileSelection = 0;

	char flagEditorSel = 0;
	char flagCraft = 0;

	initPlayer();
	sfEvent event;
	float tick = 0.0f;

	load_map(tilemap, &playerPos, inventory);

	//Musique 
	float volume = 0.0f;
	char flagMusic = 0;

	sfMusic* music = sfMusic_createFromFile(AUDIO_PATH"01_main_screen_trailer.wav");
	sfSoundStatus audioStatus;
	sfMusic_play(music);
	volume = sfMusic_getVolume(music);
	sfMusic_setLoop(music, sfTrue);

	// Game loop
	while (sfRenderWindow_isOpen(window)) {
		while (sfRenderWindow_pollEvent(window, &event)) {
			if (event.type == sfEvtClosed) sfRenderWindow_close(window);
			else if (event.type == sfEvtMouseButtonPressed && event.mouseButton.button == sfMouseLeft) {
				if (gameState == MENU) {
					if (isClicked(window, buttonPlay)) {
						gameState = GAME;
						load_map(tilemap, &playerPos, inventory);
					}
					else if (isClicked(window, buttonQuit)) gameState = QUIT;
				}

				else if (gameState == GAME) {
					if (isClicked(window, buttonCraft)) {
						if (inventory[0] && inventory[1] && inventory[2] && inventory[3]) {
							flagCraft = 1;
						}
					}
				}
			}
		}
		restartClock();
		sfRenderWindow_clear(window, sfBlack);

		if (gameState == MENU) {
			sfRenderWindow_setView(window, sfRenderWindow_getDefaultView(window));		
			sfRenderWindow_drawSprite(window, backgroundSprite, NULL);

			updateDialogBox(str, sizeof(str), sfTxt_db, dialogBox, (sfVector2f) { 50.0f, 50.0f }, DEFAULT_DIALOG_SIZE);
			updateDialogBox(game, sizeof(game), sfTxt_g, buttonPlay, (sfVector2f) { 225.0f, 350.0f }, DEFAULT_DIALOG_SIZE);
			updateDialogBox(quit, sizeof(quit), sfTxt_q, buttonQuit, (sfVector2f) { 425.0f, 350.0f }, DEFAULT_DIALOG_SIZE);
			updateDialogBox(quit, sizeof(edit), sfTxt_q, buttonEdit, (sfVector2f) { 370.0f, 450.0f }, DEFAULT_DIALOG_SIZE);

			displayDialogBox(window, sfTxt_db, dialogBox, sfFalse);
			sfRenderWindow_drawSprite(window, spritePlay, NULL);
			sfRenderWindow_drawSprite(window, spriteQuit, NULL);
            sfRenderWindow_drawSprite(window, spriteEdit, NULL);
			sfRenderWindow_display(window);

			if (isClicked(window, buttonPlay)) gameState = GAME;
			else if (isClicked(window, buttonEdit)) gameState = EDITOR;
			else if (isClicked(window, buttonQuit)) gameState = QUIT;
		}
		else if (gameState == GAME) {
			tick += getDeltaTime();
			if (tick >= TICK_TIME) {
				tick = 0.0f;

				if (flagCraft == 1) {
					for (int i = 0; i < 4; i++) {
						inventory[i] = 0;
					}
					inventory[0] = 2;
					flagCraft = 0;
				}
				audioStatus = sfMusic_getStatus(music);
				if (audioStatus == sfPlaying)
				{
					if (sfKeyboard_isKeyPressed(sfKeyRight) && volume < 100) volume += 1;
					if (sfKeyboard_isKeyPressed(sfKeyLeft) && volume > 0) volume -= 1;
					if (volume != sfMusic_getVolume(music)) sfMusic_setVolume(music, volume);
				}

				if (sfKeyboard_isKeyPressed(sfKeyM)) {
					if (!flagMusic) {
						if (audioStatus == sfPlaying) sfMusic_pause(music);
						else if (audioStatus == sfPaused) sfMusic_play(music);
					}
					flagMusic = 1;
				}
				else flagMusic = 0;

				// Updates
				updatePlayer(tilemap);
				updateView(window, viewGame, playerPos);
				updateDialogBox(craft, sizeof(craft), sfTxt_c, buttonCraft, (sfVector2f) { 430.0f, 480.0f }, (sfVector2f) { 0.0f, 30.0f });

				// Rendering
				sfRenderWindow_setView(window, viewGame);
				renderMap(tilemap, window, sfView_getCenter(viewGame));
				displayPlayer(window);
				displayInventory(window, inventory, inventorySprite, keySprite);
				if (hasAllKeyPieces(inventory)) displayDialogBox(window, sfTxt_c, buttonCraft, sfTrue);

				sfRenderWindow_display(window);

				if (sfKeyboard_isKeyPressed(sfKeyK) && sfKeyboard_isKeyPressed(sfKeyLControl)) save_map(tilemap, playerPos, inventory);
				if (sfKeyboard_isKeyPressed(sfKeyL) && sfKeyboard_isKeyPressed(sfKeyLControl)) load_map(tilemap, &playerPos, inventory);

				if (isClicked(window, buttonCraft)) {
					if (inventory[0] && inventory[1] && inventory[2] && inventory[3]) {
						for (int i = 0; i < 4; i++) inventory[i] = 0;
						inventory[0] = 2;
					}
				}

				if (sfKeyboard_isKeyPressed(sfKeyEscape)) {
					save_map(tilemap, playerPos, inventory);
					gameState = MENU;
				}
			}
		}
		else if (gameState == EDITOR) {
			tick += getDeltaTime();
			if (tick >= TICK_TIME) {
				tick = 0.0f;

				if (sfMouse_isButtonPressed(sfMouseLeft)) changeTile(window, viewEditor, tilemap, tileSelection);

				if (sfKeyboard_isKeyPressed(sfKeyLeft)) {
					if (!flagEditorSel) {
						tileSelection = (tileSelection + 1) % 4;
						flagEditorSel = 1;
					}
				}
				else flagEditorSel = 0;

				printf("%d\n", tilemap[0][0]);

				sfRenderWindow_setView(window, viewEditor);
				updateEditorView(window, viewEditor);
				renderMap(tilemap, window, sfView_getCenter(viewEditor));
				sfRenderWindow_display(window);
			}

			if (sfKeyboard_isKeyPressed(sfKeyEscape)) {
				save_map(tilemap, playerPos, inventory);
				gameState = MENU;
			}
		}
		else if (gameState == QUIT) break;
	}

	sfRenderWindow_close(window);
	printf("gbye");
	return 1;
}
#include <stdio.h>
#include <string.h>
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
#include "music.h"

int main() {
	initTools();
	char tilemap[H_MAP_T][W_MAP_T];
	char propmap[H_MAP_T][W_MAP_T];

	// Main window
	sfRenderWindow* window = initRender();
	// Game mode view
	sfView* viewGame = initGameView();
	// Editor mode view
	sfView* viewEditor = initEditorView();

	// ---MAIN MENU---
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

	// Var -MAIN MENU-
	char title[] = "The\nLegend\nof\nBonk";
	char game[] = "GAME";
	char quit[] = "QUIT";
	char edit[] = "EDIT";

	// Visuel -MAIN MENU BUTTON-
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

	//Background
	sfTexture* backgroundTexture = sfTexture_createFromFile(TEXTURE_PATH"background.png", NULL);
	sfSprite* backgroundSprite = sfSprite_create();
	sfSprite_setTexture(backgroundSprite, backgroundTexture, sfFalse);
	sfSprite_setScale(backgroundSprite, (sfVector2f) { 1.0f, 1.0f });
	sfSprite_setPosition(backgroundSprite, (sfVector2f) { 0.0f, 0.0f });

	// ---OPTION MENU---
	sfText* sfTxt_menuButton = sfText_create();
	sfText* sfTxt_optionButton = sfText_create();
	sfText* sfTxt_quitButton = sfText_create();
	sfText* sfTxt_volumeUp = sfText_create();
	sfText* sfTxt_volumeDown = sfText_create();
	sfText* sfTxt_return = sfText_create();
	sfText* sfTxt_volume = sfText_create();
	sfText_setFont(sfTxt_volume, font);
	sfText_setCharacterSize(sfTxt_volume, 30);
	sfText_setPosition(sfTxt_volume, vector2f(250.0f, 250.0f));

	sfRectangleShape* pauseMenuButton = sfRectangleShape_create();
	initDialogBox(sfTxt_menuButton, font, 30, pauseMenuButton);
	sfRectangleShape* pauseOptionButton = sfRectangleShape_create();
	initDialogBox(sfTxt_optionButton, font, 30, pauseOptionButton);
	sfRectangleShape* pauseQuitButton = sfRectangleShape_create();
	initDialogBox(sfTxt_quitButton, font, 30, pauseQuitButton);

	sfRectangleShape* volumeUpButton = sfRectangleShape_create();
	initDialogBox(sfTxt_volumeUp, font, 30, volumeUpButton);
	sfRectangleShape* volumeDownButton = sfRectangleShape_create();
	initDialogBox(sfTxt_volumeDown, font, 30, volumeDownButton);
	sfRectangleShape* returnButton = sfRectangleShape_create();
	initDialogBox(sfTxt_return, font, 30, returnButton);


	// Var -MAIN MENU-
	char txtVolume[100] = "Volume :";
	char txtButtonMenu[] = "MENU";
	char txtButtonOption[] = "OPTION";
	char txtButtonQuit[] = "QUIT";
	char txtVolumeUp[] = "VOLUME +";
	char txtVolumeDown[] = "VOLUME -";
	char txtReturn[] = "RETURN";
	char flagPauseMenu = 0;
	char flagOption = 0;
	char flagClick = 0;

	
	sfSprite* spriteMenuButtonPlay = sfSprite_create();
	sfSprite* spriteMenuButtonOption = sfSprite_create();
	sfSprite* spriteMenuButtonQuit= sfSprite_create();
	sfTexture* menuButtonMenuTexture = sfTexture_createFromFile(TEXTURE_PATH"return.png", NULL);
	sfTexture* menuButtonQuitTexture = sfTexture_createFromFile(TEXTURE_PATH"quit2.png", NULL);
	sfTexture* menuButtonOptionTexture = sfTexture_createFromFile(TEXTURE_PATH"option.png", NULL);

	sfSprite_setTexture(spriteMenuButtonPlay, menuButtonMenuTexture, sfFalse);
	sfSprite_setScale(spriteMenuButtonPlay, (sfVector2f) { 3.5f, 3.5f });
	sfSprite_setPosition(spriteMenuButtonPlay, (sfVector2f) { 350.0f, 180.0f });

	sfSprite_setTexture(spriteMenuButtonOption, menuButtonOptionTexture, sfFalse);
	sfSprite_setScale(spriteMenuButtonOption, (sfVector2f) { 3.5f, 3.5f });
	sfSprite_setPosition(spriteMenuButtonOption, (sfVector2f) { 350.0f, 250.0f });
	
	sfSprite_setTexture(spriteMenuButtonQuit, menuButtonQuitTexture, sfFalse);
	sfSprite_setScale(spriteMenuButtonQuit, (sfVector2f) { 3.5f, 3.5f });
	sfSprite_setPosition(spriteMenuButtonQuit, (sfVector2f) { 350.0f, 320.0f });

	sfSprite* spriteVolumeUp = sfSprite_create();
    sfSprite* spriteVolumeDown = sfSprite_create();
	sfTexture* volumeUpTexture = sfTexture_createFromFile(TEXTURE_PATH"volumePlus.png", NULL);
    sfTexture* volumeDownTexture = sfTexture_createFromFile(TEXTURE_PATH"volumeMoin.png", NULL);

    sfSprite_setTexture(spriteVolumeUp, volumeUpTexture, sfFalse);
	sfSprite_setScale(spriteVolumeUp, (sfVector2f) { 3.5f, 3.5f }); 
	sfSprite_setPosition(spriteVolumeUp, (sfVector2f) { 250.0f, 190.0f }); 

	sfSprite_setTexture(spriteVolumeDown, volumeDownTexture, sfFalse); 
	sfSprite_setScale(spriteVolumeDown, (sfVector2f) { 3.5f, 3.5f }); 
	sfSprite_setPosition(spriteVolumeDown, (sfVector2f) { 450.0f, 190.0f }); 
	

	// INVENTORY
	int inventory[4] = { 0, 0, 0, 0 };
	char craft[] = "CRAFT !";
	char flagCraft = 0;
	char flagEditorUI = 0;
	unsigned char flagEditorMode = 0;
	char flagEditorLeave = 0;

	sfSprite* inventorySprite = sfSprite_create();
	sfSprite* keySprite = sfSprite_create();
	initInventory(inventorySprite, keySprite);
	sfText* sfTxt_c = sfText_create();
	sfRectangleShape* buttonCraft = sfRectangleShape_create();
	initDialogBox(sfTxt_c, font, 20, buttonCraft);

	char tileSelection = 0;

	initPlayer();
	sfEvent event;
	float tick = 0.0f;

	//Music 
	char flagMusic = 0;
	float canChangeVolume = 0;

	sfMusic* music = sfMusic_createFromFile(AUDIO_PATH"01_main_screen_trailer.wav");
	sfMusic_play(music);
	sfMusic_setLoop(music, sfTrue);

	load_map(tilemap, propmap, &playerPos, inventory, music);

	// Game loop
	while (sfRenderWindow_isOpen(window)) {
		while (sfRenderWindow_pollEvent(window, &event)) {
			if (event.type == sfEvtClosed) sfRenderWindow_close(window);
			else if (event.type == sfEvtMouseButtonPressed && event.mouseButton.button == sfMouseLeft) {
				if (isClicked(window, buttonCraft) && gameState == GAME) {
					if (inventory[0] && inventory[1] && inventory[2] && inventory[3]) {
						flagCraft = 1;
					}
				}
			}
		}
		restartClock();
		sfRenderWindow_clear(window, sfBlack);

		if (gameState == MENU) {
			sfRenderWindow_setView(window, sfRenderWindow_getDefaultView(window));
			sfRenderWindow_drawSprite(window, backgroundSprite, NULL);

			updateDialogBox(title, sizeof(title), sfTxt_db, dialogBox, (sfVector2f) { 50.0f, 50.0f }, DEFAULT_DIALOG_SIZE);
			updateDialogBox(game, sizeof(game), sfTxt_g, buttonPlay, (sfVector2f) { 225.0f, 350.0f }, DEFAULT_DIALOG_SIZE);
			updateDialogBox(quit, sizeof(quit), sfTxt_q, buttonQuit, (sfVector2f) { 425.0f, 350.0f }, DEFAULT_DIALOG_SIZE);
			updateDialogBox(quit, sizeof(edit), sfTxt_q, buttonEdit, (sfVector2f) { 370.0f, 450.0f }, DEFAULT_DIALOG_SIZE);

			displayDialogBox(window, sfTxt_db, dialogBox, sfFalse);
			sfRenderWindow_drawSprite(window, spritePlay, NULL);
			sfRenderWindow_drawSprite(window, spriteQuit, NULL);
			sfRenderWindow_drawSprite(window, spriteEdit, NULL);
			sfRenderWindow_display(window);

			if (isClicked(window, buttonPlay)) gameState = GAME;
			else if (isClicked(window, buttonEdit)) {
				gameState = EDITOR;
				flagClick = 1;
			}
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

				// Updates
				updatePlayer(propmap);
				updateView(window, viewGame, playerPos);
				updateDialogBox(craft, sizeof(craft), sfTxt_c, buttonCraft, (sfVector2f) { 430.0f, 480.0f }, (sfVector2f) { 0.0f, 30.0f });

				// Rendering
				sfRenderWindow_setView(window, viewGame);
				renderMap(tilemap, window, sfView_getCenter(viewGame));
				renderMap(propmap, window, sfView_getCenter(viewGame));
				displayPlayer(window);
				displayInventory(window, inventory, inventorySprite, keySprite);
				if (hasAllKeyPieces(inventory)) displayDialogBox(window, sfTxt_c, buttonCraft, sfTrue);

				sfRenderWindow_display(window);

				if (sfKeyboard_isKeyPressed(sfKeyK) && sfKeyboard_isKeyPressed(sfKeyLControl)) save_map(tilemap, propmap, playerPos, inventory, music);
				if (sfKeyboard_isKeyPressed(sfKeyL) && sfKeyboard_isKeyPressed(sfKeyLControl)) load_map(tilemap, propmap, &playerPos, inventory, music);

				if (isClicked(window, buttonCraft)) {
					if (inventory[0] && inventory[1] && inventory[2] && inventory[3]) {
						for (int i = 0; i < 4; i++) inventory[i] = 0;
						inventory[0] = 2;
					}
				}

				if (sfKeyboard_isKeyPressed(sfKeyEscape)) {
					if (!flagPauseMenu) {
						save_map(tilemap, propmap, playerPos, inventory, music);
						gameState = BREAK;
					}
					flagPauseMenu = 1;
				}
				else flagPauseMenu = 0;
			}
		}
		else if (gameState == EDITOR) {
			sfMusic_stop(music);
			tick += getDeltaTime();
			if (tick >= TICK_TIME) {
				tick = 0.0f;

				if (sfMouse_isButtonPressed(sfMouseLeft) && !flagClick) {
					changeTile(window, viewEditor, tilemap, propmap, tileSelection);
					flagClick = 0;
				}

				// Toggle editor mode - press 1 for terrain, 2 for props
				if (sfKeyboard_isKeyPressed(sfKeyNum1)) flagEditorMode = 0;
				else if (sfKeyboard_isKeyPressed(sfKeyNum2)) flagEditorMode = 1;

				sfRenderWindow_setView(window, viewEditor);
				updateEditorView(window, viewEditor);
				renderMap(tilemap, window, sfView_getCenter(viewEditor));
				renderMap(propmap, window, sfView_getCenter(viewEditor));
				if (flagEditorUI) renderEditorUI(window, sfRenderWindow_getDefaultView(window), flagEditorMode);
				sfRenderWindow_display(window);
			}

			if (sfKeyboard_isKeyPressed(sfKeyEnter)) flagEditorUI = 1;

			if (sfMouse_isButtonPressed(sfMouseLeft) && flagEditorUI) {
				flagClick = 1;
				sfVector2f mouseCursor = sfRenderWindow_mapPixelToCoords(window, sfMouse_getPosition(window), sfRenderWindow_getDefaultView(window));
				sfVector2i pos = { ((int)mouseCursor.x - 16) / TILE_PX, ((int)mouseCursor.y - 16) / TILE_PX };
				tileSelection = pos.x + pos.y * 12;
				tileSelection += 64 * flagEditorMode;
				flagEditorUI = 0;

				printf("%d %d", 64 * flagEditorMode, tileSelection);
			}

			if (!sfMouse_isButtonPressed(sfMouseLeft) && flagClick) flagClick = 0;

			if (sfKeyboard_isKeyPressed(sfKeyEscape)) {
				if (flagEditorUI == 0 && flagEditorLeave == 0) {
					save_map(tilemap, propmap, playerPos, inventory, music);
					sfMusic_play(music);
					gameState = MENU;
				}
				else {
					flagEditorUI = 0;
					flagEditorLeave = 1;
				}
			}
			else flagEditorLeave = 0;
		}
		else if (gameState == BREAK)
		{
			sfRenderWindow_setView(window, sfRenderWindow_getDefaultView(window));
			sfRenderWindow_drawSprite(window, backgroundSprite, NULL);
			if (!flagOption){
				updateDialogBox(txtButtonMenu, sizeof(txtButtonMenu), sfTxt_menuButton, pauseMenuButton, vector2f(370.0f, 180.0f), DEFAULT_DIALOG_SIZE);
				updateDialogBox(txtButtonOption, sizeof(txtButtonOption), sfTxt_optionButton, pauseOptionButton, vector2f(370.0f, 250.0f), DEFAULT_DIALOG_SIZE);
				updateDialogBox(txtButtonQuit, sizeof(txtButtonQuit), sfTxt_quitButton, pauseQuitButton, vector2f(370.0f, 320.0f), DEFAULT_DIALOG_SIZE);

				updateDialogBox(txtVolumeUp, sizeof(txtVolumeUp), sfTxt_volumeUp, volumeUpButton, vector2f(250.0f, 200.0f), DEFAULT_DIALOG_SIZE);
				updateDialogBox(txtVolumeDown, sizeof(txtVolumeDown), sfTxt_volumeDown, volumeDownButton, vector2f(450.0f, 200.0f), DEFAULT_DIALOG_SIZE);
				updateDialogBox(txtReturn, sizeof(txtReturn), sfTxt_return, returnButton, vector2f(250.0f, 300.0f), DEFAULT_DIALOG_SIZE);

				sfSprite_setPosition(spriteMenuButtonPlay, (sfVector2f) { 350.0f, 180.0f });

				sfRenderWindow_drawSprite(window, spriteMenuButtonPlay, NULL); 
				sfRenderWindow_drawSprite(window, spriteMenuButtonOption, NULL); 
				sfRenderWindow_drawSprite(window, spriteMenuButtonQuit, NULL); 

				if (isClicked(window, pauseMenuButton)) {
					save_map(tilemap, propmap, playerPos, inventory, music);
					gameState = MENU;
				}
				else if (isClicked(window, pauseOptionButton)) flagOption = 1;
				else if (isClicked(window, pauseQuitButton)) gameState = QUIT;
			}
			else {
				
				sfSprite_setPosition(spriteMenuButtonPlay, vector2f(250.0f, 300.0f));
				sfRenderWindow_drawSprite(window, spriteVolumeUp, NULL);
                sfRenderWindow_drawSprite(window, spriteVolumeDown, NULL);
				sfRenderWindow_drawSprite(window, spriteMenuButtonPlay, NULL); 

				canChangeVolume += getDeltaTime();
				if (canChangeVolume > 0.1f) {
					if (isClicked(window, volumeUpButton)) changeVolume(music, 1);
					else if (isClicked(window, volumeDownButton)) changeVolume(music, 0);
					canChangeVolume = 0;
				}
				if (isClicked(window, returnButton)) flagOption = 0;
				sprintf_s(txtVolume, 100, "Volume : %.f", sfMusic_getVolume(music));
				sfText_setString(sfTxt_volume, txtVolume);
				sfRenderWindow_drawText(window, sfTxt_volume, NULL);
			}

			if (sfKeyboard_isKeyPressed(sfKeyEscape)) {
				if (!flagPauseMenu) {
					save_map(tilemap, propmap, playerPos, inventory, music);
					flagOption = 0;
					gameState = GAME;
				}
				flagPauseMenu = 1;
			}
			else flagPauseMenu = 0;

			sfRenderWindow_display(window);
		}
		else if (gameState == QUIT) break;
	}

	sfRenderWindow_close(window);
	save_map(tilemap, propmap, playerPos, inventory, music);
	printf("gbye");
	return 1;
}
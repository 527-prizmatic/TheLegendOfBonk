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
#include "interact.h"

int main() {
	/* == RENDERING ENGINE CORE */
	sfRenderWindow* window = initRender(); // Main window
	sfView* viewGame = initGameView(); // Game mode view
	sfView* viewEditor = initEditorView(); // Editor mode view


	/* == MAIN MENU ==  */
	sfFont* font = sfFont_createFromFile(TEXTURE_PATH"3Dventure.ttf");
	sfText* textTitle = sfText_create();
	sfRectangleShape* titleBox = initDialogBox(textTitle, font, 30);
	char title[] = "The\nLegend\nof\nBonk"; // Main menu dialog box text

	/* == INTERACT HEADS-UP ==  */
	sfText* sfTxt_interact = sfText_create();
	sfText_setFont(sfTxt_interact, font);
	sfText_setCharacterSize(sfTxt_interact, 30);
	sfText_setPosition(sfTxt_interact, vector2f(440.0f, 470.0f));
	sfText_setString(sfTxt_interact, "Press E !");

	/* == PAUSE MENU == */
	char txtVolume[16] = "Volume -"; // For volume display in the options screen
	char flagOption = 0; // Whether the pause menu should display the root menu or the options screen
	char flagPauseMenu = 0; // Used for timer purposes when toggling the pause menu
	char flagClick = 0; // Used for misc timer purposes to check if the left mouse button is being pressed
	sfText* textVolume = initText(font, 30, vector2f(250.0f, 250.0f));

	/* == MISC UI BUTTONS == */
	sfSprite* buttonMainPlay = initSprite(TEXTURE_PATH"play.png", vector2f(3.5f, 3.5f), vector2f(200.0f, 350.0f));
	sfSprite* buttonMainEdit = initSprite(TEXTURE_PATH"edit.png", vector2f(3.5f, 3.5f), vector2f(330.0f, 450.0f));
	sfSprite* buttonMainQuit = initSprite(TEXTURE_PATH"quit.png", vector2f(3.5f, 3.5f), vector2f(400.0f, 350.0f));
	sfSprite* spriteMenuBackground = initSprite(TEXTURE_PATH"background.png", vector2f(1.0f, 1.0f), vector2f(0.0f, 0.0f));
	sfSprite* buttonPauseReturn = initSprite(TEXTURE_PATH"return.png", vector2f(3.5f, 3.5f), vector2f(350.0f, 180.0f));
	sfSprite* buttonPauseOptions = initSprite(TEXTURE_PATH"option.png", vector2f(3.5f, 3.5f), vector2f(350.0f, 250.0f));
	sfSprite* buttonPauseQuit = initSprite(TEXTURE_PATH"quit2.png", vector2f(3.5f, 3.5f), vector2f(350.0f, 320.0f));
	sfSprite* buttonOptionsVolPlus = initSprite(TEXTURE_PATH"vol_plus.png", vector2f(3.5f, 3.5f), vector2f(250.0f, 190.0f));
	sfSprite* buttonOptionsVolMinus = initSprite(TEXTURE_PATH"vol_minus.png", vector2f(3.5f, 3.5f), vector2f(450.0f, 190.0f));

	/* == INVENTORY == */
	int inventory[4] = { 0, 0, 0, 0 };
	sfText* sfTxt_c = sfText_create();
	char craft[] = "CRAFT!";
	sfRectangleShape* buttonCraft = initDialogBox(sfTxt_c, font, 20);
	sfSprite* inventorySprite = sfSprite_create();
	sfSprite* keySprite = sfSprite_create();
	initInventory(inventorySprite, keySprite);
	char flagCraft = 0; // Indicates whether the key can be crafted yet

	/* == MAP EDITOR == */
	char tileSelection = 0; // Which tile is currently selected in the editor
	char flagEditorUI = 0; // Whether the map editor UI is currently up
	char flagEditorMode = 0; // Whether the map editor UI currently shows terrain or props
	char flagEditorLeave = 0; // Toggled when ESC is pressed for timing purposes

	/* == BGM == */
	sfMusic* bgm = sfMusic_createFromFile(AUDIO_PATH"01_main_screen_trailer.wav");
	char flagMusic = 0; // Whether the music is currently playing
	float timerVolumeChange = 0;
	sfMusic_play(bgm);
	sfMusic_setLoop(bgm, sfTrue);

	/* == CORE INIT == */
	initTools();
	char tilemap[H_MAP_T][W_MAP_T];
	char propmap[H_MAP_T][W_MAP_T];
	load_map(tilemap, propmap, &playerPos, inventory, bgm);
	initPlayer();
	sfEvent event;
	float tick = 0.0f;

	/* == BONK == */
	sfSprite* bonk = sfSprite_create();
	sfTexture* textureBonk = sfTexture_createFromFile(TEXTURE_PATH"bonk.png", NULL);
	sfSprite_setTexture(bonk, textureBonk, sfFalse);
	sfSprite_setScale(bonk, vector2f(2.0f, 2.0f));
	float bonkAnimTimer = 0.0f;
	char frame = 0;
	sfSprite_setTextureRect(bonk, (sfIntRect) { 0, 0, 32, 32 });
	
	/* == GAME LOOP == */
	while (sfRenderWindow_isOpen(window)) {
		while (sfRenderWindow_pollEvent(window, &event)) if (event.type == sfEvtClosed) sfRenderWindow_close(window); // Check if window is closed via the WIndows UI
		restartClock();
		sfRenderWindow_clear(window, sfBlack);
		if (!sfMouse_isButtonPressed(sfMouseLeft) && flagClick) flagClick = 0; // Technical flag used in misc functions to check if the user is left-clicking somewhere

		if (gameState == MENU) {
			// Rendering functions
			tick += getDeltaTime();
			if (tick >= TICK_TIME) {
				tick = 0.0f;
				sfRenderWindow_setView(window, sfRenderWindow_getDefaultView(window));
				updateDialogBox(title, sizeof(title), textTitle, titleBox, (sfVector2f) { 50.0f, 50.0f }, DEFAULT_DIALOG_SIZE);

				// Main menu UI
				sfRenderWindow_drawSprite(window, spriteMenuBackground, NULL);
				displayDialogBox(window, textTitle, titleBox, sfFalse);
				sfRenderWindow_drawSprite(window, buttonMainPlay, NULL);
				sfRenderWindow_drawSprite(window, buttonMainEdit, NULL);
				sfRenderWindow_drawSprite(window, buttonMainQuit, NULL);
				sfRenderWindow_display(window);
			}

			if (isClicked(window, buttonMainPlay)) { // When clicking on the GAME button
				gameState = GAME;
				interactTilePos(propmap);
			}
			else if (isClicked(window, buttonMainEdit)) { // When clicking on the EDIT button
				gameState = EDITOR;
				flagClick = 1;
			}
			else if (isClicked(window, buttonMainQuit)) gameState = QUIT; // When clicking on the QUIT button
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

				// Crafts the key when hitting "Craft" button
				if (isClicked(window, buttonCraft)) {
					if (inventory[0] && inventory[1] && inventory[2] && inventory[3]) {
						flagCraft = 1;
					}
				}

				// Rendering
				sfRenderWindow_setView(window, viewGame);
				renderMap(tilemap, window, sfView_getCenter(viewGame));
				renderMap(propmap, window, sfView_getCenter(viewGame));
				displayPlayer(window);
				sfSprite_setPosition(bonk, vector2f(500.0f, 500.0f));
				sfRenderWindow_drawSprite(window, bonk, NULL);
				displayInventory(window, inventory, inventorySprite, keySprite);
				if (hasAllKeyPieces(inventory)) displayDialogBox(window, sfTxt_c, buttonCraft, sfTrue);

				if (canInteract() !=-1 && !hasAllKeyPieces(inventory) && inventory[0] !=2) sfRenderWindow_drawText(window, sfTxt_interact, sfFalse);
				if (sfKeyboard_isKeyPressed(sfKeyE) && canInteract() != -1) {
					inventory[canInteract()] = 1;
				}

				// Crafts the key when clicking on the "Craft" button with all key pieces in inventory.
				if (isClicked(window, buttonCraft)) {
					if (inventory[0] && inventory[1] && inventory[2] && inventory[3]) {
						for (int i = 0; i < 4; i++) inventory[i] = 0;
						inventory[0] = 2;
					}
				}

				if (sfKeyboard_isKeyPressed(KEY_PAUSE)) {
					if (!flagPauseMenu) {
						save_map(tilemap, propmap, playerPos, inventory, bgm);
						gameState = BREAK;
					}
					flagPauseMenu = 1;
				}
				else flagPauseMenu = 0;

				sfRenderWindow_display(window);
			}

			bonkAnimTimer += getDeltaTime();
			if (bonkAnimTimer >= 0.1f) {
				bonkAnimTimer = 0.0f;
				frame++;
				frame %= 8;
				sfSprite_setTextureRect(bonk, (sfIntRect) { 32 * frame, 0, 32, 32 });
			}
		}
		else if (gameState == EDITOR) {
			sfMusic_stop(bgm);
			tick += getDeltaTime();
			if (tick >= TICK_TIME) {
				tick = 0.0f;

				// Place tile on click
				if (sfMouse_isButtonPressed(sfMouseLeft) && !flagClick) {
					changeTile(window, viewEditor, tilemap, propmap, tileSelection);
					flagClick = 0;
				}

				// Toggle editor mode - press 1 for terrain, 2 for props
				if (sfKeyboard_isKeyPressed(sfKeyNum1)) flagEditorMode = 0;
				else if (sfKeyboard_isKeyPressed(sfKeyNum2)) flagEditorMode = 1;

				// Core rendering functions
				sfRenderWindow_setView(window, viewEditor);
				updateEditorView(window, viewEditor);
				renderMap(tilemap, window, sfView_getCenter(viewEditor));
				renderMap(propmap, window, sfView_getCenter(viewEditor));
				if (flagEditorUI) renderEditorUI(window, sfRenderWindow_getDefaultView(window), flagEditorMode, font);
				sfRenderWindow_display(window);
			}

			// Opens map editor UI
			if (sfKeyboard_isKeyPressed(KEY_EDITOR_UI)) flagEditorUI = 1;

			// Picks one tile to place on the map whenever the player clicks on the editor UI screen
			if (sfMouse_isButtonPressed(sfMouseLeft) && flagEditorUI){
				flagClick = 1;
				sfVector2f mouseCursor = sfRenderWindow_mapPixelToCoords(window, sfMouse_getPosition(window), sfRenderWindow_getDefaultView(window));
				sfVector2i pos = { ((int)mouseCursor.x - 16) / TILE_PX, ((int)mouseCursor.y - 64) / TILE_PX };
				tileSelection = pos.x + pos.y * 12;
				tileSelection += 64 * flagEditorMode;
				flagEditorUI = 0;

				printf("%d %d", 64 * flagEditorMode, tileSelection);
			}

			// When pressing the pause key (Esc by default):
			if (sfKeyboard_isKeyPressed(KEY_PAUSE)) {
				if (flagEditorUI == 0 && flagEditorLeave == 0) { // If the editor UI is closed, go back to menu
					save_map(tilemap, propmap, playerPos, inventory, bgm);
					sfMusic_play(bgm);
					gameState = MENU;
				}
				else { // Otherwise, just close the editor UI
					flagEditorUI = 0;
					flagEditorLeave = 1;
				}
			}
			else flagEditorLeave = 0;
		}
		else if (gameState == BREAK) { // When pause menu open
			sfRenderWindow_setView(window, sfRenderWindow_getDefaultView(window));
			sfRenderWindow_drawSprite(window, spriteMenuBackground, NULL);
			if (!flagOption){
				sfSprite_setPosition(buttonPauseReturn, (sfVector2f) { 350.0f, 180.0f });

				// Pause menu UI
				sfRenderWindow_drawSprite(window, buttonPauseReturn, NULL); 
				sfRenderWindow_drawSprite(window, buttonPauseOptions, NULL); 
				sfRenderWindow_drawSprite(window, buttonPauseQuit, NULL); 

				if (isClicked(window, buttonPauseReturn)) {
					save_map(tilemap, propmap, playerPos, inventory, bgm);
					gameState = MENU;
				}
				else if (isClicked(window, buttonPauseOptions) && flagClick == 0) {
					flagOption = 1;
					flagClick == 1;
				}
				else if (isClicked(window, buttonPauseQuit) && flagClick == 0) gameState = QUIT;
			}
			else {
				// Options menu UI
				sfSprite_setPosition(buttonPauseReturn, vector2f(250.0f, 300.0f));
				sfRenderWindow_drawSprite(window, buttonOptionsVolPlus, NULL);
                sfRenderWindow_drawSprite(window, buttonOptionsVolMinus, NULL);
				sfRenderWindow_drawSprite(window, buttonPauseReturn, NULL);

				timerVolumeChange += getDeltaTime();
				if (timerVolumeChange > 0.1f) {
					if (isClicked(window, buttonOptionsVolPlus)) changeVolume(bgm, 1);
					else if (isClicked(window, buttonOptionsVolMinus)) changeVolume(bgm, 0);
					timerVolumeChange = 0;
				}
				if (isClicked(window, buttonPauseReturn) && flagClick == 0) {
					flagOption = 0;
					flagClick = 1;
				}
				sprintf_s(txtVolume, 16, "Volume : %.f", sfMusic_getVolume(bgm));
				sfText_setString(textVolume, txtVolume);
				sfRenderWindow_drawText(window, textVolume, NULL);
			}

			if (sfKeyboard_isKeyPressed(KEY_PAUSE)) {
				if (!flagPauseMenu) {
					save_map(tilemap, propmap, playerPos, inventory, bgm);
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
	save_map(tilemap, propmap, playerPos, inventory, bgm);
	printf("gbye");
	return 1;
}
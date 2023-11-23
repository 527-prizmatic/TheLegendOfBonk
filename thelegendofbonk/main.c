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
			///***  = = =  PREINIT  = = =  ***///

	/* == RENDERING ENGINE CORE */
	sfRenderWindow* window = initRender(); // Main window
	sfView* viewGame = initGameView(); // Game mode view
	sfView* viewEditor = initEditorView(); // Editor mode view
	sfView* viewMinimap = initMinimapView(); // Editor mode view
	sfView* viewCredits = initCreditsView(); // Credits mode view

	/* == MAIN MENU ==  */
	sfFont* font = sfFont_createFromFile(TEXTURE_PATH"FontGame.ttf");
	sfVector2f logoPos = vector2f(400.0f, 200.0f);
	sfSprite* logo = initSprite(TEXTURE_PATH"logo.png", vector2f(0.7f, 0.7f), logoPos);
	sfSprite_setOrigin(logo, vector2f(400.0f, 200.0f));
	float logoAnimTimer = 0.0f;

	/* == PAUSE MENU == */
	char txtVolume[16] = "Volume -"; // For volume display in the options screen
	char flagOptions = 0; // Whether the pause menu should display the root menu or the options screen
	char flagPauseMenu = 0; // Used for timer purposes when toggling the pause menu
	char flagClick = 0; // Used for misc timer purposes to check if the left mouse button is being pressed
	sfText* textVolume = initText(font, 30, vector2f(250.0f, 250.0f));

	/* == INTERACTIONS HEADS-UP ==  */
	sfText* sfTxt_interact = initText(font, 30, vector2f(600.f, 460.f));
	formatTextOutline(sfTxt_interact, sfBlack);
	sfText_setString(sfTxt_interact, "Press E !\0");

	/* == INVENTORY == */
	int inventory[4] = { 0, 0, 0, 0 };
	sfSprite* spriteInventory = sfSprite_create();
	sfSprite* spriteDogecoin = sfSprite_create();
	initInventory(spriteInventory, spriteDogecoin);

	/* == MAIN DIALOG BOX == */
	sfText* sfTxt_npc = sfText_create();
	char textNpc[] = "";
	sfRectangleShape* dialogBoxNpc = initDialogBox(sfTxt_npc, font, 20);
	char flagInteraction = 0;
	int checkInteract = 0;

	/* == MISC UI BUTTONS == */
	sfSprite* buttonMainPlay = initSprite(TEXTURE_PATH"play.png", vector2f(3.5f, 3.5f), vector2f(175.0f, 400.0f));
	sfSprite* buttonMainEdit = initSprite(TEXTURE_PATH"edit.png", vector2f(3.5f, 3.5f), vector2f(454.0f, 400.0f));
	sfSprite* buttonMainQuit = initSprite(TEXTURE_PATH"quit.png", vector2f(3.5f, 3.5f), vector2f(314.0f, 485.0f));
	sfSprite* buttonMainCredits = initSprite(TEXTURE_PATH"credits.png", vector2f(2.5f, 2.5f), vector2f(30.0f, 30.0f)); 
	sfSprite* spriteMenuBackground = initSprite(TEXTURE_PATH"background.png", vector2f(1.0f, 1.0f), vector2f(0.0f, 0.0f));
	sfSprite* buttonPauseReturn = initSprite(TEXTURE_PATH"return.png", vector2f(3.5f, 3.5f), vector2f(350.0f, 180.0f));
	sfSprite* buttonPauseOptions = initSprite(TEXTURE_PATH"option.png", vector2f(3.5f, 3.5f), vector2f(350.0f, 250.0f));
	sfSprite* buttonPauseQuit = initSprite(TEXTURE_PATH"quit2.png", vector2f(3.5f, 3.5f), vector2f(350.0f, 320.0f));
	sfSprite* buttonOptionsVolPlus = initSprite(TEXTURE_PATH"vol_plus.png", vector2f(3.5f, 3.5f), vector2f(250.0f, 190.0f));
	sfSprite* buttonOptionsVolMinus = initSprite(TEXTURE_PATH"vol_minus.png", vector2f(3.5f, 3.5f), vector2f(450.0f, 190.0f));
	sfSprite* buttonUICraft = initSprite(TEXTURE_PATH"craft.png", vector2f(2.0f, 2.0f), vector2f(420.0, 465.0f));
	sfColor hoverColor = sfColor_fromRGBA(128, 128, 128, 128); // Color when hovering on buttons

	/* == FOR EFFECTS ON BUTTONS == */
	sfSprite* UIButtons[] = {
		buttonMainPlay,
		buttonMainEdit,
		buttonMainQuit,
		buttonMainCredits, 
		buttonPauseReturn,
		buttonPauseOptions,
		buttonPauseQuit,
		buttonOptionsVolPlus,
		buttonOptionsVolMinus,
		buttonUICraft
	};

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

	/* == BUTTON CLICK SOUND == */
	sfSound* sndButtonClick = sfSound_create();
	sfSoundBuffer* bufferUI = sfSoundBuffer_createFromFile(AUDIO_PATH"click.wav");
	sfSound_setBuffer(sndButtonClick, bufferUI);

	/* == NPCS AND WORLD OBJECTS == */
	sfSprite* bonk = initSprite(TEXTURE_PATH"bonk.png", vector2f(2.0f, 2.0f), vector2f(4000.0f, 68.0f));
	sfSprite* npcCheese = initSprite(TEXTURE_PATH"pnj.png", vector2f(2.0f, 2.0f), vector2f(1655.0f, 2085.0f));
	sfSprite* cage = initSprite(TEXTURE_PATH"cage.png", vector2f(0.3f, 0.3f), vector2f(3970.0f, 20.0f));

	/* == TIMERS & ANIMATION HANDLERS == */
	float bonkAnimTimer = 0.0f;
	char frameBonk = 0;
	sfSprite_setTextureRect(bonk, (sfIntRect) { 0, 0, 32, 32 });
	float npcAnimTimer = 0.0f;
	char frameNpc = 0;
	sfSprite_setTextureRect(npcCheese, (sfIntRect) { 0, 0, 32, 32 });

	/* == DAY/NIGHT CYCLE == */
	sfRectangleShape* nightOverlay = initRectangle(vector2f(0.0f, 0.0f), vector2f(800.0f, 600.0f));
	float timeNight = 0.f;
	float nightFilterAlpha = 96.f;
	const float dayCycleLengthSecs = 240.f;

	/* == CORE INIT == */
	// FOR DEVS - Always keep this at the bottom of the preinit stack
	initTools();
	char tilemap[H_MAP_T][W_MAP_T];
	char propmap[H_MAP_T][W_MAP_T];
	load_map(tilemap, propmap, &playerPos, inventory, bgm);
	initPlayer();
	sfEvent event;
	float tick = 0.0f;
	float tickEnding = 0.0f;


	///***  = = =  GAME LOOP  = = =  ***///
	while (sfRenderWindow_isOpen(window)) {

		// Some core functions
		while (sfRenderWindow_pollEvent(window, &event)) if (event.type == sfEvtClosed) sfRenderWindow_close(window); // Check if window is closed via the WIndows UI
		restartClock();
		sfRenderWindow_clear(window, sfBlack);
		tick += getDeltaTime(); // Ticks game rendering engine
		if (!testLClick(NULL) && flagClick) flagClick = 0; // Technical flag used in misc functions to check if the user is left-clicking somewhere

		// Makes it so that buttons are greyed out when hovering the mouse on them, but only if the game window is currently being focused on
		if (sfRenderWindow_hasFocus(window)) {
			sfVector2i mousePos = sfMouse_getPositionRenderWindow(window);
			for (int i = 0; i < sizeof(UIButtons) / sizeof(sfSprite*); i++) {
				sfSprite* button = UIButtons[i];
				sfFloatRect spriteBounds = sfSprite_getGlobalBounds(button);
				if (sfFloatRect_contains(&spriteBounds, (float) mousePos.x, (float) mousePos.y)) sfSprite_setColor(button, hoverColor);
				else sfSprite_setColor(button, sfWhite);
			}
		}

		/* == MAIN MENU == */
		if (gameState == MENU) {
			/* == RENDERING ENGINE == */
			sfRenderWindow_setView(window, sfRenderWindow_getDefaultView(window));
			if (tick >= TICK_TIME) {
				tick = 0.0f;

				// Main menu UI
				sfRenderWindow_drawSprite(window, spriteMenuBackground, NULL);
				sfRenderWindow_drawSprite(window, logo, NULL);
				sfRenderWindow_drawSprite(window, buttonMainPlay, NULL);
				sfRenderWindow_drawSprite(window, buttonMainEdit, NULL);
				sfRenderWindow_drawSprite(window, buttonMainQuit, NULL);

				sfRenderWindow_drawSprite(window, buttonMainCredits, NULL);
				
				sfRenderWindow_display(window);
			}
			
			
			/* == COMPUTING LOGO ANIMATIONS == */
			logoAnimTimer += getDeltaTime();
			logoPos.y = 200.0f + cosf(logoAnimTimer / 2.f) * 30.0f;
			logoPos.x = 400.0f + sinf(logoAnimTimer / 3.3f) * 70.0f;
			sfSprite_setRotation(logo, cosf(logoAnimTimer * 4.6f) * 3.0f);
			sfSprite_setPosition(logo, logoPos);
			
			
			/* == USER INPUT == */
			// When clicking on the GAME button
			if (isClicked(window, buttonMainPlay)) {
				sfSound_play(sndButtonClick);
				flagInteraction = 0;
				gameState = GAME;
				interactTilePos(propmap);
			}
			// When clicking on the EDIT button
			else if (isClicked(window, buttonMainEdit)) {
				sfSound_play(sndButtonClick);
				gameState = EDITOR;
				flagClick = 1;
			}

			// When clicking on the CREDITS button 
			else if (isClicked(window, buttonMainCredits)) {
				sfSound_play(sndButtonClick);
				gameState = CREDITS;
				flagClick = 1;
			}

			// When clicking on the QUIT button
            else if(isClicked(window, buttonMainQuit)) gameState = QUIT;
		}

		/* == GAME == */
		else if (gameState == GAME) {
			/* == RENDERING ENGINE == */
			timeNight += getDeltaTime(); // Ticks day / night cycle
			if (timeNight >= dayCycleLengthSecs) timeNight -= dayCycleLengthSecs;

			if (tick >= TICK_TIME) {
				tick = 0.0f;

				// Regularly updating a few game variables
				updatePlayer(propmap, window);
				updateView(window, viewGame, playerPos);


				// Sets up a dialog box for when the player interacts with a sign
				checkInteract = canInteract();
				if (checkInteract > 19 && checkInteract != 100) {
					int idNpc = checkInteract - 20;
					updateDialogBox(pnjArray[idNpc].txt, sizeof(pnjArray[idNpc].txt), sfTxt_npc, dialogBoxNpc, (sfVector2f) { 10.0f, 450.0f }, (sfVector2f) { 380.0f, 140.0f }, 0);
					if (testKeyPress(KEY_INTERACT, window)) flagInteraction = 1;
				}
				// Check for interaction with chests when pressing the bound key
				else if (testKeyPress(KEY_INTERACT, window) && checkInteract != -1 && inventory[0] != 2) inventory[checkInteract] = 1;
				

				// Rendering
				sfRenderWindow_setView(window, viewGame); // Rendering on map view
				renderMap(tilemap, window, sfView_getCenter(viewGame), -1, 0); // Rendering map - terrain layer
				renderMap(propmap, window, sfView_getCenter(viewGame), 0, 0); // Rendering map - props layer - background
				displayPlayer(window); // Rendering Bingchilling
				renderMap(propmap, window, sfView_getCenter(viewGame), 1, 0); // Rendering map - props layer - foreground
				sfRenderWindow_drawSprite(window, npcCheese, NULL); // Rendering cheese NPC
				sfRenderWindow_drawSprite(window, bonk, NULL); // Rendering Bonk
				sfRenderWindow_drawSprite(window, cage, NULL); // Rendering cage

				sfRenderWindow_setView(window, sfRenderWindow_getDefaultView(window)); // Now rendering on HUD
				sfRenderWindow_drawRectangleShape(window, nightOverlay, NULL); // Renders nighttime overlay
				displayInventory(window, inventory, spriteInventory, spriteDogecoin); // Rendering inventory HUD
				if (hasAllDogecoinPieces(inventory)) sfRenderWindow_drawSprite(window, buttonUICraft, NULL); // Renders craft button (but only if the dogecoin can be crafted)
				renderMinimap(window, viewMinimap, tilemap, propmap); // Renders minimap

				// Displays "PRESS E" pop-up above inventory bar
				sfRenderWindow_setView(window, sfRenderWindow_getDefaultView(window)); // Now rendering on HUD
				if (checkInteract != -1) {
					if (checkInteract == 100) {
						if (inventory[0] == 2) sfRenderWindow_drawText(window, sfTxt_interact, sfFalse);
					}
					else sfRenderWindow_drawText(window, sfTxt_interact, sfFalse);
				}
				if (flagInteraction == 1) displayDialogBox(window, sfTxt_npc, dialogBoxNpc, sfFalse); // Displays dialog box if need be
				
				sfRenderWindow_display(window);
				
				if (inventory[0] == 2 && testKeyPress(KEY_INTERACT, window) && canInteract() == 100) gameState = ENDING;
			}
			

			/* == ANIMATIONS == */
			bonkAnimTimer += getDeltaTime();
			if (bonkAnimTimer >= 0.1f) {
				bonkAnimTimer = 0.0f;
				
				// Bonk animation
				frameBonk++;
				frameBonk %= 8;
				sfSprite_setTextureRect(bonk, (sfIntRect) { 32 * frameBonk, 0, 32, 32 });
				
				// NPC animation
				frameNpc++;
				frameNpc %= 7; 
				sfSprite_setTextureRect(npcCheese, (sfIntRect) { 32 * frameNpc, 0, 32, 32 }); 
			}

			// Computing day/night cycle & changing lamp post textures accordingly
			nightFilterAlpha = 96.0f - sinf((timeNight / dayCycleLengthSecs) * PI * 2.f) * 1000.f;
			nightFilterAlpha = max(0.f, min(192.0f, nightFilterAlpha));
			sfRectangleShape_setFillColor(nightOverlay, sfColor_fromRGBA(8, 8, 32, (int)nightFilterAlpha));
			if (nightFilterAlpha > 96.0f) selectTexture_lampPost(1); // Lamp posts turn on at night
			else selectTexture_lampPost(0); // Lamp posts turn off at day
			
			// Check for world interactions
			if (canInteract() == -1) flagInteraction = 0;
			
			
			/* == USER INPUT == */
			// Crafting the dogecoin
			if (isClicked(window, buttonUICraft) && hasAllDogecoinPieces(inventory) && inventory[0] != 2) {
				for (int i = 0; i < 4; i++) inventory[i] = 0;
				inventory[0] = 2;
			}

			// Secret debug keybind (ALT+R) which returns the player at the spawn point
			if (sfKeyboard_isKeyPressed(sfKeyLAlt) && testKeyPress(sfKeyR, window) && DEBUG) {
				playerPos.x = 544;
				playerPos.y = 512;
			}
			
			// Pulls out the game menu when pressing the bound key
			if (testKeyPress(KEY_PAUSE, window)) {
				printf("%.2f %.2f", playerPos.x, playerPos.y);
				if (!flagPauseMenu) {
					sfSound_play(sndButtonClick); 
					save_map(tilemap, propmap, playerPos, inventory, bgm);
					gameState = BREAK;
				}
				flagPauseMenu = 1;
			}
			else flagPauseMenu = 0;
		}

		/* == LEVEL EDITOR == */
		else if (gameState == EDITOR) {
			sfMusic_stop(bgm);
			/* == RENDERING ENGINE == */
			if (tick >= TICK_TIME) {
				tick = 0.0f;

				// Places tiles on click
				if (testLClick(window) && !flagClick) {
					if (tileSelection == 91) interactTilePos(propmap);
					changeTile(window, viewEditor, tilemap, propmap, tileSelection);
					flagClick = 0;
				}

				// Rendering
				sfRenderWindow_setView(window, viewEditor);
				updateEditorView(window, viewEditor);
				renderMap(tilemap, window, sfView_getCenter(viewEditor), -1, 0);
				renderMap(propmap, window, sfView_getCenter(viewEditor), -1, 0);
				if (flagEditorUI) renderEditorUI(window, sfRenderWindow_getDefaultView(window), flagEditorMode, font);
				sfRenderWindow_display(window);
			}
			
			/* == USER INPUT == */
			// Toggle editor mode - press 1 for terrain, 2 for props
			if (testKeyPress(sfKeyNum1, window)) flagEditorMode = 0;
			else if (testKeyPress(sfKeyNum2, window)) flagEditorMode = 1;

			// Opens map editor UI
			if (testKeyPress(KEY_EDITOR_UI, window)) flagEditorUI = 1;

			// Picks one tile to place on the map whenever the player clicks on the editor UI screen
			if (testLClick(window) && flagEditorUI) {
				flagClick = 1;
				sfVector2f mouseCursor = sfRenderWindow_mapPixelToCoords(window, sfMouse_getPosition(window), sfRenderWindow_getDefaultView(window));
				sfVector2i pos = { ((int)mouseCursor.x - 16) / TILE_PX, ((int)mouseCursor.y - 64) / TILE_PX };
				tileSelection = pos.x + pos.y * 12;
				tileSelection += 64 * flagEditorMode;
				flagEditorUI = 0;
			}

			// When pressing the pause key (Esc by default):
			if (testKeyPress(KEY_PAUSE, window)) {
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


		/* == PAUSE MENU == */
		else if (gameState == BREAK) { // When pause menu open
			sfRenderWindow_setView(window, sfRenderWindow_getDefaultView(window));

			/* == MAIN SCREEN == */
			if (!flagOptions){
				// Moves the return button to a new position to avoid having to re-declare it
				sfSprite_setPosition(buttonPauseReturn, (sfVector2f) { 350.0f, 180.0f });

				/* == RENDERING ENGINE == */
				if (tick >= TICK_TIME) {
					tick = 0.0f;
					sfSprite_setScale (buttonPauseReturn, (sfVector2f) { 3.5f, 3.5f }); 
					sfRenderWindow_drawSprite(window, spriteMenuBackground, NULL);
					sfRenderWindow_drawSprite(window, buttonPauseReturn, NULL);
					sfRenderWindow_drawSprite(window, buttonPauseOptions, NULL);
					sfRenderWindow_drawSprite(window, buttonPauseQuit, NULL);
					
					sfRenderWindow_display(window);
				}


				/* == USER INPUT == */
				// Returns to the main menu
				if (isClicked(window, buttonPauseReturn)) {
					sfSound_play(sndButtonClick);
					save_map(tilemap, propmap, playerPos, inventory, bgm);
					gameState = MENU;
				}
				// Opens options menu
				else if (isClicked(window, buttonPauseOptions) && flagClick == 0) {
					sfSound_play(sndButtonClick);
					flagOptions = 1;
					flagClick = 1;
				}
				// Quits game
				else if (isClicked(window, buttonPauseQuit) && flagClick == 0) {
					sfSound_play(sndButtonClick);
					gameState = QUIT;
				}
			}

			/* == OPTIONS == */
			else {
				// Moves the return button to a new position to avoid having to re-declare it
				sfSprite_setPosition(buttonPauseReturn, vector2f(250.0f, 300.0f));

				/* == RENDERING ENGINE == */
				if (tick >= TICK_TIME) {
					tick = 0.0f;
					sfRenderWindow_drawSprite(window, spriteMenuBackground, NULL);
					sfRenderWindow_drawSprite(window, buttonOptionsVolPlus, NULL);
					sfRenderWindow_drawSprite(window, buttonOptionsVolMinus, NULL);
					sfRenderWindow_drawSprite(window, buttonPauseReturn, NULL);
					sprintf_s(txtVolume, 16, "Volume : %.f", sfMusic_getVolume(bgm));
					sfText_setString(textVolume, txtVolume);
					sfText_setOutlineThickness(textVolume, 2.0f);
					sfText_setOutlineColor(textVolume, sfBlack);
					sfRenderWindow_drawText(window, textVolume, NULL);
					
					sfRenderWindow_display(window);
				}

				/* == USER INPUT == */
				// Volume control buttons, placed within a timer to allow for slowly lowering volume when holding down the button
				timerVolumeChange += getDeltaTime();
				if (timerVolumeChange > 0.1f) {
					// Volume up
					if (isClicked(window, buttonOptionsVolPlus)) {
						sfSound_play(sndButtonClick);
						changeVolume(bgm, 1);
						timerVolumeChange = 0;
					}
					// Volume down
					else if (isClicked(window, buttonOptionsVolMinus)) {
						sfSound_play(sndButtonClick);
						changeVolume(bgm, 0);
						timerVolumeChange = 0;
					}
				}

				// Goes back to pause menu
				if (isClicked(window, buttonPauseReturn) && flagClick == 0) {
					sfSound_play(sndButtonClick); 
					flagOptions = 0;
					flagClick = 1;
				}
			}

			/* == USER INPUT == */
			// Goes back to game when pressing the bound key
			if (testKeyPress(KEY_PAUSE, window)) {
				if (!flagPauseMenu) {
					sfSound_play(sndButtonClick);
					save_map(tilemap, propmap, playerPos, inventory, bgm);
					flagInteraction = 0;
					flagOptions = 0;
					gameState = GAME;
				}
				flagPauseMenu = 1;
			}
			else flagPauseMenu = 0;
		}

		/* == ENDING SCENE == */ 
		else if (gameState == ENDING) {
			printf("BONK");
		}

		/* == CREDITS == */ 
		else if (gameState == CREDITS) 
		{
			sfRenderWindow_setView(window, sfRenderWindow_getDefaultView(window)); 
			if (tick >= TICK_TIME) { 
				tick = 0.0f;
				sfSprite_setPosition(buttonPauseReturn, (sfVector2f) { 600.0f, 520.0f });
				sfSprite_setScale(buttonPauseReturn, (sfVector2f) { 2.5f, 2.5f });
				sfRenderWindow_drawSprite(window, spriteMenuBackground, NULL); 
				sfRenderWindow_drawSprite(window, buttonPauseReturn, NULL);
				sfRenderWindow_display(window); 
			}
			if (testKeyPress(KEY_PAUSE, window)) gameState = MENU; 
			else if (isClicked(window, buttonPauseReturn)) gameState = MENU; 
		}

		/* == MUCH SAD QUIMT GAME == */
		else if (gameState == QUIT) break;
	}

	sfRenderWindow_close(window);
	save_map(tilemap, propmap, playerPos, inventory, bgm);
	return 1;
}
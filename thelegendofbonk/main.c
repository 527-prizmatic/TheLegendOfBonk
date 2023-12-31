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

#pragma warning (disable: 4090)
#pragma warning (disable: 4133)
#pragma warning (disable: 4244)

int main() {

	

			///***  = = =  PREINIT  = = =  ***///

	/* == RENDERING ENGINE CORE */
	sfRenderWindow* window = initRender(); // Main window
	sfView* viewGame = initGameView(); // Game mode view
	sfView* viewEditor = initEditorView(); // Editor mode view
	sfView* viewMinimap = initMinimapView(); // Editor mode view
	sfView* viewCredits = initCreditsView(); // Credits mode view

    //Change icone .exe 
    sfImage* icon = sfImage_createFromFile(TEXTURE_PATH"icon.png");
    sfRenderWindow_setIcon(window, 64, 64, sfImage_getPixelsPtr(icon));
	
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
	sfSprite* spriteKeyTesla = sfSprite_create();
	initInventory(spriteInventory, spriteDogecoin, spriteKeyTesla);

	/* == MAIN DIALOG BOX == */
	sfText* sfTxt_npc = sfText_create();
	char textNpc[] = "";
	sfRectangleShape* dialogBoxNpc = initDialogBox(sfTxt_npc, font, 20);
	char flagInteraction = 0;
	int checkInteract = 0;

	/* == MISC UI BUTTONS == */
	sfSprite* buttonMainPlay = initSprite(TEXTURE_PATH"play.png", vector2f(3.5f, 3.5f), vector2f(314.0f, 400.0f));
	sfSprite* buttonMainNew = initSprite(TEXTURE_PATH"new.png", vector2f(3.5f, 3.5f), vector2f(135.0f, 400.0f));
	sfSprite* buttonMainEdit = initSprite(TEXTURE_PATH"edit.png", vector2f(3.5f, 3.5f), vector2f(494.0f, 400.0f));
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
    sfSprite* creditsBackground = initSprite(TEXTURE_PATH"creditsMain.png", vector2f(1.0f, 1.0f), vector2f(0.0f, 0.0f));
	/* == FOR EFFECTS ON BUTTONS == */
	sfSprite* UIButtons[] = {
		buttonMainPlay,
		buttonMainNew,
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
	sfMusic* musicCybertruck = sfMusic_createFromFile(AUDIO_PATH"et_cybertruck.wav");
	sfMusic_setVolume(musicCybertruck, 50);
	char flagMusic = 0; // Whether the music is currently playing
	float timerVolumeChange = 0;
	sfMusic_play(bgm);
	sfMusic_setLoop(bgm, sfTrue);

	/* == BUTTON CLICK SOUND == */
	sfSound* sndButtonClick = sfSound_create();
	sfSoundBuffer* bufferUI = sfSoundBuffer_createFromFile(AUDIO_PATH"click.wav");
	sfSound_setBuffer(sndButtonClick, bufferUI);

	sfSound* sndFinal = sfSound_create();
    sfSoundBuffer* bufferFinal = sfSoundBuffer_createFromFile(AUDIO_PATH"final.wav");
    sfSound_setBuffer(sndFinal, bufferFinal);


	/* == ENDING SFX == */
	sfVector2f cagePos;
	sfVector2f bonkPos;
	sfVector2f ctPos;
	sfVector2f emPos;
	float emScale;
	float trigTicker;
	sfClock* clockEnding = sfClock_create();
	sfSound* sndVroom = sfSound_create();
	sfSoundBuffer* bufferVroom = sfSoundBuffer_createFromFile(AUDIO_PATH"vroom.wav");
	sfSound_setBuffer(sndVroom, bufferVroom);
	sfSound* sndBoom = sfSound_create();
	sfSoundBuffer* bufferBoom = sfSoundBuffer_createFromFile(AUDIO_PATH"boom.wav");
	sfSound_setBuffer(sndBoom, bufferBoom);
	sfSound* sndIsHim = sfSound_create();
	sfSoundBuffer* bufferIsHim = sfSoundBuffer_createFromFile(AUDIO_PATH"this_is_elon_musk.wav");
	sfSound_setBuffer(sndIsHim, bufferIsHim);
	sfSound* sndChest = sfSound_create();
    sfSoundBuffer* bufferChest = sfSoundBuffer_createFromFile(AUDIO_PATH"pickup.wav");
    sfSound_setBuffer(sndChest, bufferChest);
	sfSound_setVolume(sndChest, 25);

	float timerEndEsc = 0.f;

	sfSound* sndCage = sfSound_create();
    sfSoundBuffer* bufferCage = sfSoundBuffer_createFromFile(AUDIO_PATH"cage.wav");
    sfSound_setBuffer(sndCage, bufferCage);
    sfSound_setVolume(sndCage, 50);



	/* == CREDITS TEXTS == */
	sfText* txtCredits = initText(font, 30, vector2f(200.f, 425.f));
	char* credits[11] = { "    THE LEGEND OF BONK",
		"               WITH\n  DOGE as BINGCHILLING",
		"        LEVEL DESIGN\n        VALETTE EVAN\n TOUSSAINT J.SEBASTIEN",
		"         PROGRAMMING\n        GELOT MATHIEU\n         VALETTE EVAN\n  TOUSSAINT J.SEBASTIEN",
		"        GRAPHIC DESIGN\n         GELOT MATHIEU\n          VALETTE EVAN",
		"         SOUND DESIGN\n         VALETTE EVAN\n  TOUSSAINT J.SEBASTIEN",
		"            ELON MUSK\n            ELON MUSK",
		"                BONK\n       BALLTZE \"CHEEMS\"",
		"       CREDITS MUSIC\nEXTRA TERRA - CYBERTRUCK",
		"       TO BE CONTINUED...",
		"       TO BE CONTINUED...\n             ...MAYBE"
	};

	/* == NPCS AND WORLD OBJECTS == */
	sfSprite* bonk = initSprite(TEXTURE_PATH"bonk.png", vector2f(2.0f, 2.0f), vector2f(4000.0f, 68.0f));
	sfSprite* npcCheese = initSprite(TEXTURE_PATH"pnj.png", vector2f(2.0f, 2.0f), vector2f(1655.0f, 2085.0f));
	char cheeseTxt[143] = "Hey you over there!\nYou look like you got dogecoin.\nSpare one? I gotta buy myself\nthe newest Tesla.\nI can find you a cool reward\nin exchange.";
	char cheeseTxt2[84] = "YOOOO!!\nFinally I can get that new car!!\nYou can have my old car keys\nin exchange!!";
	char flagCheese = 0;
	sfSprite* cage = initSprite(TEXTURE_PATH"cage.png", vector2f(0.3f, 0.3f), vector2f(3970.0f, 20.0f));
	sfSprite* cybertruck = initSprite(TEXTURE_PATH"cybertruck.png", vector2f(0.2f, 0.2f), vector2f(4500.0f, 40.0f));
	sfSprite* elongatedMuskrat = initSprite(TEXTURE_PATH"muskSmoke.png", vector2f(0.0f, 0.0f), vector2f(4580.0f, 50.0f));

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
		restartClock();
		while (sfRenderWindow_pollEvent(window, &event)) if (event.type == sfEvtClosed) sfRenderWindow_close(window); // Check if window is closed via the Windows UI
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
				sfRenderWindow_drawSprite(window, buttonMainNew, NULL);
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
			// When clicking on the NEW button
			if (isClicked(window, buttonMainNew)) {
				sfSound_play(sndButtonClick);
				flagInteraction = 0;
				load_new_map(tilemap, propmap, &playerPos, inventory, bgm);
				gameState = GAME;
				interactTilePos(tilemap, propmap, bgm);
			}

			// When clicking on the GAME button
			if (isClicked(window, buttonMainPlay)) {
				sfSound_play(sndButtonClick);
				flagInteraction = 0;
				gameState = GAME;
				interactTilePos(tilemap, propmap, bgm);
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
				updatePlayer(tilemap, propmap, window, 1);
				updateView(window, viewGame, playerPos);

				// Sets up a dialog box for when the player interacts with a sign
				checkInteract = canInteract();
				if (checkInteract > 19 && checkInteract != 100 && checkInteract != 200) {
					int idNpc = checkInteract - 20;
					
					updateDialogBox(npcArray[idNpc].txt, sizeof(npcArray[idNpc].txt), sfTxt_npc, dialogBoxNpc, (sfVector2f) { 10.0f, 450.0f }, (sfVector2f) { 380.0f, 140.0f }, 0);
					if (testKeyPress(KEY_INTERACT, window)) {
					  sfSound_play(sndButtonClick); 
					  flagInteraction = 1;
					}
				}
				else if (checkInteract == 200 && !flagCheese && inventory[0] != 3 ) {
					updateDialogBox(cheeseTxt, sizeof(cheeseTxt), sfTxt_npc, dialogBoxNpc, (sfVector2f) { 10.0f, 450.0f }, (sfVector2f) { 380.0f, 140.0f }, 0);
					if (testKeyPress(KEY_INTERACT, window)) flagInteraction = 1;
				}
				
				// Check for interaction with chests when pressing the bound key
				else if (testKeyPress(KEY_INTERACT, window) && checkInteract != -1 && inventory[0] != 2 && inventory[0] != 3) {
					inventory[checkInteract] = 1;
					if (chestArray[checkInteract].flagOpen == 0) sfSound_play(sndChest);
					chestArray[checkInteract].flagOpen = 1;
				}
				
				if (flagCheese) {
					updateDialogBox(cheeseTxt2, sizeof(cheeseTxt2), sfTxt_npc, dialogBoxNpc, (sfVector2f) { 10.0f, 450.0f }, (sfVector2f) { 380.0f, 140.0f }, 0);
					if (testKeyPress(KEY_INTERACT, window)) flagInteraction = 1;
					inventory[0] = 3;
					flagCheese = 0;
					if (sfSound_getStatus(sndChest) == sfStopped && chestArray[checkInteract].flagOpen == 0) sfSound_play(sndChest);
				}
				
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
				displayInventory(window, inventory, spriteInventory, spriteDogecoin, spriteKeyTesla); // Rendering inventory HUD
				if (hasAllDogecoinPieces(inventory)) sfRenderWindow_drawSprite(window, buttonUICraft, NULL); // Renders craft button (but only if the dogecoin can be crafted)
				
				// Displays "PRESS E" pop-up above inventory bar
				if (checkInteract != -1) {
					if (checkInteract == 100) {
						if (inventory[0] == 3) sfRenderWindow_drawText(window, sfTxt_interact, sfFalse);
					}
					if (checkInteract == 200) {
						if ((!hasAllDogecoinPieces(inventory) || inventory[0] == 2) && inventory[0] != 3) sfRenderWindow_drawText(window, sfTxt_interact, sfFalse);
					}
					if (checkInteract < 19 && (inventory[0] == 2 || inventory[0] == 3)) checkInteract = -1;
					//else if (checkInteract == 200 && inventory[0] == 3) continue; 
					else sfRenderWindow_drawText(window, sfTxt_interact, sfFalse);
				}
				if (flagInteraction == 1) displayDialogBox(window, sfTxt_npc, dialogBoxNpc, sfFalse); // Displays dialog box if need be
				
//				renderMinimap(window, viewMinimap, tilemap, propmap); // Renders minimap
				sfRenderWindow_display(window);
				
				if (inventory[0] == 2 && testKeyPress(KEY_INTERACT, window) && checkInteract == 200) flagCheese = 1;
				if (inventory[0] == 3 && testKeyPress(KEY_INTERACT, window) && checkInteract == 100) {
					gameState = ENDING;
					sfClock_restart(clockEnding);
				}
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

				// Chest animations
				for (int i = 0; i < 4; i++) if (chestArray[i].spriteId <= 6 && chestArray[i].flagOpen == 1) chestArray[i].spriteId++;
			}

			// Computing day/night cycle & changing lamp post textures accordingly
			nightFilterAlpha = 96.0f - sinf((timeNight / dayCycleLengthSecs) * PI * 2.f) * 1000.f;
			nightFilterAlpha = max(0.f, min(192.0f, nightFilterAlpha));
			sfRectangleShape_setFillColor(nightOverlay, sfColor_fromRGBA(8, 8, 32, (int)nightFilterAlpha));
			if (nightFilterAlpha > 96.0f) selectTexture_lampPost(1); // Lamp posts turn on at night
			else selectTexture_lampPost(0); // Lamp posts turn off at day

			// Check for world interactions
			if (checkInteract == -1) flagInteraction = 0;
			if (inventory[0] == 2 && testKeyPress(KEY_INTERACT, window) && checkInteract == 100) gameState = ENDING;

			/* == USER INPUT == */
			// Crafting the dogecoin
			if (isClicked(window, buttonUICraft) && hasAllDogecoinPieces(inventory) && inventory[0] != 2) {
				sfSound_play(sndButtonClick); 
				for (int i = 0; i < 4; i++) inventory[i] = 0;
				inventory[0] = 2;
			}

			// Plays a boom sound when opening the cage
			if (testKeyPress(KEY_INTERACT, window) && canInteract() == 200 && inventory[0] == 3 && sfSound_getStatus(sndCage) == sfStopped) sfSound_play(sndCage);

			// Secret debug keybind (ALT+R) which returns the player at the spawn point
			if (sfKeyboard_isKeyPressed(sfKeyLAlt) && testKeyPress(sfKeyR, window) && DEBUG) {
				playerPos.x = 544;
				playerPos.y = 512;
			}

			// Secret debug keybind (ALT+A) which sends the player near the cage
			if (sfKeyboard_isKeyPressed(sfKeyLAlt) && testKeyPress(sfKeyA, window) && DEBUG) {
				playerPos.x = 3968;
				playerPos.y = 150;
			}
			
			// Pulls out the game menu when pressing the bound key
			if (testKeyPress(KEY_PAUSE, window)) {
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
					if (tileSelection == 91) interactTilePos(tilemap, propmap, bgm);
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
			sfMusic_stop(bgm);

			cagePos = sfSprite_getPosition(cage);
			bonkPos = sfSprite_getPosition(bonk);
			ctPos = sfSprite_getPosition(cybertruck);
			emPos = sfSprite_getPosition(elongatedMuskrat);
			emScale = sfSprite_getScale(elongatedMuskrat).x;

			if (tickEnding == 0) {
				playerPos.x = cagePos.x - 40;
				playerPos.y = bonkPos.y;
				frameY = LEFT;
			}

			tickEnding = sfTime_asSeconds(sfClock_getElapsedTime(clockEnding));
			tick += getDeltaTime();
			logoAnimTimer += getDeltaTime();
			
			if (testKeyPress(sfKeyEscape, window)) {
				timerEndEsc += getDeltaTime();
				if (timerEndEsc >= 3.f) {
					endingPlayerPos();
					if (sfMusic_getStatus(musicCybertruck) == sfPlaying) sfMusic_stop(musicCybertruck);
					sfMusic_play(bgm);
					sfMusic_setLoop(bgm, sfTrue);
					gameState = MENU;
				}
			}
			else timerEndEsc = 0.f;

			if (tick >= TICK_TIME) {
				tick = 0.f;
				trigTicker = (tickEnding - 2) * 4 * PI;
				
				/* == CUTSCENE SCRIPT == */
				if (tickEnding <= 2.f) {
					cagePos.y -= .33f;
					updateView(window, viewGame, bonkPos);
				}
				// play cage sound instantly
                if (tickEnding > 0.f && tickEnding <= 0.01f) if (sfSound_getStatus(sndCage) != sfPlaying) sfSound_play(sndFinal);
				
				
				if (tickEnding > 2.f && tickEnding <= 2.25f) bonkPos.y -= cos(trigTicker) * 2;
				if (tickEnding > 2.25f && tickEnding <= 2.5f) bonkPos.y += cos(trigTicker) * 2;
				if (tickEnding > 2.75f && tickEnding <= 3.f) playerPos.y += cos(trigTicker) * 2;
				if (tickEnding > 3.f && tickEnding <= 3.25f) playerPos.y -= cos(trigTicker) * 2;
				if (tickEnding > 3.25f && tickEnding <= 3.5f) {
					playerPos.x += .5f;
					bonkPos.x += .5f;
				}
				if (tickEnding > 3.25f && tickEnding <= 7.462f) {
					playerPos.x += sin(-trigTicker) * 2;
					playerPos.y -= cos(trigTicker) * 2;
					bonkPos.x += sin(trigTicker) * 2;
					bonkPos.y += cos(trigTicker) * 2;
				}

				if (tickEnding > 3.75f && tickEnding <= 3.76f) if (sfSound_getStatus(sndVroom) != sfPlaying) sfSound_play(sndVroom);
				if (tickEnding > 4.f && tickEnding <= 4.25f) playerPos.y -= cos(trigTicker) * 2;
				if (tickEnding > 4.25f && tickEnding <= 4.5f) playerPos.y += cos(trigTicker) * 2;
				if (tickEnding > 5.5f && tickEnding <= 5.75f) bonkPos.y -= cos(trigTicker) * 2;
				if (tickEnding > 5.75f && tickEnding <= 6.f) bonkPos.y += cos(trigTicker) * 2;
				if (tickEnding > 6.5f && tickEnding <= 6.75f) playerPos.y -= cos(trigTicker) * 2;
				if (tickEnding > 6.75f && tickEnding <= 7.f) playerPos.y += cos(trigTicker) * 2;
				if (tickEnding > 7.05f && ctPos.x > 3900.f) {
					ctPos.x -= 7.f;
					emPos.x -= 7.f;
				}
				
				if (tickEnding > 7.43f && tickEnding <= 8.5f) {
					playerPos.x -= 4.f;
					playerPos.y -= 0.4f;
					bonkPos.x -= 4.f;
					bonkPos.y -= 0.7f;
					sfSprite_setRotation(player, sfSprite_getRotation(player) + 2);
					sfSprite_setRotation(bonk, sfSprite_getRotation(bonk) - 2);
				}
				if (tickEnding > 7.03f && tickEnding <= 7.04f) if (sfSound_getStatus(sndIsHim) != sfPlaying) sfSound_play(sndIsHim);
				if (tickEnding > 7.43f && tickEnding <= 7.44f) if (sfSound_getStatus(sndBoom) != sfPlaying) sfSound_play(sndBoom);
				if (tickEnding > 7.462f && tickEnding < 7.472f) sfSound_stop(sndVroom);
				if (tickEnding > 9.25f && tickEnding <= 9.26f) emScale = 0.1f;
				if (tickEnding > 12.f && tickEnding <= 12.01f) if (sfMusic_getStatus(musicCybertruck) != sfPlaying) sfMusic_play(musicCybertruck);

				if (tickEnding > 13.f && tickEnding <= 16.f) {
					endingPlayerPos();
					sfText_setString(txtCredits, credits[0]);
				}
				if (tickEnding > 16.f && tickEnding <= 19.f) sfText_setString(txtCredits, credits[1]);
				if (tickEnding > 19.f && tickEnding <= 22.f) sfText_setString(txtCredits, credits[2]);
				if (tickEnding > 22.f && tickEnding <= 25.f) sfText_setString(txtCredits, credits[3]);
				if (tickEnding > 25.f && tickEnding <= 28.f) sfText_setString(txtCredits, credits[4]);
				if (tickEnding > 28.f && tickEnding <= 31.f) sfText_setString(txtCredits, credits[5]);
				if (tickEnding > 31.f && tickEnding <= 34.f) sfText_setString(txtCredits, credits[6]);
				if (tickEnding > 34.f && tickEnding <= 37.f) sfText_setString(txtCredits, credits[7]);
				if (tickEnding > 37.f && tickEnding <= 40.f) sfText_setString(txtCredits, credits[8]);
				if (tickEnding > 40.f && tickEnding <= 46.f) sfText_setString(txtCredits, credits[9]);
				if (tickEnding > 46.f && tickEnding <= 48.f) sfText_setString(txtCredits, credits[10]);

				// Updates
				// updateView(window, viewGame,  vector2f(4500.f, 300.f));
				sfSprite_setPosition(player, playerPos);
				sfSprite_setPosition(bonk, bonkPos);
				sfSprite_setPosition(cage, cagePos);
				sfSprite_setPosition(cybertruck, ctPos);
				sfSprite_setPosition(elongatedMuskrat, emPos);
				sfSprite_setScale(elongatedMuskrat, vector2f(emScale, emScale));
				sfText_setColor(txtCredits, sfWhite);

				if (tickEnding <= 12.f){
					// Rendering
					sfRenderWindow_setView(window, viewGame); // Rendering on map view
					renderMap(tilemap, window, vector2f(4500.f, 0.f), -1, 2); // Rendering map - terrain layer
					renderMap(propmap, window, vector2f(4500.f, 0.f), 0, 2); // Rendering map - props layer - background
					displayPlayer(window); // Rendering Bingchilling
					sfRenderWindow_drawSprite(window, bonk, NULL); // Rendering Bonk
					if (tickEnding <= 2.f) sfRenderWindow_drawSprite(window, cage, NULL); // Rendering cage
					if (tickEnding > 6.f) sfRenderWindow_drawSprite(window, cybertruck, NULL); // Rendering the cybertruck
					if (tickEnding > 6.f) sfRenderWindow_drawSprite(window, elongatedMuskrat, NULL); // Rendering Elon
					renderMap(propmap, window, vector2f(4500.f, 0.f), 1, 2); // Rendering map - props layer - foreground
					sfRenderWindow_drawRectangleShape(window, nightOverlay, NULL); // Renders nighttime overlay
				}
				else if (tickEnding > 13.f && tickEnding <= 47.25f) {
					sfRenderWindow_setView(window, sfRenderWindow_getDefaultView(window)); // Rendering on window
					sfRenderWindow_drawSprite(window, logo, NULL);

					/* == COMPUTING LOGO ANIMATIONS == */
					logoAnimTimer += getDeltaTime();
					logoPos.y = 200.0f + cosf(logoAnimTimer / 2.f) * 30.0f;
					logoPos.x = 400.0f + sinf(logoAnimTimer / 3.3f) * 70.0f;
					sfSprite_setRotation(logo, cosf(logoAnimTimer * 4.6f) * 3.0f);
					sfSprite_setPosition(logo, logoPos);

					sfRenderWindow_drawText(window, txtCredits, NULL);
				}

				sfRenderWindow_display(window);

				if (tickEnding > 50.f) {
					sfMusic_stop(musicCybertruck);
					sfMusic_play(bgm);
					sfMusic_setLoop(bgm, sfTrue);
					gameState = MENU;
				}
			}
		}

		/* == CREDITS == */ 
		else if (gameState == CREDITS) {
			sfRenderWindow_setView(window, sfRenderWindow_getDefaultView(window)); 
			if (tick >= TICK_TIME) { 
				tick = 0.0f;
				sfSprite_setPosition(buttonPauseReturn, (sfVector2f) { 600.0f, 520.0f });
				sfSprite_setScale(buttonPauseReturn, (sfVector2f) { 2.5f, 2.5f });
				sfRenderWindow_drawSprite(window, spriteMenuBackground, NULL);
				sfRenderWindow_drawSprite(window, creditsBackground, NULL);
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
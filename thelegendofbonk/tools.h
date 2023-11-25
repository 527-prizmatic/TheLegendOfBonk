#pragma once
#include "SFML/Graphics.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#define TEXTURE_PATH "..\\assets\\textures\\"
#define AUDIO_PATH "..\\assets\\audio\\"

#define TICKSPEED 120
#define TICK_TIME 1 / (float)TICKSPEED
#define PI (float)3.1415926535

#define DEBUG 00

#define KEY_UP sfKeyZ
#define KEY_DOWN sfKeyS
#define KEY_LEFT sfKeyQ
#define KEY_RIGHT sfKeyD
#define KEY_PAUSE sfKeyEscape
#define KEY_INTERACT sfKeyE
#define KEY_EDITOR_UI sfKeyEnter
#define KEY_CREDITS sfKeyC

typedef enum GameState {
	MENU,
	GAME,
	EDITOR,
	BREAK,
	CREDITS,
	ENDING,
	QUIT
} GameState;

GameState gameState;

/// Initializes misc tools for handling time.
void initTools();

/// Restarts the game's internal clock, for time-tracking purposes.
void restartClock();

/// \return Time elapsed since last restartClock() call
float getDeltaTime();

/// Quick sfVector2f constructor
sfVector2f vector2f(float _x, float _y);

/// \return Whether the mouse pointer is currently within the display window
sfBool isMouseWithinWindow(sfRenderWindow* _w);

/// Utility function to quickly initialize rectangle shape objects.
/// \param _pos - Where to display the rectangle on screen
/// \param _size - Rectangle size
/// \return Pointer to an initialized rectangle shape object
sfRectangleShape* initRectangle(sfVector2f _pos, sfVector2f _size);

/// Utility function to quickly initialize sprite objects.
/// \param _texture_path - Path to sprite texture file
/// \param _scale - Sprite scale
/// \param _pos - Where to display the sprite on screen
/// \return Pointer to an initialized sprite object
sfSprite* initSprite(char* _texture_path, sfVector2f _scale, sfVector2f _pos);

/// Utility function to quickly initialize text objects.
/// \param _font - Font object to use
/// \param _size - Text size
/// \param _pos - Where to display the sprite on screen
/// \return Pointer to an initialized text object
sfText* initText(sfFont* _font, int _size, sfVector2f _pos);

/// Utility function to quickly apply a simple outline style to text objects.
/// \param _txt - Text object to format
/// \param _color - Outline color
void formatTextOutline(sfText* _txt, sfColor _color);

/// Checks if the given key has been pressed. If a non-NULL object is passed as argument, the function also checks for focus.
sfBool testKeyPress(sfKeyCode _key, sfRenderWindow* _w);

/// Checks if the left mouse button is being pressed. If a non-NULL object is passed as argument, the function also checks for focus.
sfBool testLClick(sfRenderWindow* _w);
#pragma once
#include "render.h"

sfVector2f playerPos ;

typedef enum moveDir {
	UP,
	LEFT,
	DOWN,
	RIGHT
} moveDir;

/* Initializes the player character's sprite, stats and inventory. */
void initPlayer();

/* Input tracking and movement functions
*  \param _map[][] - An initialized tilemap */
void updatePlayer(char _map[H_MAP_T][W_MAP_T]);

/* Checks the player's surroundings for a potential collision with a solid block.
*  \param _map[][] - An initialized tilemap
*  \param _dir - Direction towards which to check for a collision */
sfBool checkForCollisions(char _map[H_MAP_T][W_MAP_T], moveDir _dir);

void movePlayer(moveDir _dir, sfBool _isDiag);

/* Renders player character's sprite in the game window.
*  \param _window - The window to display the sprite on */
void displayPlayer(sfRenderWindow* _window);
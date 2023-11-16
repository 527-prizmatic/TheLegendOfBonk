#pragma once
#include "render.h"

sfVector2f playerPos;

typedef enum moveDir {
	UP,
	LEFT,
	DOWN,
	RIGHT
} moveDir;

/* Initializes the player character's sprite, stats and inventory. */
void initPlayer();

/* Input tracking and movement functions.
*  \param _map - An initialized tilemap */
void updatePlayer(char _map[H_MAP_T][W_MAP_T]);

/* Checks the player's surroundings for a potential collision with a solid block.
*  \param _map - An initialized tilemap
*  \param _dir - Direction towards which to check for a collision */
sfBool checkForCollisions(char _map[H_MAP_T][W_MAP_T], moveDir _dir);

/* Checks if the player character is in water.
*  \param _map - An initialized tilemap */
sfBool isInWater(char _map[H_MAP_T][W_MAP_T]);

/* Handles player movement.
*  \param _dir - Movement direction
*  \param _isDiag - Should we divide speed by the square root of two for the sake of keeping diagonal movement balanced? */
void movePlayer(moveDir _dir, sfBool _isDiag, char _map[H_MAP_T][W_MAP_T]);

/* Renders player character's sprite in the game window.
*  \param _window - The window to display the sprite on */
void displayPlayer(sfRenderWindow* _window);
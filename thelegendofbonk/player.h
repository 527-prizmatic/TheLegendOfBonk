#pragma once
#include "render.h"

/* Initializes the player character's sprite, stats and inventory. */
void initPlayer();

/* Input tracking and movement functions */
void updatePlayer();

int updateInventory();

/* Renders player character's sprite in the game window.
*  \param _window - The window to display the sprite on */
void displayPlayer(sfRenderWindow* _window);
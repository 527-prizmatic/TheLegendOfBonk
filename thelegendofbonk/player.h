#pragma once
#include "render.h"

sfVector2f playerPos ;

/* Initializes the player character's sprite, stats and inventory. */
void initPlayer();

/* Input tracking and movement functions */
void updatePlayer();

void updateInventory();

/* Renders player character's sprite in the game window.
*  \param _window - The window to display the sprite on */
void displayPlayer(sfRenderWindow* _window);
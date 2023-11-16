#pragma once
#include "tools.h"

/* Initializes the inventory HUD's textures.
*  \param _inventorySprite - A sprite object for use as the inventory slots' backdrop
*  \param _keySprite - A sprite object for use as item icons */
void initInventory(sfSprite* _inventorySprite, sfSprite* _keySprite);

/* Renders the inventory HUD.
*  \param _window - A render window
*  \param _inventorySprite - A sprite object for use as the inventory slots' backdrop
*  \param _keySprite - A sprite object for use as item icons */
void displayInventory(sfRenderWindow* _window, int* _inventory, sfSprite* _inventorySprite, sfSprite* _keySprite);

sfBool hasAllKeyPieces(int _inv[4]);
#pragma once
#include "tools.h"

/* Initializes the inventory HUD's textures.
*  \param _inventorySprite - A sprite object for use as the inventory slots' backdrop
*  \param _keySprite - A sprite object for use as item icons */
void initInventory(sfSprite* _inventorySprite, sfSprite* _keySprite);

/* A debug function which allows to manually give oneself items
*  \param _inventory - An inventory array
*  \param _keySprite - A sprite object for use as item icons */
void updateInventory(int* _inventory, sfSprite* _keySprite);

/* Renders the inventory HUD.
*  \param _window - A render window
*  \param _inventorySprite - A sprite object for use as the inventory slots' backdrop
*  \param _keySprite - A sprite object for use as item icons */
void displayInventory(sfRenderWindow* _window, sfSprite* _inventorySprite, sfSprite* _keySprite);
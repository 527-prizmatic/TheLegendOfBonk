#pragma once
#include "tools.h"


sfSprite* initSprite();
void initInventory(sfSprite* _inventorySprite, sfSprite* _keySprite, sfRectangleShape* _craftButton, sfText* _craftText);
void displayInventory(sfRenderWindow* _window, int* _inventory, sfSprite* _inventorySprite, sfSprite* _keySprite, sfRectangleShape* _craftButton, sfText* _craftText);

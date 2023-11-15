#pragma once
#include "tools.h"


sfSprite* initSprite();
void initInventory(sfSprite* _inventorySprite, sfSprite* _keySprite);
void updateInventory(int* _inventory, sfSprite* _keySprite);
void displayInventory(sfRenderWindow* _window, sfSprite* _inventorySprite, sfSprite* _keySprite);

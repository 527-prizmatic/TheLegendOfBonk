#include "inventory.h"

void initInventory(sfSprite* _inventorySprite, sfSprite* _keySprite)
{
    sfTexture* inventoryTexture;

    inventoryTexture = sfTexture_createFromFile(TEXTURE_PATH"inventory.png", NULL);
    sfSprite_setTexture(_inventorySprite, inventoryTexture, sfTrue);
    sfSprite_setScale(_inventorySprite, (sfVector2f) { 3.0f, 3.0f });
    sfSprite_setPosition(_inventorySprite, (sfVector2f) { 280.0f, 280.0f });

    sfTexture* keyTexture;

    keyTexture = sfTexture_createFromFile(TEXTURE_PATH"key.png", NULL);
    sfSprite_setTexture(_keySprite, keyTexture, sfTrue);
    sfSprite_setScale(_keySprite, (sfVector2f) { 1.0f, 1.0f });
    sfSprite_setTextureRect(_keySprite, (sfIntRect){ 0, 0, 50, 50 });
    sfSprite_setPosition(_keySprite, (sfVector2f) { 680.0f, 500.0f });
}

void updateInventory(int* _inventory, sfSprite* _keySprite)
{
    sfIntRect rect = { 0, 0, 50, 50 };
    int valRect=0;

    if (sfKeyboard_isKeyPressed(sfKeyI)) _inventory[0] = 1;
    if (sfKeyboard_isKeyPressed(sfKeyO)) _inventory[1] = 1;
    if (sfKeyboard_isKeyPressed(sfKeyP)) _inventory[2] = 1;
    if (sfKeyboard_isKeyPressed(sfKeyM)) _inventory[3] = 1;

    for (int i = 0; i < 4 ; i++)
    {
        valRect += _inventory[i];
    }

    rect.left = valRect * 50;
    sfSprite_setTextureRect(_keySprite, rect);
    sfSprite_setPosition(_keySprite, (sfVector2f) { 440.0f, 500.0f });

    if (_inventory[0] && _inventory[1] && _inventory[2] && _inventory[3])
    {
        printf("WIN !\n");
    }
}

void displayInventory(sfRenderWindow* _window, sfSprite* _inventorySprite, sfSprite* _keySprite)
{
    sfRenderWindow_setView(_window, sfRenderWindow_getDefaultView(_window));
    sfRenderWindow_drawSprite(_window, _inventorySprite, NULL);
    sfRenderWindow_drawSprite(_window, _keySprite, NULL);
}

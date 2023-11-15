#include "inventory.h"

sfSprite* initSprite()
{
    sfSprite* _sprite = sfSprite_create();
    return _sprite;
}

void initInventory(sfSprite* _inventorySprite, sfSprite* _keySprite)
{
    sfTexture* inventoryTexture;

    inventoryTexture = sfTexture_createFromFile(TEXTURE_PATH"inventory.png", NULL);
    sfSprite_setTexture(_inventorySprite, inventoryTexture, sfTrue);
    sfSprite_setScale(_inventorySprite, (sfVector2f) { 3.0f, 3.0f });
    sfSprite_setPosition(_inventorySprite, (sfVector2f) { 280.0f, 280.0f });

    sfTexture* keyTexture;

    keyTexture = sfTexture_createFromFile(TEXTURE_PATH"inventory.png", NULL);
    sfSprite_setTexture(_inventorySprite, keyTexture, sfTrue);
    sfSprite_setScale(_inventorySprite, (sfVector2f) { 3.0f, 3.0f });
    sfSprite_setPosition(_inventorySprite, (sfVector2f) { 280.0f, 280.0f });
}

void updateInventory(int* _inventory)
{
    if (sfKeyboard_isKeyPressed(sfKeyI)) { _inventory[0] = 1; }
    if (sfKeyboard_isKeyPressed(sfKeyO)) { _inventory[1] = 1; }
    if (sfKeyboard_isKeyPressed(sfKeyP)) { _inventory[2] = 1; }
    if (sfKeyboard_isKeyPressed(sfKeyM)) { _inventory[3] = 1; }

    if (_inventory[0] == 1 && _inventory[1] == 1 && _inventory[2] == 1 && _inventory[3] == 1)
    {
        printf("WIN !\n");
    }
}

void displayInventory(sfRenderWindow* _window, sfSprite* _sprite) {
    sfRenderWindow_setView(_window, sfRenderWindow_getDefaultView(_window));
    sfRenderWindow_drawSprite(_window, _sprite, NULL);
}

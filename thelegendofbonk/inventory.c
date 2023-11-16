#include "inventory.h"

sfSprite* initSprite()
{
    return sfSprite_create();
}

void initInventory(sfSprite* _inventorySprite, sfSprite* _keySprite) {
    // TEXTURE INVENTAIRE
    sfTexture* inventoryTexture;

    inventoryTexture = sfTexture_createFromFile(TEXTURE_PATH"inventory.png", NULL);
    sfSprite_setTexture(_inventorySprite, inventoryTexture, sfTrue);
    sfSprite_setScale(_inventorySprite, (sfVector2f) { 3.0f, 3.0f });
    sfSprite_setPosition(_inventorySprite, (sfVector2f) { 280.0f, 280.0f });

    // TEXTURE CLE
    sfTexture* keyTexture;

    keyTexture = sfTexture_createFromFile(TEXTURE_PATH"key.png", NULL);
    sfSprite_setTexture(_keySprite, keyTexture, sfTrue);
    sfSprite_setScale(_keySprite, (sfVector2f) { 1.0f, 1.0f });
    sfSprite_setTextureRect(_keySprite, (sfIntRect) { 0, 0, 50, 50 });
    sfSprite_setPosition(_keySprite, (sfVector2f) { 680.0f, 500.0f });
}

void displayInventory(sfRenderWindow* _window, int* _inventory, sfSprite* _inventorySprite, sfSprite* _keySprite)
{
    sfIntRect rect = { 0, 0, 50, 50 };

    sfRenderWindow_setView(_window, sfRenderWindow_getDefaultView(_window));
    sfRenderWindow_drawSprite(_window, _inventorySprite, NULL);
    if (sfKeyboard_isKeyPressed(sfKeyI)) _inventory[0] = 1;
    if (sfKeyboard_isKeyPressed(sfKeyO)) _inventory[1] = 1;
    if (sfKeyboard_isKeyPressed(sfKeyP)) _inventory[2] = 1;
    if (sfKeyboard_isKeyPressed(sfKeyM)) _inventory[3] = 1;
    if (sfKeyboard_isKeyPressed(sfKeyN))
    {
        for (int i = 0; i < 4; i++)
        {
            _inventory[i] = 1;
        }
    }
    if (sfKeyboard_isKeyPressed(sfKeyB))
    {
        for (int i = 0; i < 4; i++)
        {
            _inventory[i] = 0;
        }
    }
    
    if (_inventory[0])
    {
        rect.left = 0;
        sfSprite_setTextureRect(_keySprite, rect);
        sfSprite_setPosition(_keySprite, (sfVector2f) { 440.0f, 500.0f });
        sfRenderWindow_drawSprite(_window, _keySprite, NULL);
    }
    if (_inventory[1])
    {
        rect.left = 50;
        sfSprite_setTextureRect(_keySprite, rect);
        sfSprite_setPosition(_keySprite, (sfVector2f) { 530.0f, 500.0f });
        sfRenderWindow_drawSprite(_window, _keySprite, NULL);
    }
    if (_inventory[2])
    {
        rect.left = 100;
        sfSprite_setTextureRect(_keySprite, rect);
        sfSprite_setPosition(_keySprite, (sfVector2f) { 620.0f, 500.0f });
        sfRenderWindow_drawSprite(_window, _keySprite, NULL);
    }
    if (_inventory[3])
    {
        rect.left = 150;
        sfSprite_setTextureRect(_keySprite, rect);
        sfSprite_setPosition(_keySprite, (sfVector2f) { 700.0f, 500.0f });
        sfRenderWindow_drawSprite(_window, _keySprite, NULL);
    }
}

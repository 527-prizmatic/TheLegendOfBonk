#include "inventory.h"

void initInventory(sfSprite* _inventorySprite, sfSprite* _keySprite, sfRectangleShape* _craftButton, sfText* _craftText) {
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
    sfSprite_setTextureRect(_keySprite, (sfIntRect){ 0, 0, 50, 50 });
    sfSprite_setPosition(_keySprite, (sfVector2f) { 680.0f, 500.0f });

    // CRAFT BUTTON
    sfFont* font = sfFont_createFromFile(TEXTURE_PATH"3Dventure.ttf");

    sfText_setFont(_craftText, font);
    sfText_setCharacterSize(_craftText, 20);
    sfText_setFillColor(_craftText, sfBlack);
    sfText_setPosition(_craftText, (sfVector2f) { 430.0f, 470.0f });
    sfText_setString(_craftText, " Craft !");

    // Adapter taille dialogBox 

    sfRectangleShape_setPosition(_craftButton, (sfVector2f) { 430.0f, 470.0f });
    sfRectangleShape_setFillColor(_craftButton, sfWhite);
    sfRectangleShape_setOutlineColor(_craftButton, sfBlack);
    sfRectangleShape_setOutlineThickness(_craftButton, 2);
    sfRectangleShape_setSize(_craftButton, (sfVector2f) { 90.0f, 30.0f });
}

void displayInventory(sfRenderWindow* _window, int* _inventory, sfSprite* _inventorySprite, sfSprite* _keySprite, sfRectangleShape* _craftButton, sfText* _craftText)
{
    sfIntRect rect = { 0, 0, 50, 50 };

    sfRenderWindow_setView(_window, sfRenderWindow_getDefaultView(_window));
    sfRenderWindow_drawSprite(_window, _inventorySprite, NULL);
    if (sfKeyboard_isKeyPressed(sfKeyI)) _inventory[0] = 1;
    if (sfKeyboard_isKeyPressed(sfKeyO)) _inventory[1] = 1;
    if (sfKeyboard_isKeyPressed(sfKeyP)) _inventory[2] = 1;
    if (sfKeyboard_isKeyPressed(sfKeyM)) _inventory[3] = 1;
    
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

    if (_inventory[0] && _inventory[1] && _inventory[2] && _inventory[3] )
    {
        sfRenderWindow_drawRectangleShape(_window, _craftButton, sfFalse);
        sfRenderWindow_drawText(_window, _craftText, sfFalse);
    }
}

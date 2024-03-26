#include "inventory.h"

void initInventory(sfSprite* _inventorySprite, sfSprite* _dogecoinSprite, sfSprite* _keyTeslaSprite) {
    // TEXTURE INVENTAIRE
    sfTexture* inventoryTexture = sfTexture_createFromFile(TEXTURE_PATH"inventory.png", NULL);
    sfSprite_setTexture(_inventorySprite, inventoryTexture, sfTrue);
    sfSprite_setScale(_inventorySprite, (sfVector2f) { 3.0f, 3.0f });
    sfSprite_setPosition(_inventorySprite, (sfVector2f) { 280.0f, 280.0f });

    // TEXTURE DOGECOIN
    sfTexture* keyTexture = sfTexture_createFromFile(TEXTURE_PATH"key.png", NULL);
    sfSprite_setTexture(_dogecoinSprite, keyTexture, sfTrue);
    sfSprite_setScale(_dogecoinSprite, (sfVector2f) { 2.0f, 2.0f });
    sfSprite_setPosition(_dogecoinSprite, (sfVector2f) { 650.0f, 500.0f });

<<<<<<< HEAD
    keyTexture = sfTexture_createFromFile(TEXTURE_PATH"key.png", NULL);
    sfSprite_setTexture(_keySprite, keyTexture, sfTrue);
    setScale(_keySprite, (sfVector2f) { 2.0f, 2.0f });
    sfSprite_setPosition(_keySprite, (sfVector2f) { 650.0f, 500.0f });
}

void displayInventory(sfRenderWindow* _window, int* _inventory, sfSprite* _inventorySprite, sfSprite* _keySprite)
{
    sfIntRect rect = { 0, 0, 32, 32 };

=======
    // TEXTURE KEY
    sfTexture* keyTeslaTexture = sfTexture_createFromFile(TEXTURE_PATH"keyTesla.png", NULL);
    sfSprite_setTexture(_keyTeslaSprite, keyTeslaTexture, sfTrue);
    sfSprite_setPosition(_keyTeslaSprite, (sfVector2f) { 510.0f, 508.0f });
    sfSprite_setScale(_keyTeslaSprite, (sfVector2f) { 0.16f, 0.16f });
}

void displayInventory(sfRenderWindow* _window, int* _inventory, sfSprite* _inventorySprite, sfSprite* _dogecoinSprite, sfSprite* _keyTeslaSprite) {
    sfIntRect rect = { 0, 0, 32, 32 };
	
>>>>>>> a1b689888de1b8e55f361d1ad46d1c7013ce22ea
    sfRenderWindow_setView(_window, sfRenderWindow_getDefaultView(_window));
    sfRenderWindow_drawSprite(_window, _inventorySprite, NULL);
    
<<<<<<< HEAD
    if (_inventory[0])
    {
        if (_inventory[0] == 2)
        {
            rect.left = 0;
            sfSprite_setTextureRect(_keySprite, rect);
            sfSprite_setPosition(_keySprite, (sfVector2f) { 440.0f, 490.0f });
            sfRenderWindow_drawSprite(_window, _keySprite, NULL);
=======
    if (_inventory[0]) {
        if (_inventory[0] == 2) {
            rect.left = rect.width * 4;
            sfSprite_setTextureRect(_dogecoinSprite, rect);
            sfSprite_setPosition(_dogecoinSprite, (sfVector2f) { 443.0f, 515.0f });
            sfSprite_setScale(_dogecoinSprite, (sfVector2f) { 1.7f, 1.7f });
            sfRenderWindow_drawSprite(_window, _dogecoinSprite, NULL);
>>>>>>> a1b689888de1b8e55f361d1ad46d1c7013ce22ea
        }
        else if (_inventory[0] == 3) sfRenderWindow_drawSprite(_window, _keyTeslaSprite, NULL);
        else {
            rect.left = 0;
            sfSprite_setTextureRect(_dogecoinSprite, rect);
            sfSprite_setPosition(_dogecoinSprite, (sfVector2f) { 450.0f, 520.0f });
            sfRenderWindow_drawSprite(_window, _dogecoinSprite, NULL);
        }
    }
<<<<<<< HEAD
    if (_inventory[1])
    {
        rect.left = rect.width*1;
        sfSprite_setTextureRect(_keySprite, rect);
        sfSprite_setPosition(_keySprite, (sfVector2f) { 530.0f, 490.0f });
        sfRenderWindow_drawSprite(_window, _keySprite, NULL);
=======
    if (_inventory[1]) {
        rect.left = rect.width * 1;
        sfSprite_setTextureRect(_dogecoinSprite, rect);
        sfSprite_setPosition(_dogecoinSprite, (sfVector2f) { 500.0f, 520.0f });
        sfRenderWindow_drawSprite(_window, _dogecoinSprite, NULL);
>>>>>>> a1b689888de1b8e55f361d1ad46d1c7013ce22ea
    }
    if (_inventory[2]) {
        rect.left = rect.width * 2;
<<<<<<< HEAD
        sfSprite_setTextureRect(_keySprite, rect);
        sfSprite_setPosition(_keySprite, (sfVector2f) { 585.0f, 495.0f });
        sfRenderWindow_drawSprite(_window, _keySprite, NULL);
=======
        sfSprite_setTextureRect(_dogecoinSprite, rect);
        sfSprite_setPosition(_dogecoinSprite, (sfVector2f) { 585.0f, 495.0f });
        sfRenderWindow_drawSprite(_window, _dogecoinSprite, NULL);
>>>>>>> a1b689888de1b8e55f361d1ad46d1c7013ce22ea
    }
    if (_inventory[3]) {
        rect.left = rect.width * 3;
        sfSprite_setTextureRect(_dogecoinSprite, rect);
        sfSprite_setPosition(_dogecoinSprite, (sfVector2f) { 695.0f, 495.0f });
        sfRenderWindow_drawSprite(_window, _dogecoinSprite, NULL);
    }
}

sfBool hasAllDogecoinPieces(int _inv[4]) {
    if (_inv[0] == 1 && _inv[1] == 1 && _inv[2] == 1 && _inv[3] == 1) return sfTrue;
    else return sfFalse;
}
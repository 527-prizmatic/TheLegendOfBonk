#include "enemy.h"

sfSprite* badDoggo;
sfTexture* badDoggoSpriteSheet;
sfIntRect badDoggoIrect = { 0, 0, 128, 128 };

float badDoggoAnimTime;
int badDoggoFrameX;
int badDoggoFrameY;

sfVector2f badDoggoPos = { 600.0f, 550.0f };
const float badDoggoSpeed = 520.0f;

void initEnemy()
{
    badDoggo = sfSprite_create();
    badDoggoSpriteSheet = sfTexture_createFromFile("..\\assets\\textures\\badDoggo.png", NULL);
    sfSprite_setTexture(badDoggo, badDoggoSpriteSheet, sfTrue);
    sfSprite_setTextureRect(badDoggo, badDoggoIrect);
    sfSprite_setScale(badDoggo, vector2f(0.5f, 0.5f));
    sfSprite_setPosition(badDoggo, badDoggoPos);

    badDoggoAnimTime = 0.0f;
    badDoggoFrameX = 0;
    badDoggoFrameY = 0;
}

void updateEnemy()
{
    int playerRadius = 60;
    int enemyRadius = 100;
    int sqrPosEnemyX = 0;
    int sqrPosEnemyY = 0;
    int sqrRadius = (playerRadius + enemyRadius) * (playerRadius + enemyRadius);

    sqrPosEnemyX = (playerPos.x - badDoggoPos.x) * (playerPos.x - badDoggoPos.x);
    sqrPosEnemyY = (playerPos.y - badDoggoPos.y) * (playerPos.y - badDoggoPos.y);
    if (sqrPosEnemyX + sqrPosEnemyY < sqrRadius) enemyChasing();
}

void enemyChasing()
{
    float move = badDoggoSpeed * TICK_TIME;
    switch (direction) {
    case UP: 
        badDoggoPos.y -= move;
        break;
    case RIGHT: 
        badDoggoPos.x += move;
        break;
    case DOWN: 
        badDoggoPos.y += move;
        break;
    case LEFT: 
        badDoggoPos.x -= move;
        break;
    }
    
    sfSprite_setPosition(badDoggo, badDoggoPos);
}

void displayEnemy(sfRenderWindow* _window)
{
    sfRenderWindow_drawSprite(_window, badDoggo, NULL);
}

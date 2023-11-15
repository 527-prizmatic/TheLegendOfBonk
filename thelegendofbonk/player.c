#include <math.h>

#include "player.h"
#include "SFML/Graphics.h"
#include "map.h"

#define KEY_UP sfKeyZ
#define KEY_DOWN sfKeyS
#define KEY_LEFT sfKeyQ
#define KEY_RIGHT sfKeyD

#define DISPLAY_HITBOX sfFalse

sfSprite* player;
sfTexture* spriteSheet;
sfIntRect irect = { 0, 0, 32, 32 };

float animTime;
int frameX;
int frameY;
sfBool isMoving; 

sfVector2f playerPos = { 20.0f, 20.0f };
const float playerSpeed = 3.5f;
sfRectangleShape* playerHitbox;

sfVector2f vector2f(float _x, float _y)
{
	return (sfVector2f) { _x, _y };
}

void initPlayer() 
{
    player = sfRectangleShape_create();  
    sfRectangleShape_setSize(player, (sfVector2f){48, 48});
    sfRectangleShape_setFillColor(player, sfWhite);	 
    sfSprite_setPosition(player, playerPos);

    animTime = 0.0f;
    frameX = 0;
    frameY = 0; 
    isMoving = sfFalse;

    playerHitbox = sfRectangleShape_create();
    if (DISPLAY_HITBOX) {
        sfRectangleShape_setOutlineColor(playerHitbox, sfRed);
        sfRectangleShape_setFillColor(playerHitbox, sfTransparent);
        sfRectangleShape_setOutlineThickness(playerHitbox, 2);
    }
}

void updatePlayer(char _map[H_MAP_T][W_MAP_T]) {

    //animation
    isMoving = sfFalse;
    
    // Diagonal movement
    if (sfKeyboard_isKeyPressed(KEY_UP) && sfKeyboard_isKeyPressed(KEY_LEFT)) {
        if (!checkForCollisions(_map, UP)) movePlayer(UP, sfTrue);
        if (!checkForCollisions(_map, LEFT)) movePlayer(LEFT, sfTrue);
    }
    else if (sfKeyboard_isKeyPressed(KEY_DOWN) && sfKeyboard_isKeyPressed(KEY_LEFT)) {
        if (!checkForCollisions(_map, DOWN)) movePlayer(DOWN, sfTrue);
        if (!checkForCollisions(_map, LEFT)) movePlayer(LEFT, sfTrue);
    }
    else if (sfKeyboard_isKeyPressed(KEY_DOWN) && sfKeyboard_isKeyPressed(KEY_RIGHT)) {
        if (!checkForCollisions(_map, DOWN)) movePlayer(DOWN, sfTrue);
        if (!checkForCollisions(_map, RIGHT)) movePlayer(RIGHT, sfTrue);
    }
    else if (sfKeyboard_isKeyPressed(KEY_UP) && sfKeyboard_isKeyPressed(KEY_RIGHT)) {
        if (!checkForCollisions(_map, UP)) movePlayer(UP, sfTrue);
        if (!checkForCollisions(_map, RIGHT)) movePlayer(RIGHT, sfTrue);
    }

    // Orthonormal movement
    else if (sfKeyboard_isKeyPressed(KEY_UP)) { if (!checkForCollisions(_map, UP)) movePlayer(UP, sfFalse); }
    else if (sfKeyboard_isKeyPressed(KEY_DOWN)) { if (!checkForCollisions(_map, DOWN)) movePlayer(DOWN, sfFalse); }
    else if (sfKeyboard_isKeyPressed(KEY_LEFT)) { if (!checkForCollisions(_map, LEFT)) movePlayer(LEFT, sfFalse); }
    else if (sfKeyboard_isKeyPressed(KEY_RIGHT)) { if (!checkForCollisions(_map, RIGHT)) movePlayer(RIGHT, sfFalse); }
    

    if (isMoving)
    {
        if (animTime > 1.5)
        {
            frameX = (frameX + 1) % 4;
            irect.left = frameX * irect.width;
            irect.top = frameY * irect.height;
            sfSprite_setTextureRect(player, irect);
            animTime = 0.0f;
        }
    }
    else
    {
        frameX = 0;
        irect.left = 0;
        irect.top = frameY * irect.height;
        sfSprite_setTextureRect(player, irect);
    }
    sfSprite_setPosition(player, playerPos);


    //animation

    

    sfSprite_setPosition(player, playerPos);
}

sfBool isSolidBlock(char _id) {
    switch (_id) {
    case 3: return sfTrue;
    default: return sfFalse;
    }
}

sfBool checkForCollisions(char _map[H_MAP_T][W_MAP_T], moveDir _dir) {
    sfFloatRect hitbox = sfRectangleShape_getGlobalBounds(player);
    hitbox.left += hitbox.width * 0.1;
    hitbox.top += hitbox.height * 0.1;
    hitbox.width *= 0.8;
    hitbox.height *= 0.8;
    sfRectangleShape_setSize(playerHitbox, (sfVector2f) { hitbox.width, hitbox.height });
    sfRectangleShape_setPosition(playerHitbox, (sfVector2f) { hitbox.left, hitbox.top });

    // printf("{ %.2f %.2f %.2f %.2f }\n", hitbox.left, hitbox.top, hitbox.height, hitbox.width);

    if (_dir == UP) {
        int blockAbove = trunc((hitbox.top - playerSpeed * 1.1) / TILE_PX);
        int cornerTL = trunc(hitbox.left / TILE_PX);
        int cornerTR = trunc((hitbox.left + hitbox.width) / TILE_PX);
        if (isSolidBlock(_map[blockAbove][cornerTL]) || isSolidBlock(_map[blockAbove][cornerTR])) return sfTrue;
    }
    else if (_dir == DOWN) {
        int blockBelow = trunc((hitbox.top + hitbox.height + playerSpeed * 1.1) / TILE_PX);
        int cornerBL = trunc(hitbox.left / TILE_PX);
        int cornerBR = trunc((hitbox.left + hitbox.width) / TILE_PX);
        if (isSolidBlock(_map[blockBelow][cornerBL]) || isSolidBlock(_map[blockBelow][cornerBR])) return sfTrue;
    }
    else if (_dir == LEFT) {
        int blockLeft = trunc((hitbox.left - playerSpeed * 1.1) / TILE_PX);
        int cornerTL = trunc(hitbox.top / TILE_PX);
        int cornerBL = trunc((hitbox.top + hitbox.height) / TILE_PX);
        if (isSolidBlock(_map[cornerTL][blockLeft]) || isSolidBlock(_map[cornerBL][blockLeft])) return sfTrue;
    }
    else if (_dir == RIGHT) {
        int blockRight = trunc((hitbox.left + hitbox.width + playerSpeed * 1.1) / TILE_PX);
        int cornerTR = trunc(hitbox.top / TILE_PX);
        int cornerBR = trunc((hitbox.top + hitbox.height) / TILE_PX);
        if (isSolidBlock(_map[cornerTR][blockRight]) || isSolidBlock(_map[cornerBR][blockRight])) return sfTrue;
    }

    return sfFalse;
}

void movePlayer(moveDir _dir, sfBool _isDiag) {
    float move = playerSpeed * getDeltaTime();
    if (_isDiag) move /= sqrt(2);
    switch (_dir) {
    case UP: frameY = DOWN; playerPos.y -= move; animTime += getDeltaTime(); isMoving = sfTrue; break;
        case RIGHT:frameY = LEFT; playerPos.x += move; animTime += getDeltaTime(); isMoving = sfTrue; break; 
        case DOWN: frameY = UP; playerPos.y += move; animTime += getDeltaTime(); isMoving = sfTrue; break;
        case LEFT: frameY = RIGHT;playerPos.x -= move; animTime += getDeltaTime(); isMoving = sfTrue; break; 
    }

}

void displayPlayer(sfRenderWindow* _window) {
	if (player != NULL) {
        sfSprite_setPosition(player, playerPos);
		sfRenderWindow_drawSprite(_window, player, NULL);
        if (DISPLAY_HITBOX) sfRenderWindow_drawRectangleShape(_window, playerHitbox, NULL);
	}
}


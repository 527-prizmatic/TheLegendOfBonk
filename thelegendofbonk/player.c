#include <math.h>

#include "player.h"
#include "SFML/Graphics.h"
#include "map.h"
#include "tools.h"
#include "textures.h"

#define DISPLAY_HITBOX sfFalse

sfSprite* player;
sfTexture* spriteSheet;
sfIntRect irect = { 0, 0, 32, 32 };

float animTime;
int frameX;
int frameY;
sfBool isMoving; 

sfVector2f playerPos = { 20.0f, 20.0f };
const float playerSpeed = 500.0f;
sfRectangleShape* playerHitbox;

void initPlayer() 
{
    player = sfSprite_create();
    spriteSheet = sfTexture_createFromFile("..\\assets\\textures\\spriteSheet.png", NULL);
    sfSprite_setTexture(player, spriteSheet, sfTrue);
    sfSprite_setTextureRect(player, irect);
    sfSprite_setScale(player, vector2f(2.0f, 2.0f));
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

void updatePlayer(char _map[H_MAP_T][W_MAP_T], sfRenderWindow* _w) {

    //animation
    animTime += TICK_TIME;
    
    // Diagonal movement
    if (sfRenderWindow_hasFocus(_w)) {
        if (sfKeyboard_isKeyPressed(KEY_UP) && sfKeyboard_isKeyPressed(KEY_LEFT)) {
            if (!checkForCollisions(_map, UP)) movePlayer(UP, sfTrue, _map, _w);
            if (!checkForCollisions(_map, LEFT)) movePlayer(LEFT, sfTrue, _map, _w);
        }
        else if (sfKeyboard_isKeyPressed(KEY_DOWN) && sfKeyboard_isKeyPressed(KEY_LEFT)) {
            if (!checkForCollisions(_map, DOWN)) movePlayer(DOWN, sfTrue, _map, _w);
            if (!checkForCollisions(_map, LEFT)) movePlayer(LEFT, sfTrue, _map, _w);
        }
        else if (sfKeyboard_isKeyPressed(KEY_DOWN) && sfKeyboard_isKeyPressed(KEY_RIGHT)) {
            if (!checkForCollisions(_map, DOWN)) movePlayer(DOWN, sfTrue, _map, _w);
            if (!checkForCollisions(_map, RIGHT)) movePlayer(RIGHT, sfTrue, _map, _w);
        }
        else if (sfKeyboard_isKeyPressed(KEY_UP) && sfKeyboard_isKeyPressed(KEY_RIGHT)) {
            if (!checkForCollisions(_map, UP)) movePlayer(UP, sfTrue, _map, _w);
            if (!checkForCollisions(_map, RIGHT)) movePlayer(RIGHT, sfTrue, _map, _w);
        }

        // Orthonormal movement
        else if (sfKeyboard_isKeyPressed(KEY_UP)) { if (!checkForCollisions(_map, UP)) movePlayer(UP, sfFalse, _map, _w); }
        else if (sfKeyboard_isKeyPressed(KEY_DOWN)) { if (!checkForCollisions(_map, DOWN)) movePlayer(DOWN, sfFalse, _map, _w); }
        else if (sfKeyboard_isKeyPressed(KEY_LEFT)) { if (!checkForCollisions(_map, LEFT)) movePlayer(LEFT, sfFalse, _map, _w); }
        else if (sfKeyboard_isKeyPressed(KEY_RIGHT)) { if (!checkForCollisions(_map, RIGHT)) movePlayer(RIGHT, sfFalse, _map, _w); }

        else isMoving = sfFalse;
    }
    else isMoving = sfFalse;

    // Loop back when hitting map borders
    if (sfKeyboard_isKeyPressed(KEY_LEFT) && playerPos.x + 32 <= 0) playerPos.x += W_MAP_PX + 32;
    else if (sfKeyboard_isKeyPressed(KEY_RIGHT) && playerPos.x + 32 >= W_MAP_PX) playerPos.x -= W_MAP_PX + 32;

    if (sfKeyboard_isKeyPressed(KEY_UP) && playerPos.y + 32 <= 0) playerPos.y += H_MAP_PX + 32;
    else if (sfKeyboard_isKeyPressed(KEY_DOWN) && playerPos.y + 32 >= H_MAP_PX) playerPos.y -= H_MAP_PX + 32;
    
    if (isMoving) {
        if (animTime > 0.1f) {
            frameX = (frameX + 1) % 4;
            irect.left = frameX * irect.width;
            irect.top = frameY * irect.height;
            animTime = 0.0f;
        }
    }
    else {
        frameX = 0;
        irect.left = 0;
        irect.top = frameY * irect.height;
    }
    sfSprite_setTextureRect(player, irect);
    sfSprite_setPosition(player, playerPos);
}

sfBool checkForCollisions(char _map[H_MAP_T][W_MAP_T], moveDir _dir) {
    sfFloatRect hitbox = sfSprite_getGlobalBounds(player);
    hitbox.left += hitbox.width * 0.2;
    hitbox.top += hitbox.height * 0.5;
    hitbox.width *= 0.6;
    hitbox.height *= 0.4;
    sfRectangleShape_setSize(playerHitbox, vector2f(hitbox.width, hitbox.height));
    sfRectangleShape_setPosition(playerHitbox, vector2f(hitbox.left, hitbox.top));

    if (_dir == UP) {
        int blockAbove = trunc((hitbox.top - playerSpeed * 2.1 * TICK_TIME) / TILE_PX);
        int cornerTL = trunc(hitbox.left / TILE_PX);
        int cornerTR = trunc((hitbox.left + hitbox.width) / TILE_PX); 
        if (isSolidBlock(_map[blockAbove][cornerTL]) || isSolidBlock(_map[blockAbove][cornerTR])) {
            isMoving = sfFalse;
            return sfTrue;
        }
    }
    else if (_dir == DOWN) {
        int blockBelow = trunc((hitbox.top + hitbox.height + playerSpeed * 2.1 * TICK_TIME) / TILE_PX);
        int cornerBL = trunc(hitbox.left / TILE_PX);
        int cornerBR = trunc((hitbox.left + hitbox.width) / TILE_PX);
        if (isSolidBlock(_map[blockBelow][cornerBL]) || isSolidBlock(_map[blockBelow][cornerBR])) {
            isMoving = sfFalse;
            return sfTrue;
        }
    }
    else if (_dir == LEFT) {
        int blockLeft = trunc((hitbox.left - playerSpeed * 2.1 * TICK_TIME) / TILE_PX);

        if (blockLeft % W_MAP_T == 0) return sfFalse;
        int cornerTL = trunc(hitbox.top / TILE_PX);
        int cornerBL = trunc((hitbox.top + hitbox.height) / TILE_PX);
        if (isSolidBlock(_map[cornerTL][blockLeft]) || isSolidBlock(_map[cornerBL][blockLeft])) {
            isMoving = sfFalse;
            return sfTrue;
        }
    }
    else if (_dir == RIGHT) {
        int blockRight = trunc((hitbox.left + hitbox.width + playerSpeed * 2.1 * TICK_TIME) / TILE_PX);

        if (blockRight % W_MAP_T == 0) return sfFalse;
        int cornerTR = trunc(hitbox.top / TILE_PX);
        int cornerBR = trunc((hitbox.top + hitbox.height) / TILE_PX);
        if (isSolidBlock(_map[cornerTR][blockRight]) || isSolidBlock(_map[cornerBR][blockRight])) {
            isMoving = sfFalse;
            return sfTrue;
        }
    }
    return sfFalse;
}

sfBool isInWater(char _map[H_MAP_T][W_MAP_T]) {
    sfFloatRect hitbox = sfSprite_getGlobalBounds(player);
    hitbox.left += hitbox.width * 0.2;
    hitbox.top += hitbox.height * 0.5;
    hitbox.width *= 0.6;
    hitbox.height *= 0.4;

    int x = trunc((hitbox.top + hitbox.height / 2) / TILE_PX);
    int y = trunc((hitbox.left + hitbox.width / 2) / TILE_PX);

    if (isWater(_map[x][y])) return sfTrue;
    else return sfFalse;
}

void movePlayer(moveDir _dir, sfBool _isDiag, char _map[H_MAP_T][W_MAP_T], sfRenderWindow* _w) {
    float move = playerSpeed * TICK_TIME;
    if (_isDiag) move /= sqrt(2);
    if (isInWater(_map)) move *= 0.25f;
    if (sfKeyboard_isKeyPressed(sfKeyLShift)) move *= 2;
    isMoving = sfTrue;
    switch (_dir) {
        case UP: frameY = DOWN; playerPos.y -= move; break;
        case RIGHT:frameY = LEFT; playerPos.x += move; break; 
        case DOWN: frameY = UP; playerPos.y += move; break;
        case LEFT: frameY = RIGHT; playerPos.x -= move;  break; 
    }
}

void displayPlayer(sfRenderWindow* _window) {
	if (player != NULL) {
        sfSprite_setPosition(player, playerPos);
		sfRenderWindow_drawSprite(_window, player, NULL);
        if (DISPLAY_HITBOX) sfRenderWindow_drawRectangleShape(_window, playerHitbox, NULL);
	}
}
 

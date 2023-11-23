#include <math.h>
#include "SFML/Audio.h"
#include "player.h"
#include "SFML/Graphics.h"
#include "map.h"
#include "tools.h"
#include "textures.h"

moveDir direction;
sfSprite* player;
sfTexture* spriteSheet;
sfIntRect irect = { 0, 0, 32, 32 };

float animTime;
int frameX;
int frameY;
sfBool isMoving; 

sfVector2f playerPos = { 20.0f, 20.0f };
const float playerSpeed = 1250.0f * (1 + (DEBUG * 4));
sfRectangleShape* playerHitbox;

/* == WALK SOUND*/
sfSoundBuffer* sndWalkBuffer; 
sfSound* sndWalk;

void initPlayer() {
    player = sfSprite_create();
    spriteSheet = sfTexture_createFromFile("..\\assets\\textures\\spriteSheet.png", NULL);
    sfSprite_setTexture(player, spriteSheet, sfTrue);
    sfSprite_setTextureRect(player, irect);
    sfSprite_setScale(player, vector2f(2.0f, 2.0f));
    sfSprite_setPosition(player, playerPos);

    sndWalk = sfSound_create();
	sndWalkBuffer = sfSoundBuffer_createFromFile(AUDIO_PATH"walk.wav");
	sfSound_setBuffer(sndWalk, sndWalkBuffer);
	
    animTime = 0.0f;
    frameX = 0;
    frameY = 0; 
    isMoving = sfFalse;

    if (DEBUG) {
        playerHitbox = sfRectangleShape_create();
        sfRectangleShape_setOutlineColor(playerHitbox, sfRed);
        sfRectangleShape_setFillColor(playerHitbox, sfTransparent);
        sfRectangleShape_setOutlineThickness(playerHitbox, 2);
    }
}

void updatePlayer(char _map[H_MAP_T][W_MAP_T], sfRenderWindow* _w, char _canMove) {
    // Ticking animation
    animTime += TICK_TIME;
    if (testKeyPress(sfKeyLShift, _w)) animTime += TICK_TIME / 2.f;
    
    if (_canMove) {
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

            // Orthogonal movement
            else if (sfKeyboard_isKeyPressed(KEY_UP)) { direction = UP; if (!checkForCollisions(_map, direction)) movePlayer(direction, sfFalse, _map, _w); }
            else if (sfKeyboard_isKeyPressed(KEY_DOWN)) { direction = DOWN; if (!checkForCollisions(_map, direction)) movePlayer(direction, sfFalse, _map, _w); }
            else if (sfKeyboard_isKeyPressed(KEY_LEFT)) { direction = LEFT; if (!checkForCollisions(_map, direction)) movePlayer(direction, sfFalse, _map, _w); }
            else if (sfKeyboard_isKeyPressed(KEY_RIGHT)) { direction = RIGHT; if (!checkForCollisions(_map, direction)) movePlayer(direction, sfFalse, _map, _w); }
            else isMoving = sfFalse;
        }
        else isMoving = sfFalse;

        // Loop back when hitting map borders
        if (sfKeyboard_isKeyPressed(KEY_LEFT) && playerPos.x + 32 <= 0) playerPos.x += W_MAP_PX + 32;
        else if (sfKeyboard_isKeyPressed(KEY_RIGHT) && playerPos.x + 32 >= W_MAP_PX) playerPos.x -= W_MAP_PX + 32;

        if (sfKeyboard_isKeyPressed(KEY_UP) && playerPos.y + 32 <= 0) playerPos.y += H_MAP_PX + 32;
        else if (sfKeyboard_isKeyPressed(KEY_DOWN) && playerPos.y + 32 >= H_MAP_PX) playerPos.y -= H_MAP_PX + 32;
    }
    else isMoving = sfFalse;
    
    // Computing animations
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

    if (isMoving == sfFalse) sfSound_stop(sndWalk);
    sfSprite_setTextureRect(player, irect);

    // Move player to given point
    sfSprite_setPosition(player, playerPos);
}

sfBool checkForCollisions(char _map[H_MAP_T][W_MAP_T], moveDir _dir) {
    sfFloatRect hitbox = sfSprite_getGlobalBounds(player);
    hitbox.left += hitbox.width * .2f;
    hitbox.top += hitbox.height * .5f;
    hitbox.width *= .6f;
    hitbox.height *= .4f;
    if (DEBUG) {
        sfRectangleShape_setSize(playerHitbox, vector2f(hitbox.width, hitbox.height));
        sfRectangleShape_setPosition(playerHitbox, vector2f(hitbox.left, hitbox.top));
    }

    if (_dir == UP) {
        int blockAbove = (int) trunc((hitbox.top - playerSpeed * 2.1 * TICK_TIME) / TILE_PX);
        int cornerTL = (int) trunc(hitbox.left / TILE_PX);
        int cornerTR = (int) trunc((hitbox.left + hitbox.width) / TILE_PX); 
        if (isSolidBlock(_map[blockAbove][cornerTL]) || isSolidBlock(_map[blockAbove][cornerTR])) {
            isMoving = sfFalse;
            return sfTrue;
        }
    }
    else if (_dir == DOWN) {
        int blockBelow = (int) trunc((hitbox.top + hitbox.height + playerSpeed * 2.1 * TICK_TIME) / TILE_PX);
        int cornerBL = (int) trunc(hitbox.left / TILE_PX);
        int cornerBR = (int) trunc((hitbox.left + hitbox.width) / TILE_PX);
        if (isSolidBlock(_map[blockBelow][cornerBL]) || isSolidBlock(_map[blockBelow][cornerBR])) {
            isMoving = sfFalse;
            return sfTrue;
        }
    }
    else if (_dir == LEFT) {
        int blockLeft = (int) trunc((hitbox.left - playerSpeed * 2.1 * TICK_TIME) / TILE_PX);

        if (blockLeft % W_MAP_T == 0) return sfFalse;
        int cornerTL = (int) trunc(hitbox.top / TILE_PX);
        int cornerBL = (int) trunc((hitbox.top + hitbox.height) / TILE_PX);
        if (isSolidBlock(_map[cornerTL][blockLeft]) || isSolidBlock(_map[cornerBL][blockLeft])) {
            isMoving = sfFalse;
            return sfTrue;
        }
    }
    else if (_dir == RIGHT) {
        int blockRight = (int) trunc((hitbox.left + hitbox.width + playerSpeed * 2.1 * TICK_TIME) / TILE_PX);

        if (blockRight % W_MAP_T == 0) return sfFalse;
        int cornerTR = (int) trunc(hitbox.top / TILE_PX);
        int cornerBR = (int) trunc((hitbox.top + hitbox.height) / TILE_PX);
        if (isSolidBlock(_map[cornerTR][blockRight]) || isSolidBlock(_map[cornerBR][blockRight])) {
            isMoving = sfFalse;
            return sfTrue;
        }
    }
    return sfFalse;
}

sfBool isInWater(char _map[H_MAP_T][W_MAP_T]) {
    sfFloatRect hitbox = sfSprite_getGlobalBounds(player);
    hitbox.left += hitbox.width * .2f;
    hitbox.top += hitbox.height * .5f;
    hitbox.width *= .6f;
    hitbox.height *= .4f;

    int x = (int) trunc((hitbox.top + hitbox.height / 2) / TILE_PX);
    int y = (int) trunc((hitbox.left + hitbox.width / 2) / TILE_PX);

    if (isWater(_map[x][y])) return sfTrue;
    else return sfFalse;
}

void movePlayer(moveDir _dir, sfBool _isDiag, char _map[H_MAP_T][W_MAP_T], sfRenderWindow* _w) {
    float move = playerSpeed * TICK_TIME;
    if (_isDiag) move /= sqrtf(2);
    if (isInWater(_map)) move *= 0.25f;
    if (testKeyPress(sfKeyLShift, _w)) move *= 2;
    isMoving = sfTrue;

    if (sfSound_getStatus(sndWalk) == sfStopped) {
		sfSound_play(sndWalk);
	}

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
        if (DEBUG) sfRenderWindow_drawRectangleShape(_window, playerHitbox, NULL);
	}
}
 

#include <math.h>

#include "player.h"
#include "SFML/Graphics.h"
#include "map.h"

#define KEY_UP sfKeyZ
#define KEY_DOWN sfKeyS
#define KEY_LEFT sfKeyQ
#define KEY_RIGHT sfKeyD

#define DISPLAY_HITBOX sfFalse

sfRectangleShape* player;
sfVector2f playerPos = { 20.0f, 20.0f };
const float playerSpeed = 3.5f;
sfRectangleShape* playerHitbox;

int inventory[4] = {0, 0, 0, 0};   

sfVector2f vector2f(float _x, float _y)
{
	return (sfVector2f) { _x, _y };
}

void initPlayer() {
    player = sfRectangleShape_create();  
    sfRectangleShape_setSize(player, (sfVector2f){50, 60});
    sfRectangleShape_setFillColor(player, sfWhite);	  
    sfSprite_setPosition(player, playerPos);

        playerHitbox = sfRectangleShape_create();
    if (DISPLAY_HITBOX) {
        sfRectangleShape_setOutlineColor(playerHitbox, sfRed);
        sfRectangleShape_setFillColor(playerHitbox, sfTransparent);
        sfRectangleShape_setOutlineThickness(playerHitbox, 2);
    }
}

void updatePlayer(char _map[H_MAP_T][W_MAP_T]) {
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
    else return;

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
        printf("%d %d %d\n", blockAbove, cornerTL, cornerTR);
        if (isSolidBlock(_map[blockAbove][cornerTL]) || isSolidBlock(_map[blockAbove][cornerTR])) return sfTrue;
    }
    else if (_dir == DOWN) {
        int blockBelow = trunc((hitbox.top + hitbox.height + playerSpeed * 1.1) / TILE_PX);
        int cornerBL = trunc(hitbox.left / TILE_PX);
        int cornerBR = trunc((hitbox.left + hitbox.width) / TILE_PX);
        printf("%d %d %d\n", blockBelow, cornerBL, cornerBR);
        if (isSolidBlock(_map[blockBelow][cornerBL]) || isSolidBlock(_map[blockBelow][cornerBR])) return sfTrue;
    }
    else if (_dir == LEFT) {
        int blockLeft = trunc((hitbox.left - playerSpeed * 1.1) / TILE_PX);
        int cornerTL = trunc(hitbox.top / TILE_PX);
        int cornerBL = trunc((hitbox.top + hitbox.height) / TILE_PX);
        printf("%d %d %d\n", blockLeft, cornerTL, cornerBL);
        if (isSolidBlock(_map[cornerTL][blockLeft]) || isSolidBlock(_map[cornerBL][blockLeft])) return sfTrue;
    }
    else if (_dir == RIGHT) {
        int blockRight = trunc((hitbox.left + hitbox.width + playerSpeed * 1.1) / TILE_PX);
        int cornerTR = trunc(hitbox.top / TILE_PX);
        int cornerBR = trunc((hitbox.top + hitbox.height) / TILE_PX);
        printf("%d %d %d\n", blockRight, cornerTR, cornerBR);
        if (isSolidBlock(_map[cornerTR][blockRight]) || isSolidBlock(_map[cornerBR][blockRight])) return sfTrue;
    }

    return sfFalse;
}

void movePlayer(moveDir _dir, sfBool _isDiag) {
    float move = playerSpeed * getDeltaTime();
    if (_isDiag) move /= sqrt(2);
    switch (_dir) {
        case UP: playerPos.y -= move; break;
        case DOWN: playerPos.y += move; break;
        case LEFT: playerPos.x -= move; break;
        case RIGHT: playerPos.x += move; break;
    }
}

int updateInventory()
{
    if (sfKeyboard_isKeyPressed(sfKeyI)) { inventory[0] = 1; } 
    if (sfKeyboard_isKeyPressed(sfKeyO)) { inventory[1] = 1; } 
    if (sfKeyboard_isKeyPressed(sfKeyP)) { inventory[2] = 1; } 
    if (sfKeyboard_isKeyPressed(sfKeyM)) { inventory[3] = 1; } 

    //printf("inventory : %d %d %d %d\n", inventory[0], inventory[1], inventory[2], inventory[3]);

    if (inventory[0] == 1 && inventory[1] == 1 && inventory[2] == 1 && inventory[3] == 1) {
        printf("WIN !\n");
        return 1;
    }
    else return 0;
}

void displayPlayer(sfRenderWindow* _window) {
	if (player != NULL) {
        sfSprite_setPosition(player, playerPos);
		sfRenderWindow_drawRectangleShape(_window, player, NULL);
        if (DISPLAY_HITBOX) sfRenderWindow_drawRectangleShape(_window, playerHitbox, NULL);
	}
}


#include <math.h>

#include "player.h"
#include "SFML/Graphics.h"

#define KEY_UP sfKeyZ
#define KEY_DOWN sfKeyS
#define KEY_LEFT sfKeyQ
#define KEY_RIGHT sfKeyD

sfRectangleShape* player;
sfVector2f playerPos = { 20.0f, 20.0f };;
const float playerSpeed = 3.5f;

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
}


void updatePlayer() {
    // Diagonal movement
    if (sfKeyboard_isKeyPressed(KEY_UP) && sfKeyboard_isKeyPressed(KEY_LEFT)) {
        playerPos.y -= playerSpeed * getDeltaTime() / sqrt(2);
        playerPos.x -= playerSpeed * getDeltaTime() / sqrt(2);
    }
    else if (sfKeyboard_isKeyPressed(KEY_DOWN) && sfKeyboard_isKeyPressed(KEY_LEFT)) {
        playerPos.y += playerSpeed * getDeltaTime() / sqrt(2);
        playerPos.x -= playerSpeed * getDeltaTime() / sqrt(2);
    }
    else if (sfKeyboard_isKeyPressed(KEY_DOWN) && sfKeyboard_isKeyPressed(KEY_RIGHT)) {
        playerPos.y += playerSpeed * getDeltaTime() / sqrt(2);
        playerPos.x += playerSpeed * getDeltaTime() / sqrt(2);
    }
    else if (sfKeyboard_isKeyPressed(KEY_UP) && sfKeyboard_isKeyPressed(KEY_RIGHT)) {
        playerPos.y -= playerSpeed * getDeltaTime() / sqrt(2);
        playerPos.x += playerSpeed * getDeltaTime() / sqrt(2);
    }

    // Orthonormal movement
    else if (sfKeyboard_isKeyPressed(KEY_UP)) playerPos.y -= playerSpeed * getDeltaTime();
    else if (sfKeyboard_isKeyPressed(KEY_DOWN)) playerPos.y += playerSpeed * getDeltaTime();
    else if (sfKeyboard_isKeyPressed(KEY_LEFT)) playerPos.x -= playerSpeed * getDeltaTime();
    else if (sfKeyboard_isKeyPressed(KEY_RIGHT)) playerPos.x += playerSpeed * getDeltaTime();
    else return;

    sfSprite_setPosition(player, playerPos);
}

int updateInventory()
{
    if (sfKeyboard_isKeyPressed(sfKeyI)) { inventory[0] = 1; } 
    if (sfKeyboard_isKeyPressed(sfKeyO)) { inventory[1] = 1; } 
    if (sfKeyboard_isKeyPressed(sfKeyP)) { inventory[2] = 1; } 
    if (sfKeyboard_isKeyPressed(sfKeyM)) { inventory[3] = 1; } 

    printf("inventory : %d %d %d %d\n", inventory[0], inventory[1], inventory[2], inventory[3]);

    if (inventory[0] == 1 && inventory[1] == 1 && inventory[2] == 1 && inventory[3] == 1) {
        printf("WIN !\n");
        return 1;
    }
    else return 0;
}

void displayPlayer(sfRenderWindow* _window) {
	if (player != NULL) {
		sfRenderWindow_drawRectangleShape(_window, player, NULL);
        sfSprite_setPosition(player, playerPos); 
	}
}


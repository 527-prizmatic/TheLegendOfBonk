
#include "player.h"
#include "SFML/Graphics.h"

sfRectangleShape* player;
sfVector2f playerPos = { 20.0f, 20.0f };;
float playerSpeed = 0.10f;

sfVector2f vector2f(float _x, float _y)
{
	return (sfVector2f) { _x, _y };
}

void initPlayer()
{

player = sfRectangleShape_create();  
sfRectangleShape_setSize(player, (sfVector2f){50, 60});  
sfRectangleShape_setFillColor(player, sfWhite);	  
sfSprite_setPosition(player, playerPos); 
}

void updatePlayer()
{
    if (sfKeyboard_isKeyPressed(sfKeyZ))
    {
        printf("Z pressed\n");
        playerPos.y -= playerSpeed * getDeltaTime();
        sfSprite_setPosition(player, playerPos);
    }
    if (sfKeyboard_isKeyPressed(sfKeyS))
    {
        playerPos.y += playerSpeed * getDeltaTime();
        sfSprite_setPosition(player, playerPos);
    }

    if (sfKeyboard_isKeyPressed(sfKeyQ))
    {
        playerPos.x -= playerSpeed * getDeltaTime();
        sfSprite_setPosition(player, playerPos);
    }

    if (sfKeyboard_isKeyPressed(sfKeyD))
    {
        playerPos.x += playerSpeed * getDeltaTime();
        sfSprite_setPosition(player, playerPos);
    }
}

void displayPlayer(sfRenderWindow* _window)
{
	if (player != NULL)
	{
		sfRenderWindow_drawRectangleShape(_window, player, NULL);
        sfSprite_setPosition(player, playerPos); 
	}
}


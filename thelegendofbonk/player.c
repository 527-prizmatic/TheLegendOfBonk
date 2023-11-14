
#include "player.h"
#include "SFML/Graphics.h"

sfRectangleShape* player;
sfVector2f playerPos; 

sfVector2f vector2f(float _x, float _y)
{
	return (sfVector2f) { _x, _y };
}

void initPlayer()
{
player = sfRectangleShape_create();  
sfRectangleShape_setSize(player, (sfVector2f){50, 60});  
sfRectangleShape_setFillColor(player, sfWhite);	  
playerPos = vector2f(50.0f, 50.0f);
sfRectangleShape_setPosition(player, playerPos); 

}

void uptdatePlayer()
{
  if (sfKeyboard_isKeyPressed(sfKeyZ))
	playerPos.y -= 5;

  if (sfKeyboard_isKeyPressed(sfKeyS))
    playerPos.y += 5;
	
  if (sfKeyboard_isKeyPressed(sfKeyQ))
	playerPos.x -= 5;

  if (sfKeyboard_isKeyPressed(sfKeyD))
	playerPos.x += 5;

}

void displayPlayer(sfRenderWindow* _window)
{
  sfRenderWindow_drawRectangleShape(_window, player, NULL);  
}


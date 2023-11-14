
#include "player.h"
#include "SFML/Graphics.h"

sfRectangleShape* player;

void initPlayer()
{
player = sfRectangleShape_create();  
sfRectangleShape_setSize(player, (sfVector2f){50, 60});  
sfRectangleShape_setFillColor(player, sfWhite);	  
sfRectangleShape_setPosition(player, (sfVector2f){100, 100}); 
sfRectangleShape_setOrigin(player, (sfVector2f){25, 25}); 
}

void displayPlayer(sfRenderWindow* _window)
{
  sfRenderWindow_drawRectangleShape(_window, player, NULL);  
}


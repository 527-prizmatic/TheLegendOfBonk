#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <math.h>
#include "tools.h"
#include "dialogBox.h"

void main() 
{
	sfVector2f textPos = { 140.0f , 15.0f };
	sfFont* font = initFont();
	sfText* txt = initText();
	sfVector2f dialogBoxSize = { 300.0f , 50.0f };
	sfVector2f dialogBoxPos = { 100.0f , 10.0f };
	sfRectangleShape* dialogBox = initRectangle();
	// INIT
	sfVideoMode mode = { 800, 600, 32 };
	sfRenderWindow* window;
	window = sfRenderWindow_create(mode, "Fenetre", sfDefaultStyle, NULL);
	sfEvent event;

	initDialogBox(txt, font, textPos, dialogBox, dialogBoxPos, dialogBoxSize);

	while (sfRenderWindow_isOpen(window))
	{
		// Gestion des evenements
		while (sfRenderWindow_pollEvent(window, &event))
		{
			if (event.type == sfEvtClosed)
			{
				sfRenderWindow_close(window);
			}
		}
		// Update
		
		// Display 
		sfRenderWindow_clear(window, sfCyan);
		displayDialogBox(window, txt, dialogBox);
		sfRenderWindow_display(window);
	}
}
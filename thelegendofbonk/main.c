#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <math.h>
#include "tools.h"
#include "dialogBox.h"

void main() 
{	
	// Declaration variable
	char str[] = "Lukas\nTymrakiewicz";

	// INIT
	// Variable DIALOG BOX
	sfFont* font = initFont();
	sfText* sfTxt = initText();
	sfRectangleShape* dialogBox = initRectangle();

	// Variable FENETRE
	sfVideoMode mode = { 800, 600, 32 };
	sfRenderWindow* window;
	window = sfRenderWindow_create(mode, "Fenetre", sfDefaultStyle, NULL);
	sfEvent event;

	// Init dialogBox
	initDialogBox(sfTxt, font, dialogBox);
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

		// UPDATE
		updateDialogBox(str, sizeof(str), sfTxt, dialogBox);

		// DISPLAY
		sfRenderWindow_clear(window, sfCyan);
		displayDialogBox(window, sfTxt, dialogBox);
		sfRenderWindow_display(window);
	}
}
#include "dialogBox.h"


sfText* initText()
{
	sfText* _txt = sfText_create();
	return _txt;
}

sfFont* initFont()
{
	sfFont* _font = sfFont_createFromFile(TEXTURE_PATH"3Dventure.ttf");
	return _font;
}

sfRectangleShape* initRectangle()
{
	sfRectangleShape* _rec = sfRectangleShape_create();
	return _rec;
}

/*
* FONCTION : initDialogBox
* PARAM : sfText*, sfFont*, sfRectangleShape*
* Initialise la boite de dialogue
*/
void initDialogBox(sfText* _txt, sfFont* _font, sfRectangleShape* _dialogBox)
{
	sfVector2f dialogBoxPos = { 100.0f , 10.0f };
	// OFFSET Y 10.0f, OFFSET X 5.f
	sfVector2f textPos = { 110.0f , 15.0f };

	sfText_setFont(_txt, _font);
	sfText_setCharacterSize(_txt, 30);
	sfText_setFillColor(_txt, sfBlack);
	sfText_setPosition(_txt, textPos);

	sfRectangleShape_setPosition(_dialogBox, dialogBoxPos);
	sfRectangleShape_setFillColor(_dialogBox, sfWhite);
	sfRectangleShape_setOutlineColor(_dialogBox, sfBlack);
	sfRectangleShape_setOutlineThickness(_dialogBox, 2);
}

/*
* FONCTION : updateDialogBox
* PARAM : char*, int, sfText*, sfRectangleShape*
* Calcul la taille max de la boite de dialogue par rapport au texte
*/
void updateDialogBox(char* _str,int _sizeStr, sfText* _txt, sfRectangleShape* _dialogBox)
{
	sfVector2f newSize = DEFAULT_DIALOG_SIZE;
	int size_x_dialog = 0;
	int max_size_x_dialog = 0;
	
	// Changer texte
	for (int i = 0; i < _sizeStr; i++)
	{
		size_x_dialog++;
		// Si saut de ligne
		if (_str[i] == 10)
		{
			// Calcul de la taille en y de la boite de dialogue
			newSize.y += 30;
			size_x_dialog = 0;
		}

		// Si nouvelle taille max
		if (max_size_x_dialog < size_x_dialog)
		{
			max_size_x_dialog = size_x_dialog;
		}
	}
	// Calcul de la taille en x de la boite de dialogue
	newSize.x = 19 * max_size_x_dialog;

	// Change le texte
	sfText_setString(_txt, _str);

	// Adapter taille dialogBox 
	sfRectangleShape_setSize(_dialogBox, newSize);
}

/*
* FONCTION : displayDialogBox
* PARAM : sfRenderWindow*, sfText*, sfRectangleShape*
* Draw la boite de dialogue
*/
void displayDialogBox(sfRenderWindow* _window, sfText* _txt, sfRectangleShape* _dialogBox)
{
	// Display
	sfRenderWindow_drawRectangleShape(_window, _dialogBox, sfFalse);
	sfRenderWindow_drawText(_window, _txt, sfFalse);
}

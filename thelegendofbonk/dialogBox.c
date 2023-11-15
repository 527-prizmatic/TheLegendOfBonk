#include "dialogBox.h"


sfText* initText()
{
	sfText* _txt = sfText_create();
	return _txt;
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
void initDialogBox(sfText* _txt, sfRectangleShape* _dialogBox)
{
	sfVector2f dialogBoxPos = { 100.0f , 10.0f };
	// OFFSET Y 10.0f, OFFSET X 5.f
	sfVector2f textPos = { 110.0f , 15.0f };
	sfFont* _font = sfFont_createFromFile(TEXTURE_PATH"3Dventure.ttf");

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
	int dialogBoxWidth = 0;
	int dialogBoxWidthMax = 0;
	
	// Changer texte
	for (int i = 0; i < _sizeStr; i++)
	{
		dialogBoxWidth++;
		// Si saut de ligne
		if (_str[i] == 10)
		{
			// Calcul de la taille en y de la boite de dialogue
			newSize.y += 30;
			dialogBoxWidth = 0;
		}

		// Si nouvelle taille max
		if (dialogBoxWidthMax < dialogBoxWidth)
		{
			dialogBoxWidthMax = dialogBoxWidth;
		}
	}
	// Calcul de la taille en x de la boite de dialogue
	newSize.x = 19 * (dialogBoxWidthMax + 1);

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

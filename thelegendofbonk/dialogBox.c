#include "dialogBox.h"

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

void updateDialogBox(char* _str, int _sizeStr, sfText* _txt, sfRectangleShape* _dialogBox, sfVector2f _pos)
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
	newSize.x = 19.0f * (dialogBoxWidthMax + 1.0f);

	// Change le texte
	sfText_setString(_txt, _str);

	// Adapter taille dialogBox 
	sfRectangleShape_setSize(_dialogBox, newSize);
	sfRectangleShape_setPosition(_dialogBox, _pos);
	sfText_setPosition(_txt, (sfVector2f){ _pos.x + 10, _pos.y });
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

sfBool isClicked(sfRenderWindow* _w, sfRectangleShape* _dialogBox) {
	sfFloatRect hitbox = sfRectangleShape_getGlobalBounds(_dialogBox);
	sfVector2i mousePos = sfMouse_getPositionRenderWindow(_w);
	if (mousePos.x > hitbox.left && mousePos.x < hitbox.left + hitbox.width && mousePos.y > hitbox.top && mousePos.y < hitbox.top + hitbox.height) return sfTrue;
	else return sfFalse;
}
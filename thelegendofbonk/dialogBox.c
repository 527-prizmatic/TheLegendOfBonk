#include "dialogBox.h"

/*
* FONCTION : initDialogBox
* PARAM : sfText*, sfFont*, sfRectangleShape*
* Initialise la boite de dialogue
*/
void initDialogBox(sfText* _txt, sfFont* _font, int _police, sfRectangleShape* _dialogBox)
{
	sfText_setFont(_txt, _font);
	sfText_setCharacterSize(_txt, _police);
	sfText_setFillColor(_txt, sfBlack);

	sfRectangleShape_setFillColor(_dialogBox, sfWhite);
	sfRectangleShape_setOutlineColor(_dialogBox, sfBlack);
	sfRectangleShape_setOutlineThickness(_dialogBox, 2);
}

void updateDialogBox(char* _str, int _sizeStr, sfText* _txt, sfRectangleShape* _dialogBox, sfVector2f _pos, sfVector2f _size)
{
	sfVector2f newSize = _size;
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
	if (strcmp(_str, "CRAFT !") == 0)
	{
		newSize.x = 12.0f * (float)dialogBoxWidthMax;
	}
	else
	{
		newSize.x = 19.0f * (dialogBoxWidthMax + 1.0f);
	}

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
void displayDialogBox(sfRenderWindow* _window, sfText* _txt, sfRectangleShape* _dialogBox, sfBool _static)
{
	// Display
	if(_static == sfTrue) sfRenderWindow_setView(_window, sfRenderWindow_getDefaultView(_window));
	sfRenderWindow_drawRectangleShape(_window, _dialogBox, sfFalse);
	sfRenderWindow_drawText(_window, _txt, sfFalse);
}

sfBool isClicked(sfRenderWindow* _w, sfRectangleShape* _dialogBox) {
	sfFloatRect hitbox = sfRectangleShape_getGlobalBounds(_dialogBox);  
	sfVector2i mousePos = sfMouse_getPositionRenderWindow(_w); 
	if (mousePos.x > hitbox.left && mousePos.x < hitbox.left + hitbox.width && mousePos.y > hitbox.top && mousePos.y < hitbox.top + hitbox.height) return sfTrue;
	else return sfFalse;
}
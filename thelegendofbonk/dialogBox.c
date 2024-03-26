#include "dialogBox.h"

sfRectangleShape* initDialogBox(sfText* _txt, sfFont* _font, int _police) {
	sfRectangleShape* dialogBox = sfRectangleShape_create();

	sfText_setFont(_txt, _font);
	sfText_setCharacterSize(_txt, _police);
	sfText_setFillColor(_txt, sfBlack);

	sfRectangleShape_setFillColor(dialogBox, sfWhite);
	sfRectangleShape_setOutlineColor(dialogBox, sfBlack);
	sfRectangleShape_setOutlineThickness(dialogBox, 2);

	return dialogBox;
}

void updateDialogBox(char* _str, int _sizeStr, sfText* _txt, sfRectangleShape* _dialogBox, sfVector2f _pos, sfVector2f _size, char _flagStretch) {
	sfVector2f newSize = _size;
	int dialogBoxWidth = 0;
	int dialogBoxWidthMax = 0;
	
	// Changer texte
	for (int i = 0; i < _sizeStr; i++) {
		dialogBoxWidth++;
		// Si saut de ligne
		if (_str[i] == 10) {
			// Calcul de la taille en y de la boite de dialogue
			if (_flagStretch) newSize.y += 30;
			dialogBoxWidth = 0;
		}

		// Si nouvelle taille max
		if (dialogBoxWidthMax < dialogBoxWidth) dialogBoxWidthMax = dialogBoxWidth;
	}
	// Calcul de la taille en x de la boite de dialogue
	if (strcmp(_str, "CRAFT !") == 0) newSize.x = 12.0f * (float)dialogBoxWidthMax;
	if (_flagStretch) newSize.x = 19.0f * (dialogBoxWidthMax + 1.0f);
		
	// Change le texte
	sfText_setString(_txt, _str);

	// Adapter taille dialogBox 
	sfRectangleShape_setSize(_dialogBox, newSize);
	sfRectangleShape_setPosition(_dialogBox, _pos);
	sfText_setPosition(_txt, (sfVector2f){ _pos.x + 10, _pos.y });
}

void displayDialogBox(sfRenderWindow* _w, sfText* _txt, sfRectangleShape* _dialogBox, sfBool _fixed) {
	// Display
	if(_fixed == sfTrue) sfRenderWindow_setView(_w, sfRenderWindow_getDefaultView(_w));
	sfRenderWindow_drawRectangleShape(_w, _dialogBox, sfFalse);
	sfRenderWindow_drawText(_w, _txt, sfFalse);
}

sfBool isClicked(sfRenderWindow* _w, sfSprite* _button) {
	sfFloatRect hitbox = sfSprite_getGlobalBounds(_button);
	sfVector2i mousePos = sfMouse_getPositionRenderWindow(_w); 
	if (testLClick(_w) && sfFloatRect_contains(&hitbox, (float) mousePos.x, (float) mousePos.y)) return sfTrue;
	else return sfFalse;
}
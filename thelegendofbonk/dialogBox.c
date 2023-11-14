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

void initDialogBox(sfText* txt, sfFont* font, sfVector2f textPos, sfRectangleShape* dialogBox, sfVector2f dialogBoxPos, sfVector2f dialogBoxSize)
{
	sfText_setFont(txt, font);
	sfText_setString(txt, "Hello CSFML !");
	sfText_setCharacterSize(txt, 30);
	sfText_setFillColor(txt, sfBlack);
	sfText_setPosition(txt, textPos);

	sfRectangleShape_setSize(dialogBox, dialogBoxSize);
	sfRectangleShape_setPosition(dialogBox, dialogBoxPos);
	sfRectangleShape_setFillColor(dialogBox, sfWhite);
	sfRectangleShape_setOutlineColor(dialogBox, sfBlack);
	sfRectangleShape_setOutlineThickness(dialogBox, 2);
}

void updateDialogBox()
{

}

void displayDialogBox(sfRenderWindow* _window, sfText* txt, sfRectangleShape* dialogBox)
{
	// Display
	sfRenderWindow_drawRectangleShape(_window, dialogBox, sfFalse);
	sfRenderWindow_drawText(_window, txt, sfFalse);
}

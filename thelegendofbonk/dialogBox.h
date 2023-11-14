#pragma once
#include "tools.h"

// GESTION DIALOGBOX
sfText* initText();
sfFont* initFont();
sfRectangleShape* initRectangle();
void initDialogBox(sfText* txt, sfFont* font, sfVector2f textPos, sfRectangleShape* dialogBox, sfVector2f dialogBoxPos, sfVector2f dialogBoxSize);
void updateDialogBox();
void displayDialogBox(sfRenderWindow* _window, sfText* txt, sfRectangleShape* dialogBox);
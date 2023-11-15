#pragma once
#include "tools.h"
#define DEFAULT_DIALOG_SIZE (sfVector2f){ 0.0f , 50.0f }

// GESTION DIALOGBOX
// Prototype fonction
sfText* initText();
sfFont* initFont();
sfRectangleShape* initRectangle();
void initDialogBox(sfText* txt, sfFont* font, sfRectangleShape* dialogBox);
void updateDialogBox(char* _str, int _sizeStr, sfText* _txt, sfRectangleShape* _dialogBox);
void displayDialogBox(sfRenderWindow* _window, sfText* txt, sfRectangleShape* dialogBox);
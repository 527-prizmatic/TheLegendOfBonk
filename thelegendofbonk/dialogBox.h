#pragma once
#include "tools.h"
#define DEFAULT_DIALOG_SIZE (sfVector2f){ 0.0f , 50.0f }

/* Dialog box initialization function.
*  \param txt - A text object
*  \param font - A font object
*  \param dialogBox - A display area object */
void initDialogBox(sfText* _txt, sfFont* _font, int _police, sfRectangleShape* _dialogBox);
void updateDialogBox(char* _str, int _sizeStr, sfText* _txt, sfRectangleShape* _dialogBox, sfVector2f _pos, sfVector2f _size);
void displayDialogBox(sfRenderWindow* _window, sfText* _txt, sfRectangleShape* _dialogBox, sfBool _static);
sfBool isClicked(sfRenderWindow* _w, sfSprite* _button);
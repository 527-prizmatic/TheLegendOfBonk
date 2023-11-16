#pragma once
#include "tools.h"
#define DEFAULT_DIALOG_SIZE (sfVector2f){ 0.0f , 50.0f }

/* Initializes the dialog box's text object. */
sfText* initText();

/* Initializes the dialog box's font object. */
sfFont* initFont();

/* Initializes the dialog box's display area. */
sfRectangleShape* initRectangle();

/* Dialog box initialization function.
*  \param txt - A text object
*  \param font - A font object
*  \param dialogBox - A display area object */
void initDialogBox(sfText* txt, sfFont* font, sfRectangleShape* dialogBox);

void updateDialogBox(char* _str, int _sizeStr, sfText* _txt, sfRectangleShape* _dialogBox, sfVector2f _pos);
void displayDialogBox(sfRenderWindow* _window, sfText* txt, sfRectangleShape* dialogBox);

sfBool isClicked(sfRenderWindow* _w, sfRectangleShape* _dialogBox);
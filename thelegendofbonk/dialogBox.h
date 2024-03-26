#pragma once
#include "tools.h"
#define DEFAULT_DIALOG_SIZE (sfVector2f){ 0.0f , 50.0f }

/// Dialog box initialization function.
/// \param _txt - A text object
/// \param _font - A font object
/// \param _dialogBox - A display area object */
sfRectangleShape* initDialogBox(sfText* _txt, sfFont* _font, int _police);

void updateDialogBox(char* _str, int _sizeStr, sfText* _txt, sfRectangleShape* _dialogBox, sfVector2f _pos, sfVector2f _size, char _flagStretch);

/// Displays the given dialog box.
/// \param _w - Render window object
/// \param _txt - A text object to be displayed in the dialog box
/// \param _dialogBox - A dialog box object to be displayed
/// \param _fixed - Whether the dialog box is part of the HUD or should move around with the map */
void displayDialogBox(sfRenderWindow* _w, sfText* _txt, sfRectangleShape* _dialogBox, sfBool _fixed);

/// Checks if the given button is being clicked, i.e. if the mouse's left button is pressed while the cursor is on top of the button.
sfBool isClicked(sfRenderWindow* _w, sfSprite* _button);
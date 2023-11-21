#pragma once
#include "tools.h"
#include "map.h"

/* Allows the user to move the editor's view around the map.
*  \param _w - Render window object
*  \param _v - View object */
void updateEditorView(sfRenderWindow* _w, sfView* _v);

/* Allows the user to change tiles by clicking on them.
*  The function reads the position of the mouse, maps it to coordinates on the tile maps, then changes the given tile to the given ID.
*  \param _w - Render window object to calculate clicked position
*  \param _v - View object to calculate clicked position
*  \param _map - The level's terrain map
*  \param _prop - The level's prop map
*  \param _id - The tile ID to change the clicked tile to
*/
void changeTile(sfRenderWindow* _w, sfView* _v, char _map[H_MAP_T][W_MAP_T], char _prop[H_MAP_T][W_MAP_T], char _id);


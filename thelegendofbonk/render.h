#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <math.h>

#include "SFML/Graphics.h"
#include "map.h"

/* Initializes the rendering engine by creating windows, texture sheets and the like.
*  \return A pointed to a newly created sfRenderWindow */
sfRenderWindow* initRender();

/* Initializes the rendering viewport.
*  \return A pointed to a newly created sfView */
sfView* initView();

/* Updates the given viewport's location to keep it centered on the player character as much as possible.
*  \param _w - A render window
*  \param _ma - A viewport
*  \param _window - The player character's position */
void updateView(sfRenderWindow* _w, sfView* _v, sfVector2f _pos);

/* Renders the map.
*  \param _map - An initialized tilemap to be displayed
*  \param _window - The window to display the map on */
void renderMap(char _map[H_MAP_T][W_MAP_T], sfRenderWindow* _w);
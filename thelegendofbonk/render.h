#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <math.h>

#include "SFML/Graphics.h"
#include "map.h"

/* Initializes the rendering engine by creating windows, views, texture sheets and the like.
*  \return A pointed to a newly created sfRenderWindow */
sfRenderWindow* initRender();
void initView(sfRenderWindow* _w);

void updateView(sfRenderWindow* _w, sfVector2f _pos);

/* Displays the map.
*  \param _map[][] - An initialized tilemap to be displayed
*  \param _window - The window to display the map on */
void renderMap(char _map[H_MAP_T][W_MAP_T], sfRenderWindow* _w);
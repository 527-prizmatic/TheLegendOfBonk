#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define H_MAP_T 40 // Map height in tiles
#define W_MAP_T 80 // Map width in tiles

/* Initializes the tilemap passed in argument and fills it with zeros.
*  \param _map[][] - A non-initialized tilemap */
void initMapNull(char _map[H_MAP_T][W_MAP_T]);

/* Initializes the tilemap passed in argument and fills it with random digits.
*  \param _map[][] - A non-initialized tilemap */
void initMapRandom(char _map[H_MAP_T][W_MAP_T]);
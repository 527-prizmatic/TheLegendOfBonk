#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define H_MAP_T 60 // Map height in tiles
#define W_MAP_T 80 // Map width in tiles
#define TILE_PX 64 // Tile size in pixels
#define SCALE 4.f / 3.f // Tile texture scale
#define H_MAP_PX H_MAP_T * TILE_PX // Map height in pixels
#define W_MAP_PX W_MAP_T * TILE_PX // Map height in pixels

/* Initializes the tilemap passed in argument and fills it with zeros.
*  \param _map[][] - A non-initialized tilemap */
void initMapNull(char _map[H_MAP_T][W_MAP_T]);

/* Initializes the tilemap passed in argument and fills it with random digits.
*  \param _map[][] - A non-initialized tilemap */
void initMapRandom(char _map[H_MAP_T][W_MAP_T]);
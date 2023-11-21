#pragma once
#include "SFML/Graphics.h"

/* Returns mapping coordinates for various tile textures based on numerical IDs.
*  \param _id - Tile texture ID */
sfIntRect textureFromId(int _id);

/* Checks whether the given tile ID corresponds to solid terrain. */
sfBool isSolidBlock(char _id);

/* Checks whether the given tile ID corresponds to a water tile. */
sfBool isWater(char _id);
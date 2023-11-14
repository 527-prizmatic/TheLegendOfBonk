#pragma once
#include "SFML/Graphics.h"

/* Returns mapping coordinates for various tile textures based on numerical IDs.
*  \param _id - Tile texture ID */
sfIntRect textureFromId(int _id);
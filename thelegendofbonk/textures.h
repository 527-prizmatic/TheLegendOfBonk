#pragma once
#include "SFML/Graphics.h"

const sfIntRect p_chest;
const sfIntRect p_chest_2;
const sfIntRect p_chest_3;
const sfIntRect p_chest_4;
const sfIntRect p_chest_5;
const sfIntRect p_chest_6;
const sfIntRect p_chest_7;
const sfIntRect p_chest_8;

const sfIntRect* arr_chest[8];

/// Returns mapping coordinates for various tile textures based on numerical IDs.
/// \param _id - Tile texture ID
sfIntRect textureFromId(int _id);

/// Checks whether the given tile ID corresponds to solid terrain.
sfBool isSolidBlock(char _id);

/// Checks whether the given tile ID corresponds to a water tile.
sfBool isWater(char _id);

/// Checks whether the given tile ID should render in the foreground.
sfBool isForeground(char _id);


/* == TEXTURE SWAPPERS == */

/// Swaps textures for lamp posts based on the ID passed as argument.
/// Would definitely be far more practical with classes, but we can't have everything.
void selectTexture_lampPost(char _mode);
#include "textures.h"

const sfIntRect t_none = { 0, 0, 0, 0 };

const sfIntRect t_green = { 0, 0, 32, 32 };
const sfIntRect t_blue = { 0, 32, 32, 32 };
const sfIntRect t_yellow = { 0, 64, 32, 32 };
const sfIntRect t_gray = { 0, 96, 32, 32 };

sfIntRect textureFromId(int _id) {
	switch (_id) {
	case 0: return t_green;
	case 1: return t_blue;
	case 2: return t_yellow;
	case 3: return t_gray;
	default: return t_none;
	}
}
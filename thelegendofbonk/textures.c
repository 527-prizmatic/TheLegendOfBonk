#include "textures.h"

#define TS 48

const sfIntRect t_none = { 0, 0, 0, 0 };

const sfIntRect t_grass			= { TS * 1, TS * 4, 48, 48 };
const sfIntRect t_water			= { TS * 5, TS * 8, 48, 48 };
const sfIntRect t_sand			= { TS * 1, TS * 13, 48, 48 };
const sfIntRect t_rock			= { TS * 6, TS * 4, 48, 48 };
const sfIntRect t_a				= { TS * 5, TS * 7, 48, 48 };

sfIntRect textureFromId(int _id) {
	switch (_id) {
	case 0: return t_grass;
	case 1: return t_water;
	case 2: return t_sand;
	case 3: return t_rock;
	case 4: return t_a;
	default: return t_none;
	}
}
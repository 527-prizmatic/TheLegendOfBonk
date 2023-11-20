#include "textures.h"

#define TS 48

const sfIntRect t_none = { 0, 0, 0, 0 };


const sfIntRect t_path_tl			= { TS * 0, TS * 12, 48, 48 };
const sfIntRect t_path_t			= { TS * 1, TS * 12, 48, 48 };
const sfIntRect t_path_tr			= { TS * 2, TS * 12, 48, 48 };
const sfIntRect t_path_l			= { TS * 0, TS * 13, 48, 48 };
const sfIntRect t_path				= { TS * 1, TS * 13, 48, 48 };
const sfIntRect t_path_r			= { TS * 2, TS * 13, 48, 48 };
const sfIntRect t_path_bl			= { TS * 0, TS * 14, 48, 48 };
const sfIntRect t_path_b			= { TS * 1, TS * 14, 48, 48 };
const sfIntRect t_path_br			= { TS * 2, TS * 14, 48, 48 };

const sfIntRect t_path_corner_tl	= { TS * 0, TS * 10, 48, 48 };
const sfIntRect t_path_corner_tr	= { TS * 1, TS * 10, 48, 48 };
const sfIntRect t_path_corner_bl	= { TS * 0, TS * 11, 48, 48 };
const sfIntRect t_path_corner_br	= { TS * 1, TS * 11, 48, 48 };

const sfIntRect t_grass				= { TS * 1, TS * 4, 48, 48 };

const sfIntRect t_cobble_tl			= { TS * 3, TS * 12, 48, 48 };
const sfIntRect t_cobble_t			= { TS * 4, TS * 12, 48, 48 };
const sfIntRect t_cobble_tr			= { TS * 5, TS * 12, 48, 48 };
const sfIntRect t_cobble_l			= { TS * 3, TS * 13, 48, 48 };
const sfIntRect t_cobble			= { TS * 4, TS * 13, 48, 48 };
const sfIntRect t_cobble_r			= { TS * 5, TS * 13, 48, 48 };
const sfIntRect t_cobble_bl			= { TS * 3, TS * 14, 48, 48 };
const sfIntRect t_cobble_b			= { TS * 4, TS * 14, 48, 48 };
const sfIntRect t_cobble_br			= { TS * 5, TS * 14, 48, 48 };

const sfIntRect t_cobble_corner_tl	= { TS * 3, TS * 10, 48, 48 };
const sfIntRect t_cobble_corner_tr	= { TS * 4, TS * 10, 48, 48 };
const sfIntRect t_cobble_corner_bl	= { TS * 3, TS * 11, 48, 48 };
const sfIntRect t_cobble_corner_br	= { TS * 4, TS * 11, 48, 48 };

sfIntRect textureFromId(int _id) {
	switch (_id) {
	case 0: return t_none;
	case 1: return t_path_tl;
	case 2: return t_path_t;
	case 3: return t_path_tr;
	case 4: return t_path_l;
	case 5: return t_path;
	case 6: return t_path_r;
	case 7: return t_path_bl;
	case 8: return t_path_b;
	case 9: return t_path_br;
	case 10: return t_path_corner_tl;
	case 11: return t_path_corner_tr;
	case 12: return t_path_corner_bl;
	case 13: return t_path_corner_br;

	case 14: return t_grass;

	case 15: return t_cobble_tl;
	case 16: return t_cobble_t;
	case 17: return t_cobble_tr;
	case 18: return t_cobble_l;
	case 19: return t_cobble;
	case 20: return t_cobble_r;
	case 21: return t_cobble_bl;
	case 22: return t_cobble_b;
	case 23: return t_cobble_br;
	case 24: return t_cobble_corner_tl;
	case 25: return t_cobble_corner_tr;
	case 26: return t_cobble_corner_bl;
	case 27: return t_cobble_corner_br;

	default: return t_none;
	}
}
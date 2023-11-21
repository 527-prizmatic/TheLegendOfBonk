#include "textures.h"

#define TS 48

const sfIntRect t_none				= { 0, 0, 0, 0 };
const sfIntRect p_none				= { 0, 0, 0, 0 };

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

const sfIntRect t_stairs	= { TS * 4, TS * 5, 48, 48 };


const sfIntRect p_ledge_tl			= { TS * 0, TS * 3, 48, 48 };
const sfIntRect p_ledge_t			= { TS * 1, TS * 3, 48, 48 };
const sfIntRect p_ledge_tr			= { TS * 2, TS * 3, 48, 48 };
const sfIntRect p_ledge_l			= { TS * 0, TS * 4, 48, 48 };
const sfIntRect p_ledge_r			= { TS * 2, TS * 4, 48, 48 };
const sfIntRect p_ledge_bl			= { TS * 0, TS * 5, 48, 48 };
const sfIntRect p_ledge_b			= { TS * 1, TS * 5, 48, 48 };
const sfIntRect p_ledge_br			= { TS * 2, TS * 5, 48, 48 };

const sfIntRect p_ledge_corner_tl	= { TS * 3, TS * 3, 48, 48 };
const sfIntRect p_ledge_corner_tr	= { TS * 4, TS * 3, 48, 48 };
const sfIntRect p_ledge_corner_bl	= { TS * 3, TS * 4, 48, 48 };
const sfIntRect p_ledge_corner_br	= { TS * 4, TS * 4, 48, 48 };

const sfIntRect p_flower_w			= { TS * 5, TS * 3, 48, 48 };
const sfIntRect p_flower_r			= { TS * 6, TS * 3, 48, 48 };
const sfIntRect p_rock_s			= { TS * 5, TS * 4, 48, 48 };
const sfIntRect p_rock_m			= { TS * 6, TS * 4, 48, 48 };

const sfIntRect p_lamppost_top		= { TS * 7, TS * 3, 48, 48 };
const sfIntRect p_lamppost_bottom	= { TS * 7, TS * 4, 48, 48 };

const sfIntRect p_fence_l			= { TS * 5, TS * 5, 48, 48 };
const sfIntRect p_fence_h			= { TS * 6, TS * 5, 48, 48 };
const sfIntRect p_fence_r			= { TS * 7, TS * 5, 48, 48 };
const sfIntRect p_fence_t			= { TS * 7, TS * 6, 48, 48 };
const sfIntRect p_fence_v			= { TS * 7, TS * 7, 48, 48 };
const sfIntRect p_fence_b			= { TS * 7, TS * 8, 48, 48 };
const sfIntRect p_fence_post		= { TS * 6, TS * 6, 48, 48 };

const sfIntRect p_sign				= { TS * 6, TS * 7, 48, 48 };

const sfIntRect p_chest             = { TS * 5, TS * 7, 48, 48 };

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

	case 28: return t_stairs;

	case 64: return p_none;

	case 65: return p_ledge_tl;
	case 66: return p_ledge_t;
	case 67: return p_ledge_tr;
	case 68: return p_ledge_l;
	case 69: return p_ledge_r;
	case 70: return p_ledge_bl;
	case 71: return p_ledge_b;
	case 72: return p_ledge_br;

	case 73: return p_ledge_corner_tl;
	case 74: return p_ledge_corner_tr;
	case 75: return p_ledge_corner_bl;
	case 76: return p_ledge_corner_br;

	case 77: return p_flower_w;
	case 78: return p_flower_r;
	case 79: return p_rock_s;
	case 80: return p_rock_m;

	case 81: return p_lamppost_top;
	case 82: return p_lamppost_bottom;

	case 83: return p_fence_l;
	case 84: return p_fence_h;
	case 85: return p_fence_r;
	case 86: return p_fence_t;
	case 87: return p_fence_v;
	case 88: return p_fence_b;
	case 89: return p_fence_post;

	case 90: return p_sign;
	case 91: return p_chest;

	default: return t_none;
	}
}


sfBool isSolidBlock(char _id) {
	if (_id >= 65 && _id <= 76) return sfTrue;
	if (_id >= 83 && _id <= 89) return sfTrue;
	switch (_id) {
		case 79: return sfTrue;
		case 80: return sfTrue;
		case 82: return sfTrue;
		case 90: return sfTrue;
		case 91: return sfTrue;
		default: return sfFalse;
	}
}

sfBool isWater(char _id) {
	switch (_id) {
		// case 1: return sfTrue;
	default: return sfFalse;
	}
}
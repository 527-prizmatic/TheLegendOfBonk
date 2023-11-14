#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <math.h>

#include "SFML/Graphics.h"
#include "map.h"


sfRenderWindow* render_init();

void render_map(char _map[H_MAP_T][W_MAP_T]);
#pragma once
#include "tools.h"
#include "map.h"

void updateEditorView(sfRenderWindow* _w, sfView* _v);

void changeTile(sfRenderWindow* _w, sfView* _v, char _map[H_MAP_T][W_MAP_T], char _id);


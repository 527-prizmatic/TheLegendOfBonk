#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <math.h>

#include "SFML/Graphics.h"
#include "map.h"

sfTexture* tilesheet;
sfSprite* tile;

/// Initializes the rendering engine by creating windows, texture sheets and the like.
/// \return A pointed to a newly created sfRenderWindow
sfRenderWindow* initRender();

/// Initializes rendering viewports.
/// \return A pointed to a newly created sfView
sfView* initGameView();
sfView* initEditorView();
sfView* initMinimapView();
sfView* initCreditsView();

/// Updates the given viewport's location to keep it centered on the player character as much as possible.
/// \param _w - A render window
/// \param _ma - A viewport
/// \param _window - The player character's position
void updateView(sfRenderWindow* _w, sfView* _v, sfVector2f _pos);

/// Renders the map.
/// \param _map - An initialized tilemap to be displayed
/// \param _window - The window to display the map on
/// \param _pos - Player position
/// \param _fg - Whether the propmap should render the foreground
void renderMap(char _map[H_MAP_T][W_MAP_T], sfRenderWindow* _w, sfVector2f _pos, char _fg, char _minimap);

/// Renders the map editor's tile selection UI.
void renderEditorUI(sfRenderWindow* _w, sfView* _v, int _mode, sfFont* _font);

/// A function including a large set of technical operations to set up and display a minimap on the top-left corner of the screen.
/// NOTE - HIGHLY UNSTABLE, DEVOURS CPU POWER, WE'RE LOOKING INTO THAT ISSUE
void renderMinimap(sfRenderWindow* _w, sfView* _v, char _map[H_MAP_T][W_MAP_T], char _props[H_MAP_T][W_MAP_T]);

/// Displays a small rectangle on the minimap to mark the player'slocation.
void renderPlayerOnMinimap(sfRenderWindow* _w);

/// Displays the credits in the main menu
void renderCredit(sfRenderWindow* _w, sfView* _v, sfFont* _font, char _name[], char _role[], char _posX, char _posY);
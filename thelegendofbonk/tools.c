#include "tools.h"

#pragma warning (disable: 4018)

sfTime sf_time;
sfClock* sf_clock;
sfBool isRunning = sfTrue;

void initTools() {
	sf_clock = sfClock_create();
	srand((unsigned int)time(NULL));
	gameState = MENU;
}

void restartClock() {
	sf_time = sfClock_restart(sf_clock);
}

float getDeltaTime() {
	return sfTime_asSeconds(sf_time);
	
}

sfVector2f vector2f(float _x, float _y) {
	return (sfVector2f) { _x, _y };
}

sfBool isMouseWithinWindow(sfRenderWindow* _w) {
	sfVector2i mouseCursor = sfMouse_getPosition(_w);
	if (mouseCursor.x >= 0 && mouseCursor.x <= sfWindow_getSize(_w).x && mouseCursor.y >= 0 && mouseCursor.y <= sfWindow_getSize(_w).y) return sfTrue;
	else return sfFalse;
}

sfRectangleShape* initRectangle(sfVector2f _pos, sfVector2f _size) {
	sfRectangleShape* rect = sfRectangleShape_create();
	sfRectangleShape_setPosition(rect, _pos);
	sfRectangleShape_setSize(rect, _size);

	return rect;
}

sfSprite* initSprite(char* _texture_path, sfVector2f _scale, sfVector2f _pos) {
	sfSprite* spr = sfSprite_create();
	sfTexture* texture = sfTexture_createFromFile(_texture_path, NULL);
	sfSprite_setTexture(spr, texture, sfFalse);
	sfSprite_setScale(spr, _scale);
	sfSprite_setPosition(spr, _pos);

	return spr;
}

sfText* initText(sfFont* _font, int _size, sfVector2f _pos) {
	sfText* txt = sfText_create();
	sfText_setFont(txt, _font);
	sfText_setCharacterSize(txt, _size);
	sfText_setPosition(txt, _pos);

	return txt;
}

void formatTextOutline(sfText* _txt, sfColor _color) {
	sfText_setOutlineThickness(_txt, 2.0f);
	sfText_setOutlineColor(_txt, _color);
}

sfBool testKeyPress(sfKeyCode _key, sfRenderWindow* _w) {
	if (_w != NULL && !sfRenderWindow_hasFocus(_w)) return sfFalse;
	if (!sfKeyboard_isKeyPressed(_key)) return sfFalse;
	return sfTrue;
}

sfBool testLClick(sfRenderWindow* _w) {
	if (_w != NULL && !sfRenderWindow_hasFocus(_w)) return sfFalse;
	if (!sfMouse_isButtonPressed(sfMouseLeft)) return sfFalse;
	return sfTrue;
}


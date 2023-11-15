#pragma once
#include "SFML/Graphics.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define TEXTURE_PATH "..\\assets\\textures\\"
#define AUDIO_PATH "..\\assets\\audio\\"

// GESTION TIME


/* Initializes misc tools for handling time. */
void initTools();

/* Restarts the game's internal clock, for time-tracking purposes. */
void restartClock();

/* \return Time elapsed since last restartClock() call */
float getDeltaTime();

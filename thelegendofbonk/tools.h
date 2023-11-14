#pragma once
#include "SFML/Graphics.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define TEXTURE_PATH = "..\\assets\textures"
#define AUDIO_PATH = "..\\assets\audio"

// GESTION TIME
void initTools();
void restartClock();
float getDeltaTime();
#include "tools.h"

sfTime sf_time;
sfClock* sf_clock;

void initTools()
{
	sf_clock = sfClock_create();
	srand((unsigned int)time(NULL));
}

void restartClock()
{
	sf_time = sfClock_restart(sf_clock);
}

float getDeltaTime()
{
	return sfTime_asSeconds(sf_time);
}
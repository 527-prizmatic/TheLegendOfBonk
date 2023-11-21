#include "music.h"
#include "SFML/Audio.h"

void changeVolume(sfMusic* _music, char _flag_increase) {
	float vol = sfMusic_getVolume(_music);

	if (_flag_increase == 1) {
		vol += 10.0f;
		if (vol >= 95.0f) vol = 100.0f;
	}
	else {
		vol -= 10.0f;
		if (vol <= 5.0f) vol = 0.0f;
	}

	sfMusic_setVolume(_music, vol);
}

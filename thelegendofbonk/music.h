#pragma once
#include "tools.h"
#include "SFML/Audio.h"

/// Increments or decrements the music's volume by 10%.
/// \param _music - Music object whose volume to be changed
/// \param _flag_increase - Whether to increase (= 1) or decrease (= 0) the volume */
void changeVolume(sfMusic* _music, char _flag_increase);

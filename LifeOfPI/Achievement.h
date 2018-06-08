#pragma once

#include "GameObject.h"
#include "Achievements.h"

class Achievement : public GameObject
{

	bool _unlocked;
	Achievements::eAchievementType _type;
	Achievements *_achievements;

public:

	Achievement(sf::Image &spriteSheet, 
				sf::IntRect firstFrame, 
				Achievements::eAchievementType type,
				Achievements &achievements);

	virtual Achievement& updateState();

};
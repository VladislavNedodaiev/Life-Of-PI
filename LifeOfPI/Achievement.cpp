#include "Achievement.h"

Achievement::Achievement(sf::Image &spriteSheet,
						 sf::IntRect firstFrame,
						 Achievements::eAchievementType type,
						 Achievements &achievements) :
							GameObject(spriteSheet, 2, 0, firstFrame)
{
	_type = type;
	_achievements = &achievements;
	_unlocked = false;

	updateState();
} // constructor

Achievement& Achievement::updateState()
{
	if (_achievements->getAchievementState(_type) != _unlocked)
	{
		_unlocked = !_unlocked;
		_currentAnimation->setFrame(_unlocked);
		_currentAnimation->updateTexture();
	} // if

	return *this;
} // reading and updating the state
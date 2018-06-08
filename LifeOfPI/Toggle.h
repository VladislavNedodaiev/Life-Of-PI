#pragma once

#include "GameObject.h"

class Toggle : public GameObject
{

	Animation *_toggleON;
	Animation *_toggleOFF;

	bool _toggled;

public:

	Toggle(sf::Image &toggle, sf::IntRect firstFrameOFF, sf::IntRect firstFrameON);
	virtual ~Toggle();

	virtual bool pointIsOver(sf::Vector2i &point);
	virtual bool isPressed(sf::Event &event, sf::Vector2i &point);

	virtual Toggle& toggle();

	virtual Toggle& setToggle(bool toggled);
	virtual bool getToggle() const;

};
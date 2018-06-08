#pragma once

#include "GameObject.h"

class Button : public GameObject
{
public:

	Button(sf::Image &spriteSheet, sf::IntRect firstFrame);
	virtual ~Button();

	virtual bool pointIsOver(sf::Vector2i &point);
	virtual bool isPressed(sf::Event &event, sf::Vector2i &point);

};
#pragma once

#include "Lecturer.h"

class Litvinog : public Lecturer
{
public:

	Litvinog(sf::Image &sheet, int sceneLeftX, int sceneRightX);
	virtual ~Litvinog();

	virtual Litvinog& setPosition(const sf::Vector2f &position);
	virtual Litvinog& setPosition(float x, float y);

	virtual Litvinog& move(const sf::Vector2f &offset);
	virtual Litvinog& move(float offsetX, float offsetY);

};

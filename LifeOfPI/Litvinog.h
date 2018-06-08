#pragma once

#include "Lecturer.h"

class Litvinog : public Lecturer
{
public:

	Litvinog(sf::Image &sheet, int sceneLeftX, int sceneRightX, sf::Font *font);
	virtual ~Litvinog();

};

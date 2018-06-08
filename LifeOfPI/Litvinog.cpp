#include "Litvinog.h"

Litvinog::Litvinog(sf::Image &sheet, int sceneLeftX, int sceneRightX, sf::Font *font) :
	Lecturer(sheet, sceneLeftX, sceneRightX, font) 
{
	setPosition(80, 46);
} // constructor

Litvinog::~Litvinog() {} // destructor
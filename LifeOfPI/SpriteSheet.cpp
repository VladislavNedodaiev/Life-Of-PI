#include "SpriteSheet.h"

SpriteSheet::SpriteSheet()
{
	this->_sheet.create(0, 0);
} // constructor #1

SpriteSheet::SpriteSheet(std::string path)
{
	this->load(path);
} // constructor #2

SpriteSheet& SpriteSheet::load(std::string path)
{
	if (!this->_sheet.loadFromFile(path))
		this->_sheet.create(0, 0);

	return *this;
} // loading

sf::Image& SpriteSheet::getSheet()
{
	return this->_sheet;
} // getting sheet
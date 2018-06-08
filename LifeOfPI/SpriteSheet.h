#pragma once

#include <SFML\Graphics.hpp>
#include <string>

class SpriteSheet
{

	sf::Image _sheet;

public:

	SpriteSheet();
	SpriteSheet(std::string path);

	SpriteSheet& load(std::string path);
	sf::Image& getSheet();

};
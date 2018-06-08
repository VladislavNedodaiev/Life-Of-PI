#pragma once

#include "GameObject.h"

class Question : public GameObject
{
protected:

	sf::Text _text;

public:

	Question(sf::Image &sheet,  
			 sf::Font &font, 
			 sf::IntRect firstFrame,
			 unsigned int characterSize,
			 sf::Color textColor);
	virtual ~Question();

	virtual Question& setPosition(const sf::Vector2f &position);
	virtual Question& setPosition(float x, float y);

	virtual Question& move(const sf::Vector2f &offset);
	virtual Question& move(float offsetX, float offsetY);

	virtual Question& setText(sf::String text);
	virtual Question& setFont(sf::Font &font);
	virtual Question& setCharacterSize(unsigned int characterSize);
	virtual Question& setTextColor(sf::Color textColor);

	virtual Question& update(float dt);
	virtual Question& render(sf::RenderTarget &target);

};
#pragma once

#include "SFML\Graphics.hpp"

struct TextInfo
{
	enum eHorizontalAlign
	{
		Left = 0,
		Middle = 1,
		Right = 2
	};
	enum eVerticalAlign
	{
		Top = 0,
		Center = 1,
		Bottom = 2
	};

	eHorizontalAlign horizontalAlign;
	eVerticalAlign verticalAlign;

	sf::Font *font;
	unsigned int characterSize;
	int lineSpacing;
	sf::Vector2f margin;
	sf::Color textColor;
	sf::Color backgroundColor;

	TextInfo();
	TextInfo(const TextInfo &textinfo);
	void operator =(const TextInfo &textinfo);

};
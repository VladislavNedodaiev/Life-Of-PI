#pragma once

#include <vector>
#include "TextInfo.h"

#include <iostream>

class Text
{
protected:

	sf::Texture _texture;
	sf::RenderTexture _renderTexture;
	sf::RectangleShape _box;

	sf::Text _text;
	std::vector <sf::String> _strings;
	TextInfo _textinfo;

	Text& createTexture();
	
	sf::Vector2f _size;
	sf::Vector2f _position;

public:

	Text();
	virtual ~Text();

	virtual Text& setPosition(const sf::Vector2f &position);
	virtual Text& setPosition(float x, float y);

	virtual Text& move(const sf::Vector2f &offset);
	virtual Text& move(float offsetX, float offsetY);

	Text& setTextInfo(TextInfo &textinfo);
	TextInfo getTextInfo();

	Text& operator=(const sf::String &string);

	Text& render(sf::RenderTarget &target);

};
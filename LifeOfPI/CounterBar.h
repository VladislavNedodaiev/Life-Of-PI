#pragma once

#include "SFML\Graphics.hpp"

class CounterBar
{
protected:

	sf::Vector2f _initialSize;
	sf::VertexArray _bar;

	float _rate;

public:

	CounterBar(sf::Vector2f size, sf::Color fillColor, float initialRate);
	virtual ~CounterBar();

	virtual CounterBar& setPosition(const sf::Vector2f &position);
	virtual CounterBar& setPosition(float x, float y);

	virtual CounterBar& move(const sf::Vector2f &offset);
	virtual CounterBar& move(float offsetX, float offsetY);

	virtual CounterBar& setSize(sf::Vector2f size);
	virtual sf::Vector2f getSize();

	virtual CounterBar& increase(float rate);
	virtual CounterBar& setRate(float rate);
	virtual CounterBar& setFull();
	virtual CounterBar& setEmpty();

	virtual float getRate();

	virtual CounterBar& setFillColor(sf::Color fillColor);

	virtual CounterBar& render(sf::RenderTarget &target);

};
#include "Litvinog.h"

Litvinog::Litvinog(sf::Image &sheet, int sceneLeftX, int sceneRightX) :
	Lecturer(sheet, sceneLeftX, sceneRightX) 
{
	setPosition(80, 46);
} // constructor

Litvinog::~Litvinog() {} // destructor

Litvinog& Litvinog::setPosition(const sf::Vector2f &position)
{
	GameObject::setPosition(sf::Vector2f(sf::Vector2i(position)));
	_position = position;

	return *this;
} // setting position

Litvinog& Litvinog::setPosition(float x, float y)
{
	return setPosition(sf::Vector2f(x, y));
} // setting position

Litvinog& Litvinog::move(const sf::Vector2f &offset)
{
	_position += offset;
	if (_position.x < _sceneLeftX)
		_position.x = _sceneLeftX;
	else if (_position.x > _sceneRightX)
		_position.x = _sceneRightX;

	setPosition(_position.x, _position.y);

	return *this;
} // move

Litvinog& Litvinog::move(float offsetX, float offsetY)
{
	return move(sf::Vector2f(offsetX, offsetY));
} // move
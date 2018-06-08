#include "Button.h"

Button::Button(sf::Image &spriteSheet, sf::IntRect firstFrame) :
	GameObject(spriteSheet, 2, 0, firstFrame) { } // constructor

Button::~Button() {} // destructor

bool Button::pointIsOver(sf::Vector2i &point)
{
	if (_currentAnimation != nullptr)
	{
		if (GameObject::pointIsOver(point))
		{
			if (!_currentAnimation->getFrame())
			{
				_currentAnimation->setFrame(1);
				_currentAnimation->updateTexture();
			} // if

			return true;
		} // if 

		if (_currentAnimation->getFrame())
		{
			_currentAnimation->setFrame(0);
			_currentAnimation->updateTexture();
		} // if
	} // if

	return false;
} // point is over

bool Button::isPressed(sf::Event &event, sf::Vector2i &point)
{
	if (pointIsOver(point) &&
		event.type == sf::Event::MouseButtonPressed)
		return true;

	return false;
} // checking if the button is pressed
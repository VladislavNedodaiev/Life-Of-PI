#include "Toggle.h"

Toggle::Toggle(sf::Image &toggle, sf::IntRect firstFrameOFF, sf::IntRect firstFrameON) :
	GameObject(toggle, 2, 0, firstFrameOFF)
{
	this->_toggleOFF = _currentAnimation;
	this->_toggleON = new Animation(firstFrameON, 2, 0, toggle, _texture);

	this->_toggled = false;
} // constructor

Toggle::~Toggle()
{
	delete _toggleOFF;
	delete _toggleON;
	_currentAnimation = nullptr;
} // destructor

bool Toggle::pointIsOver(sf::Vector2i &point)
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

bool Toggle::isPressed(sf::Event &event, sf::Vector2i &point)
{
	if (pointIsOver(point) &&
		event.type == sf::Event::MouseButtonPressed)
	{
		toggle();
		pointIsOver(point); // for frame change
		return true;
	} // if

	return false;
} // checking if the button is pressed

Toggle& Toggle::toggle()
{
	_toggled = !_toggled;
	
	if (_toggled)
		_currentAnimation = _toggleON;
	else
		_currentAnimation = _toggleOFF;

	_currentAnimation->updateTexture();

	return *this;
} // toggle the toggle (sounds pretty weird, yay)

Toggle& Toggle::setToggle(bool toggled)
{
	if (toggled != _toggled)
		toggle();

	return *this;
} // set the toggle state

bool Toggle::getToggle() const
{
	return _toggled;
} // get the toggle state
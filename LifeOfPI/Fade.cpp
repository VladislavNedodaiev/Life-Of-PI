#include "Fade.h"

Fade::Fade(float fps, sf::RectangleShape &object) : Behaviour(fps)
{
	this->_object = &object;
	this->_alpha = object.getFillColor().a;
	this->_fullFade = false;
	this->_fcount = 0;
} // constructor

Fade::Fade(float fps, sf::RectangleShape &object, bool fullFade) : Behaviour(fps)
{
	this->_object = &object;
	this->_alpha = object.getFillColor().a;
	this->_fullFade = fullFade;
	this->_fcount = 0;
} // constructor with "fullfade" arg

Fade& Fade::setFullFade(bool fullFade)
{
	_fullFade = true;
	return *this;
} // setting "fullfade" arg

Fade& Fade::setPlaying(bool playing)
{
	this->_playing = playing;
	this->_fcount = 0;
	return *this;
} // setting playing

bool Fade::getFullFade()
{
	return _fullFade;
} // getting _fullFade

Fade& Fade::update(float dt)
{
	if (!_playing)
		return *this;

	sf::Color color = _object->getFillColor();
	if ((int)_alpha != color.a)
		_alpha = color.a;

	_alpha += _dps * dt;

	if (_alpha > 255)
	{
		if (_looping)
		{
			if (_fullFade)
			{
				_dps = -_dps;
				_alpha = 255;
			}
			else
				_alpha -= ((int)_alpha / 255) * 255;
		} // if
		else if (_fullFade && _fcount == 0)
		{
			_dps = -_dps;
			_alpha = 255;
		} // else if
		else
		{
			_playing = false;
			_alpha = 255;
		}

		if (_fcount < 2)
			_fcount++;
	} // if
	else if (_alpha < 0)
	{
		if (_looping)
		{
			if (_fullFade)
			{
				_dps = -_dps;
				_alpha = 0;
			}
			else
				_alpha = 255 - (-(int)_alpha) % 255;
		} // if
		else if (_fullFade && _fcount == 0)
		{
			_dps = -_dps;
			_alpha = 0;
		} // else if
		else
		{
			_playing = false;
			_alpha = 0;
		}

		if (_fcount < 2)
			_fcount++;
	} // else if

	if ((int)_alpha != color.a)
		_object->setFillColor(sf::Color(color.r, color.g, color.b, _alpha));

	return *this;
} // update(float dt)
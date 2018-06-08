#include "Blink.h"

Blink::Blink(float bps, bool &visible) : Behaviour(bps)
{
	_blink = 0;

	if (_dps < 0)
		_dps = 0;

	_visible = &visible;
} // default constructor

Behaviour& Blink::update(float dt)
{
	if (_playing)
		_blink += dt * _dps;

	if (_blink >= 1)
	{
		if (!_looping)
		{
			_playing = false;
			_blink = 0;
		}
		if ((int)_blink % 2 != 0)
			*this->_visible = !*_visible;
		_blink -= (int)_blink;
	}

	return *this;
} // Behaviour& Blink::update(float dt)
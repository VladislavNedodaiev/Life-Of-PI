#pragma once

#include "Behaviour.h"

class Blink : public Behaviour
{
protected:

	float _blink;
	bool *_visible; // the external bool which determines whether the object is visible or not

public:

	Blink(float bps, bool &visible); // visible the external bool which determines whether the object is visible or not
	virtual Behaviour& update(float dt);

};
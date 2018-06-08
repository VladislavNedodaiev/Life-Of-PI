#pragma once

#include "SpriteSheet.h"

class Behaviour
{
protected:

	bool _looping;
	bool _playing;
	float _dps;

public:

	Behaviour();
	Behaviour(float dps);

	virtual Behaviour& setDPS(float dps);
	virtual Behaviour& setLooping(bool looping);
	virtual Behaviour& setPlaying(bool playing);

	virtual float getDPS() const;
	virtual bool getLooping() const;
	virtual bool getPlaying() const;

	virtual Behaviour& update(float dt) = 0;

};
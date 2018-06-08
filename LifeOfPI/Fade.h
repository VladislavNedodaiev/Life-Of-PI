#pragma once

#include "Behaviour.h"

class Fade : public Behaviour
{
protected:

	float _alpha;
	sf::RectangleShape *_object;
	bool _fullFade; // determines whether our fade is going to change the fading direction when the fade is over
	short _fcount; // value which saves the count of "fades"

public:

	// fps - fade per second. Color is the pointer to the object sf::Color
	Fade(float fps, sf::RectangleShape &object);
	Fade(float fps, sf::RectangleShape &object, bool fullFade);

	virtual Fade& setFullFade(bool fullFade);
	virtual Fade& setPlaying(bool playing);
	virtual bool getFullFade();

	virtual Fade& update(float dt);

};
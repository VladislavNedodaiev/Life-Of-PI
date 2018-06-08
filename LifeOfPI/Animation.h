#pragma once

#include "Behaviour.h"

class Animation : public Behaviour
{

	std::vector<sf::IntRect> _frames;
	int _framesCount;
	float _frame;

	sf::Image *_sheet;
	sf::Texture *_texture;

public:

	// creates animation pushing frames until
	// it reaches the end of the spritesheet
	Animation(sf::IntRect firstFrame,
			  float fps,
			  sf::Image &sheet,
			  sf::Texture &texture);

	// creates the animation depending on
	// "framesCount" variable
	Animation(sf::IntRect firstFrame,
			  int framesCount,
			  float fps,
			  sf::Image &sheet,
			  sf::Texture &texture);
	virtual ~Animation();

	virtual Animation& setPlaying(bool playing);
	virtual Animation& setFrame(int frame);

	virtual int getFrame() const;
	virtual int getFramesCount() const;

	virtual Animation& update(float dt);
	virtual Animation& updateTexture();

};
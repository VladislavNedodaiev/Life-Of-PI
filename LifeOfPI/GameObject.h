#pragma once

#include <SFML\Graphics.hpp>

#include "Animation.h"
#include "Blink.h"
#include "Fade.h"

class GameObject : public sf::RectangleShape
{
protected:

	sf::Texture _texture;

	Animation *_currentAnimation;
	Blink *_blink;
	Fade *_fade;

public:

	enum eInputType
	{
		None = 0
	};

	bool isVisible;
	bool isMovable;

	GameObject();
	GameObject(sf::Image &imageSheet);
	GameObject(sf::Image &imageSheet, float fps, sf::IntRect firstFrame);
	GameObject(sf::Image &imageSheet, int frames, float fps, sf::IntRect firstFrame);
	virtual ~GameObject();

	virtual GameObject& setAnimation(int animation);
	virtual GameObject& setFrame(int frame);
	virtual Animation* getAnimation();

	virtual bool pointIsOver(sf::Vector2i &point) const;
	virtual bool isPressed(sf::Event &event, sf::Vector2i &point) const;

	virtual Blink& createBlinker(float bps);
	virtual Fade& createFader(float fps, bool fullFade);

	virtual GameObject& move(const sf::Vector2f &offset);
	virtual GameObject& move(float offsetX, float offsetY);

	virtual int input(sf::Event &event, sf::Vector2i mousePos);
	virtual GameObject& update(float dt);
	virtual GameObject& render(sf::RenderTarget &target);
};
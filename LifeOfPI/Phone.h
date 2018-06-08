#pragma once

#include "SFML\Audio.hpp"
#include "Button.h"
#include "BasicSettings.h"

class Phone : public GameObject
{
protected:
	BasicSettings *_settings;

	int _ePhoneState;

	GameObject _topPanel;
	GameObject _display;
	GameObject _homeButton;

	sf::Sound _homeButtonClickSound;
	sf::Sound _tapSound;

public:

	enum ePhoneState
	{
		TurnedOff = 0,
		Home = 10
	};

	enum eInputType
	{
		None = 0,
		HomeButton = 10,
	};

	Phone(sf::Image &spriteSheet,
		  sf::SoundBuffer &homeButtonClickSB,
		  sf::SoundBuffer &tapSB,
		  BasicSettings &settings);
	virtual ~Phone();

	virtual Phone& setPosition(const sf::Vector2f &position);
	virtual Phone& setPosition(float x, float y);

	virtual Phone& move(const sf::Vector2f &offset);
	virtual Phone& move(float offsetX, float offsetY);

	virtual int input(sf::Event &event, sf::Vector2i mousePos);
	virtual Phone& update(float dt);
	virtual Phone& render(sf::RenderTarget &target);

};
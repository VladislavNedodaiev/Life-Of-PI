#pragma once

#include "State.h"
#include "MainMenuPhone.h"
#include "StateFader.h"
#include "HighMath.h"

class Menu : public State
{
protected:

	SpriteSheet _stateFaderSheet;
	//StateFader *_stateFader;

	sf::Music _backgroundMusic;
	
	sf::Sound _menuSound;

	SpriteSheet _backgroundSheet;

	SpriteSheet _pressSpaceSheet;
	sf::SoundBuffer _pressSpaceSound;

	// Phone
	sf::SoundBuffer _homeButtonClickSB;
	sf::SoundBuffer _tapSB;
	SpriteSheet _phoneSpriteSheet;

	GameObject *_background;

	GameObject *_pressSpace;

	MainMenuPhone *_phone;

	virtual Menu& initialize();

	virtual Menu& loadContent();
	virtual Menu& unloadContent();

public:

	Menu(GameHelper &gameHelper);
	virtual ~Menu();

	virtual State& input();

	virtual Menu& update(float dt);
	virtual Menu& render();

};
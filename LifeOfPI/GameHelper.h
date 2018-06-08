#pragma once

#include "GameObject.h"
#include "BasicSettings.h"
#include "Achievements.h"

class GameHelper
{
private:

	sf::View _view;

	double _total;
	int _marks;

public:

	bool isPlaying;
	
	sf::Font font;
	sf::RenderWindow renderWindow;
	sf::Event event;
	BasicSettings settings;
	Achievements achievements;

	GameHelper();
	~GameHelper();

	GameHelper& resetWindow();
	GameHelper& setLetterboxView();

	GameHelper& addMarkToTotal(double mark);
	double getTotal();
};
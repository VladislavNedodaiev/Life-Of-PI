#pragma once

#include "Game.h"
#include "MainActivity.h"

class LifeOfPIGame : public Game
{
protected:

	GameHelper _gameHelper;
	MainActivity _mainActivity;

	virtual LifeOfPIGame& loadContent();
	virtual LifeOfPIGame& unloadContent();

	virtual LifeOfPIGame& initialize();

	virtual LifeOfPIGame& input();

	virtual LifeOfPIGame& update();
	virtual LifeOfPIGame& render();

	float dt;

public:

	LifeOfPIGame();
	virtual ~LifeOfPIGame();

	virtual LifeOfPIGame& play();
};
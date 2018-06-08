#pragma once

#include "Activity.h"
#include "GameStateManager.h"
#include "Menu.h"

class MainActivity : public Activity
{
protected:
	virtual MainActivity& loadContent();
	virtual MainActivity& unloadContent();

	virtual MainActivity& initialize();

	GameHelper *_gameHelper;
	GameStateManager _gsm;

public:

	MainActivity(GameHelper &_gameHelper);

	virtual ~MainActivity();

	virtual MainActivity& input();

	virtual MainActivity& update(float dt);
	virtual MainActivity& render();

};
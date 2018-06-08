#pragma once

#include "State.h"
#include <vector>

class GameStateManager
{
	GameHelper *_gameHelper;

	std::vector <State*> _states;

	GameStateManager& clear();

public:

	GameStateManager(GameHelper &gameHelper);
	virtual ~GameStateManager();

	GameStateManager& pushState(State *state);
	GameStateManager& setState(State *state);
	GameStateManager& popState();

	unsigned long long getStatesCount();

	GameStateManager& input(); // reading the input

	GameStateManager& update(float dt); // updating the current state
	GameStateManager& render(); // rendering the objects of a current state

};
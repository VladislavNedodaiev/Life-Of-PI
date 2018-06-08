#pragma once

class Game
{
protected:

	virtual Game& loadContent() = 0;
	virtual Game& unloadContent() = 0;

	virtual Game& initialize() = 0;

	virtual Game& input() = 0;

	virtual Game& update() = 0;
	virtual Game& render() = 0;

public:

	virtual Game& play() = 0;
};
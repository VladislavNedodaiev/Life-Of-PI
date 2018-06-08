#include "LifeOfPIGame.h"

LifeOfPIGame::LifeOfPIGame() : _mainActivity(_gameHelper)
{
	this->loadContent().initialize();
} // constructor

LifeOfPIGame::~LifeOfPIGame()
{
	this->unloadContent();
} // destructor

LifeOfPIGame& LifeOfPIGame::loadContent()
{
	return *this;
} // loading needed resources (textures, sounds, music etc)

LifeOfPIGame& LifeOfPIGame::unloadContent()
{
	return *this;
} // unloading resources

LifeOfPIGame& LifeOfPIGame::initialize()
{
	return *this;
} // initialize (comes after loadContent)

LifeOfPIGame& LifeOfPIGame::input()
{
	while (this->_gameHelper.renderWindow.pollEvent(this->_gameHelper.event))
	{
		if (_gameHelper.event.type == sf::Event::Closed)
		{
			this->_gameHelper.renderWindow.close();
			this->_gameHelper.isPlaying = false;
		}
		else if (_gameHelper.event.type == sf::Event::Resized)
			this->_gameHelper.setLetterboxView();
		this->_mainActivity.input();
	}
	return *this;
} // update input

LifeOfPIGame& LifeOfPIGame::update()
{
	this->_mainActivity.update(dt);
	return *this;
} // updating the game

LifeOfPIGame& LifeOfPIGame::render()
{
	this->_gameHelper.renderWindow.clear();
	this->_mainActivity.render();
	this->_gameHelper.renderWindow.display();

	return *this;
} // rendering

LifeOfPIGame& LifeOfPIGame::play()
{
	sf::Clock dtClock;
	while (_gameHelper.isPlaying)
	{
		this->dt = dtClock.restart().asSeconds();
		this->update().render().input();
	}

	return *this;
} // play()
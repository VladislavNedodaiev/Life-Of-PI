#include "MainActivity.h"

MainActivity::MainActivity(GameHelper &_gameHelper) : _gsm(_gameHelper)
{
	this->_gameHelper = &_gameHelper;

	this->loadContent().initialize();
} // MainActivity::MainActivity

MainActivity::~MainActivity()
{
	this->unloadContent();
} // MainActivity::~MainActivity()

MainActivity& MainActivity::loadContent()
{
	return *this;
} // loading content (if any needed here)

MainActivity& MainActivity::unloadContent()
{
	return *this;
}

MainActivity& MainActivity::initialize()
{
	_gsm.pushState(new Menu(*_gameHelper));
	return *this;
}

MainActivity& MainActivity::input()
{
	this->_gsm.input();

	return *this;
}

MainActivity& MainActivity::update(float dt)
{
	_gsm.update(dt);
	if (_gsm.getStatesCount() == 0)
		this->_gameHelper->isPlaying = false;

	return *this;
}

MainActivity& MainActivity::render()
{
	this->_gsm.render();

	return *this;
}
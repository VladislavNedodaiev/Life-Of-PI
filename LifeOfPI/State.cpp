#include "State.h"

State::State(GameHelper &gameHelper)
{
	this->_gameHelper = &gameHelper;
	toDelete = false;
} // constructor

State::~State() {} // destructor
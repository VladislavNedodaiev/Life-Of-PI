#include "Behaviour.h"

Behaviour::Behaviour()
{
	this->_looping = false;
	this->_playing = true;
	this->_dps = 0;
} // default constructor

Behaviour::Behaviour(float dps)
{
	this->_looping = false;
	this->_playing = false;
	this->_dps = dps;
} // constructor with "delta per second"

Behaviour& Behaviour::setDPS(float dps)
{
	this->_dps = dps;
	return *this;
} // setting dps

Behaviour& Behaviour::setLooping(bool looping)
{
	this->_looping = looping;
	return *this;
} // setting looping 

Behaviour& Behaviour::setPlaying(bool playing)
{
	this->_playing = playing;
	return *this;
} // setting playing

float Behaviour::getDPS() const
{
	return this->_dps;
} // getting dps

bool Behaviour::getLooping() const
{
	return this->_looping;
} // getting looping

bool Behaviour::getPlaying() const
{
	return this->_playing;
} // getting playing
#pragma once

class Activity
{
protected:

	virtual Activity& loadContent() = 0;
	virtual Activity& unloadContent() = 0;

	virtual Activity& initialize() = 0;

public:

	virtual Activity& input() = 0;

	virtual Activity& update(float dt) = 0;
	virtual Activity& render() = 0;

};
#pragma once

#include "GameObject.h"

class Lecturer : public GameObject
{
protected:

	Animation *_idleAnimation;
	Animation *_activeAnimation;
	Animation *_questionAnimation;

	int _lecturerState;

	int _minTime;
	int _maxTime;
	float _timeLeft;
	
	sf::Vector2f _position;

	int _sceneLeftX;
	int _sceneRightX;

	float _moveSpeed;

	virtual Lecturer& idleUpdate();
	virtual Lecturer& walkUpdate();
	virtual Lecturer& activeUpdate();
	virtual Lecturer& questionUpdate();

public:
	enum eLecturerState
	{
		Idle = 0,
		Walk = 1,
		Active = 2,
		Question = 3
	};

	Lecturer(sf::Image &sheet, int sceneLeftX, int sceneRightX);
	virtual ~Lecturer();

	virtual Lecturer& setMinTime(int minTime);
	virtual Lecturer& setMaxTime(int maxTime);
	virtual int getMinTime();
	virtual int getMaxTime();

	virtual Lecturer& setMoveSpeed(float dx);
	virtual float getMoveSpeed();

	virtual Lecturer& setPosition(const sf::Vector2f &position);
	virtual Lecturer& setPosition(float x, float y);

	virtual Lecturer& move(const sf::Vector2f &offset);
	virtual Lecturer& move(float offsetX, float offsetY);

	virtual Lecturer& setState(eLecturerState state);
	virtual int getState();

	virtual Lecturer& update(float dt);

};
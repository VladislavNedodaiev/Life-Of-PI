#include "Lecturer.h"

Lecturer::Lecturer(sf::Image &sheet, int sceneLeftX, int sceneRightX, sf::Font *font) :
	GameObject(sheet, 1, 5, sf::IntRect(0, 0, 32, 38))
{
	_idleAnimation = _currentAnimation;
	_idleAnimation->setLooping(true);
	_activeAnimation = new Animation(sf::IntRect(32, 0, 32, 38), 2, 5, sheet, _texture);
	_activeAnimation->setLooping(true);
	_questionAnimation = new Animation(sf::IntRect(0, 38, 32, 38), 4, 5, sheet, _texture);
	_questionAnimation->setLooping(true);

	_minTime = 2;
	_maxTime = 6;
	setState(eLecturerState::Idle);

	_position = this->getPosition();

	_sceneLeftX = sceneLeftX;
	_sceneRightX = sceneRightX - this->getSize().x;

	_moveSpeed = 0.02;

	_textDuration = 0;
	TextInfo textinfo;
	textinfo.horizontalAlign = TextInfo::eHorizontalAlign::Middle;
	textinfo.verticalAlign = TextInfo::eVerticalAlign::Bottom;
	textinfo.font = font;
	textinfo.characterSize = 5;
	textinfo.backgroundColor = sf::Color::Transparent;
	sf::FloatRect rect = this->getGlobalBounds();
	_lecturerText.setTextInfo(textinfo).setPosition(
		sf::Vector2f((int)(rect.left + rect.width / 2), (int)(rect.top))
	);

} // constructor

Lecturer::~Lecturer()
{
	_currentAnimation = nullptr;
	delete _idleAnimation;
	delete _activeAnimation;
	delete _questionAnimation;
} // destructor

Lecturer& Lecturer::say(sf::String text, float duration)
{
	_lecturerText = text;
	_textDuration = duration;

	return *this;
} // say something

Lecturer& Lecturer::setMinTime(int minTime)
{
	if (minTime > 0) _minTime = minTime;

	return *this;
} // setting minimal time

Lecturer& Lecturer::setMaxTime(int maxTime)
{
	if (maxTime > _minTime)
		_maxTime = maxTime;

	return *this;
} // setting maximum time

int Lecturer::getMinTime()
{
	return _minTime;
} // getting mintime

int Lecturer::getMaxTime()
{
	return _maxTime;
} // getting maxtime

Lecturer& Lecturer::setState(eLecturerState state)
{
	_lecturerState = state;
	_timeLeft = std::rand() % (_maxTime - _minTime) + _minTime;

	switch (_lecturerState)
	{
	case eLecturerState::Idle:
		_currentAnimation = _idleAnimation;
		break;
	case eLecturerState::Walk:
		_moveSpeed *= (-1 + std::rand() % 2 * 2);
		if (_moveSpeed < 0)
		{
			setScale(-1, 1);
			setOrigin(getLocalBounds().width, 0);
		} // if
		else
		{
			setScale(1, 1);
			setOrigin(0, 0);
		} // else
		_currentAnimation = _idleAnimation;
		break;
	case eLecturerState::Active:
		_currentAnimation = _activeAnimation;
		break;
	case eLecturerState::Question:
		setScale(1, 1);
		setOrigin(0, 0);
		_currentAnimation = _questionAnimation;
		break;
	} // switch
	_currentAnimation->updateTexture();

	return *this;
} // setting state

int Lecturer::getState()
{
	return _lecturerState;
} // getting state

Lecturer& Lecturer::setMoveSpeed(float dx)
{
	_moveSpeed = dx;

	if (_moveSpeed < 0)
	{
		setScale(-1, 1);
		setOrigin(getLocalBounds().width, 0);
	} // if
	else
	{
		setScale(1, 1);
		setOrigin(0, 0);
	} // else

	return *this;
} // setting movespeed

float Lecturer::getMoveSpeed()
{
	return _moveSpeed;
} // getting movespeed

Lecturer& Lecturer::setPosition(const sf::Vector2f &position)
{
	GameObject::setPosition(sf::Vector2f(sf::Vector2i(position)));
	_position = position;

	sf::FloatRect rect = this->getGlobalBounds();
	_lecturerText.setPosition(
		sf::Vector2f((int)(rect.left + rect.width / 2), (int)(rect.top))
	);

	return *this;
} // setting position

Lecturer& Lecturer::setPosition(float x, float y)
{
	return setPosition(sf::Vector2f(x, y));
} // setting position

Lecturer& Lecturer::move(const sf::Vector2f &offset)
{
	_position += offset;
	if (_position.x < _sceneLeftX)
		_position.x = _sceneLeftX;
	else if (_position.x > _sceneRightX)
		_position.x = _sceneRightX;

	this->setPosition(_position);

	return *this;
} // move

Lecturer& Lecturer::move(float offsetX, float offsetY)
{
	return move(sf::Vector2f(offsetX, offsetY));
} // move

Lecturer& Lecturer::update(float dt)
{
	GameObject::update(dt);

	_timeLeft -= dt;
	if (_textDuration > 0)
		_textDuration -= dt;

	switch (_lecturerState)
	{
	case eLecturerState::Idle:
		return idleUpdate();
	case eLecturerState::Walk:
		return walkUpdate();
	case eLecturerState::Active:
		return activeUpdate();
	case eLecturerState::Question:
		return questionUpdate();
	} // switch

	return *this;
} // update

Lecturer& Lecturer::render(sf::RenderTarget &target)
{
	GameObject::render(target);

	if (isVisible && _textDuration > 0)
		_lecturerText.render(target);

	return *this;
} // rendering

Lecturer& Lecturer::idleUpdate()
{
	if (_timeLeft <= 0)
	{
		if (std::rand() % 3)
			return setState(eLecturerState::Walk);
		else
			return setState(eLecturerState::Active);
	} // if

	return *this;
} // update

Lecturer& Lecturer::walkUpdate()
{
	if (_timeLeft <= 0)
	{
		if (std::rand() % 3)
			return setState(eLecturerState::Idle);
		else
			return setState(eLecturerState::Active);
	} // if

	return move(_moveSpeed, 0);
} // update

Lecturer& Lecturer::activeUpdate()
{
	if (_timeLeft <= 0)
	{
		if (std::rand() % 3)
			return setState(eLecturerState::Walk);
		else
			return setState(eLecturerState::Idle);
	} // if

	return *this;
} // update

Lecturer& Lecturer::questionUpdate()
{
	return *this;
} // update
#include "GameObject.h"

GameObject::GameObject() : RectangleShape()
{
	_texture.create(0, 0);
	this->setTexture(&_texture);

	_currentAnimation = nullptr;
	_blink = nullptr;
	_fade = nullptr;

	isVisible = true;
	isMovable = true;

} // default constructor

GameObject::GameObject(sf::Image &imageSheet) : RectangleShape(sf::Vector2f(imageSheet.getSize()))
{
	_texture.create(imageSheet.getSize().x, imageSheet.getSize().y);
	this->setTexture(&_texture);

	_currentAnimation = new Animation(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(imageSheet.getSize())),
		1,
		0,
		imageSheet,
		_texture);

	_currentAnimation->updateTexture();

	_blink = nullptr;
	_fade = nullptr;

	isVisible = true;
	isMovable = true;

} // constructor

GameObject::GameObject(sf::Image &imageSheet, float fps, sf::IntRect firstFrame) :
	RectangleShape(sf::Vector2f(firstFrame.width, firstFrame.height))
{

	_texture.create(firstFrame.width, firstFrame.height);
	this->setTexture(&_texture);

	_currentAnimation = new Animation(firstFrame,
		fps,
		imageSheet,
		_texture);

	_currentAnimation->updateTexture();

	_blink = nullptr;
	_fade = nullptr;

	isVisible = true;
	isMovable = true;

} // creates the gameobject with the animation

GameObject::GameObject(sf::Image &imageSheet, int frames, float fps, sf::IntRect firstFrame) : 
	RectangleShape(sf::Vector2f(firstFrame.width, firstFrame.height))
{

	_texture.create(firstFrame.width, firstFrame.height);
	this->setTexture(&_texture);

	_currentAnimation = new Animation(firstFrame,
		frames,
		fps,
		imageSheet,
		_texture);

	_currentAnimation->updateTexture();

	_blink = nullptr;
	_fade = nullptr;

	isVisible = true;
	isMovable = true;

} // create with animation

GameObject::~GameObject()
{
	if (_currentAnimation != nullptr)
		delete _currentAnimation;
	if (_blink != nullptr)
		delete _blink;
	if (_fade != nullptr)
		delete _fade;
} // destructor

GameObject& GameObject::setAnimation(int animation)
{
	return *this;
} // set animation by number (doesn't work with GameObject, but is implemented in children)

GameObject& GameObject::setFrame(int frame)
{
	if (this->_currentAnimation != nullptr)
		this->_currentAnimation->setFrame(frame).updateTexture();

	return *this;
} // setting the frame for animation

Animation* GameObject::getAnimation()
{
	return _currentAnimation;
} // return current animation

bool GameObject::pointIsOver(sf::Vector2i &point) const
{
	if (this->getGlobalBounds().contains(sf::Vector2f(point)))
		return true;

	return false;
} // checking if mouse is over the button

bool GameObject::isPressed(sf::Event &event, sf::Vector2i &point) const
{
	if (pointIsOver(point) &&
		event.type == sf::Event::MouseButtonPressed)
		return true;

	return false;
} // checking if the button is pressed

Blink& GameObject::createBlinker(float bps = 0)
{
	if (_blink != nullptr)
		delete _blink;

	this->_blink = new Blink(bps, isVisible);
	return *this->_blink;
} // creating blink

Fade& GameObject::createFader(float fps = 0, bool fullFade = false)
{
	if (_fade != nullptr)
		delete _fade;

	this->_fade = new Fade(fps, *this, fullFade);
	return *this->_fade;
} // creating fade

GameObject& GameObject::move(const sf::Vector2f &offset)
{
	if (isMovable)
		RectangleShape::move(offset);

	return *this;
} // recshape move overload #1

GameObject& GameObject::move(float offsetX, float offsetY)
{
	if (isMovable)
		RectangleShape::move(offsetX, offsetY);

	return *this;
} // recshape move overload #2

int GameObject::input(sf::Event &event, sf::Vector2i mousePos)
{
	return None;
} // reading input

GameObject& GameObject::update(float dt)
{
	if (_currentAnimation != nullptr)
		_currentAnimation->update(dt);
	if (_blink != nullptr)
		_blink->update(dt);
	if (_fade != nullptr)
		_fade->update(dt);

	return *this;
} // update(dt)

GameObject& GameObject::render(sf::RenderTarget &target)
{
	if (isVisible)
		target.draw(*this);

	return *this;
}
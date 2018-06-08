#include "Phone.h"

Phone::Phone(sf::Image &spriteSheet,
			 sf::SoundBuffer &homeButtonClickSB,
			 sf::SoundBuffer &tapSB,
			 BasicSettings &settings) : GameObject(spriteSheet, 1, 0, sf::IntRect(0, 0, 70, 108)),
										_topPanel(spriteSheet, 1, 0, sf::IntRect(166, 72, 45, 3)),
									    _homeButton(spriteSheet, 1, 0, sf::IntRect(160, 72, 6, 6)),
									    _display(spriteSheet, 4, 0, sf::IntRect(0, 108, 45, 80))
{
	_settings = &settings;

	_ePhoneState = ePhoneState::Home;
	_display.setFrame(1);

	_topPanel.setPosition(9, 14);
	_homeButton.setPosition(29, 95);
	_display.setPosition(9, 14);

	_homeButtonClickSound.setBuffer(homeButtonClickSB);
	_tapSound.setBuffer(tapSB);

} // Phone constructor

Phone::~Phone() {} // destructor

Phone& Phone::setPosition(const sf::Vector2f &position)
{

	sf::Vector2f deltaPos = position - this->getPosition();

	RectangleShape::setPosition(position);
	_topPanel.setPosition(_topPanel.getPosition() + deltaPos);
	_homeButton.setPosition(_homeButton.getPosition() + deltaPos);
	_display.setPosition(_display.getPosition() + deltaPos);

	return *this;
} // setPosition overload, which is needed to change pos of every child element

Phone& Phone::setPosition(float x, float y)
{
	return this->setPosition(sf::Vector2f(x, y));
} // setPosition overload, which is needed to change pos of every child element

Phone& Phone::move(const sf::Vector2f &offset)
{
	if (isMovable)
	{
		RectangleShape::move(offset);
		_topPanel.move(offset);
		_homeButton.move(offset);
		_display.move(offset);
	} // if

	return *this;
} // recshape move overload #1

Phone& Phone::move(float offsetX, float offsetY)
{
	return this->move(sf::Vector2f(offsetX, offsetY));
} // recshape move overload #2

int Phone::input(sf::Event &event, sf::Vector2i mousePos)
{
	if (_homeButton.isPressed(event, mousePos))
	{
		if (_settings->sounds)
			_homeButtonClickSound.play();
		return HomeButton;
	} // if home button is pressed

	return None;
} // reading input

Phone& Phone::update(float dt)
{
	GameObject::update(dt);

	return *this;
} // update

Phone& Phone::render(sf::RenderTarget &target)
{

	if (isVisible)
	{
		target.draw(*this);
		target.draw(_homeButton);
		target.draw(_display);
	} // if

	return *this;
} // render
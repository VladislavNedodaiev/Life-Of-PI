#include "Answer.h"

Answer::Answer(sf::Image &sheet, 
			   sf::Font &font,
			   sf::IntRect firstFrame, 
			   sf::IntRect correctFrame,
			   sf::IntRect incorrectFrame, 
			   unsigned int characterSize, 
			   sf::Color textColor) : 
					Button(sheet, firstFrame)
{

	_notPressed = _currentAnimation;

	_text.setFont(font);
	setCharacterSize(characterSize);
	_text.setFillColor(textColor);

	isCorrect = false;

	_correctAnswer = new Animation(correctFrame, 1, 0, sheet, _texture);
	_incorrectAnswer = new Animation(incorrectFrame, 1, 0, sheet, _texture);

} // constructor

Answer::~Answer() 
{

	_currentAnimation = nullptr;
	delete _notPressed;
	delete _correctAnswer;
	delete _incorrectAnswer;

} // destructor

Answer& Answer::setPosition(const sf::Vector2f &position)
{
	sf::Vector2f deltaPos = position - this->getPosition();

	GameObject::setPosition(position);
	_text.setPosition(_text.getPosition() + deltaPos);

	return *this;
} // setting the position

Answer& Answer::setPosition(float x, float y)
{
	return this->setPosition(sf::Vector2f(x, y));
} // setting the position

Answer& Answer::move(const sf::Vector2f &offset)
{
	if (isMovable)
	{
		GameObject::move(offset);
		_text.move(offset);
	}

	return *this;
} // moving

Answer& Answer::move(float offsetX, float offsetY)
{
	return this->move(sf::Vector2f(offsetX, offsetY));
} // moving

Answer& Answer::setText(sf::String text)
{
	_text.setString(text);

	float fcenterX = getGlobalBounds().left + getGlobalBounds().width / 2.0;
	float fcenterY = getGlobalBounds().top + getGlobalBounds().height / 2.0;
	sf::Vector2f center = sf::Vector2f(fcenterX, fcenterY);

	
	float deltaX = -_text.getGlobalBounds().width / 2.0;
	float deltaY = -(_text.getCharacterSize() / 2.0) + 1;
	sf::Vector2f delta = sf::Vector2f(deltaX, deltaY);

	_text.setPosition(center + delta);

	return *this;
} // setting text

Answer& Answer::setFont(sf::Font &font)
{
	_text.setFont(font);

	float fcenterX = getGlobalBounds().left + getGlobalBounds().width / 2.0;
	float fcenterY = getGlobalBounds().top + getGlobalBounds().height / 2.0;
	sf::Vector2f center = sf::Vector2f(fcenterX, fcenterY);

	float deltaX = -_text.getGlobalBounds().width / 2.0;
	float deltaY = -(_text.getCharacterSize() / 2.0) + 1;
	sf::Vector2f delta = sf::Vector2f(deltaX, deltaY);

	_text.setPosition(center + delta);

	return *this;
} // setting font

Answer& Answer::setCharacterSize(unsigned int characterSize)
{
	const_cast<sf::Texture&>(_text.getFont()->getTexture(characterSize)).setSmooth(false);
	_text.setCharacterSize(characterSize);

	float fcenterX = getGlobalBounds().left + getGlobalBounds().width / 2.0;
	float fcenterY = getGlobalBounds().top + getGlobalBounds().height / 2.0;
	sf::Vector2f center = sf::Vector2f(fcenterX, fcenterY);

	float deltaX = -_text.getGlobalBounds().width / 2.0;
	float deltaY = -(_text.getCharacterSize() / 2.0) + 1;
	sf::Vector2f delta = sf::Vector2f(deltaX, deltaY);

	_text.setPosition(center + delta);

	return *this;
} // setting character size

Answer& Answer::setTextColor(sf::Color textColor)
{
	_text.setFillColor(textColor);

	return *this;
} // setting text color

bool Answer::isPressed(sf::Event &event, sf::Vector2i &point)
{
	if (_currentAnimation == _notPressed)
	{
		if (Button::isPressed(event, point))
		{
			if (isCorrect)
				_currentAnimation = _correctAnswer;
			else _currentAnimation = _incorrectAnswer;

			_currentAnimation->updateTexture();
			return true;
		} // if		
	} // if

	return false;
} // is pressed

Answer& Answer::reset()
{
	_currentAnimation = _notPressed;
	_currentAnimation->setFrame(0);
	_currentAnimation->updateTexture();
	isCorrect = false;

	return *this;
} // reset

Answer& Answer::update(float dt)
{
	GameObject::update(dt);

	return *this;
} // update

Answer& Answer::render(sf::RenderTarget &target)
{
	GameObject::render(target);
	target.draw(_text);

	return *this;
} // render
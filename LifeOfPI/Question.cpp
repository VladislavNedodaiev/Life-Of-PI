#include "Question.h"

Question::Question(sf::Image &sheet, 
				   sf::Font &font, 
				   sf::IntRect firstFrame,
				   unsigned int characterSize,
				   sf::Color textColor) : 
						GameObject(sheet, 1, 0, firstFrame)
{

	_text.setFont(font);
	setCharacterSize(characterSize);
	_text.setFillColor(textColor);

} // constructor

Question::~Question() {} // destructor

Question& Question::setPosition(const sf::Vector2f &position)
{
	sf::Vector2f deltaPos = position - this->getPosition();

	GameObject::setPosition(position);
	_text.setPosition(_text.getPosition() + deltaPos);

	return *this;
} // setting the position

Question& Question::setPosition(float x, float y)
{
	return this->setPosition(sf::Vector2f(x, y));
} // setting the position

Question& Question::move(const sf::Vector2f &offset)
{
	if (isMovable)
	{
		GameObject::move(offset);
		_text.move(offset);
	}

	return *this;
} // moving

Question& Question::move(float offsetX, float offsetY)
{
	return this->move(sf::Vector2f(offsetX, offsetY));
} // moving

Question& Question::setText(sf::String text)
{
	_text.setString(text);

	float fcenterX = getGlobalBounds().left + getGlobalBounds().width / 2.0;
	float fcenterY = getGlobalBounds().top + getGlobalBounds().height / 2.0;
	sf::Vector2f center = sf::Vector2f(fcenterX, fcenterY);

	float deltaX = -_text.getGlobalBounds().width / 2.0;
	float deltaY = -(_text.getGlobalBounds().height / 2.0) - 1;
	sf::Vector2f delta = sf::Vector2f(deltaX, deltaY);

	_text.setPosition(center + delta);

	return *this;
} // setting text

Question& Question::setFont(sf::Font &font)
{
	_text.setFont(font);

	float fcenterX = getGlobalBounds().left + getGlobalBounds().width / 2.0;
	float fcenterY = getGlobalBounds().top + getGlobalBounds().height / 2.0;
	sf::Vector2f center = sf::Vector2f(fcenterX, fcenterY);

	float deltaX = -_text.getGlobalBounds().width / 2.0;
	float deltaY = -(_text.getGlobalBounds().height / 2.0) - 1;
	sf::Vector2f delta = sf::Vector2f(deltaX, deltaY);

	_text.setPosition(center + delta);

	return *this;
} // setting font

Question& Question::setCharacterSize(unsigned int characterSize)
{

	const_cast<sf::Texture&>(_text.getFont()->getTexture(characterSize)).setSmooth(false);
	_text.setCharacterSize(characterSize);

	float fcenterX = getGlobalBounds().left + getGlobalBounds().width / 2.0;
	float fcenterY = getGlobalBounds().top + getGlobalBounds().height / 2.0;
	sf::Vector2f center = sf::Vector2f(fcenterX, fcenterY);

	float deltaX = -_text.getGlobalBounds().width / 2.0;
	float deltaY = -(_text.getGlobalBounds().height / 2.0) - 1;
	sf::Vector2f delta = sf::Vector2f(deltaX, deltaY);

	_text.setPosition(center + delta);

	return *this;
} // setting character size

Question& Question::setTextColor(sf::Color textColor)
{
	_text.setFillColor(textColor);

	return *this;
} // setting text color

Question& Question::update(float dt)
{
	GameObject::update(dt);

	return *this;
} // update

Question& Question::render(sf::RenderTarget &target)
{
	GameObject::render(target);
	target.draw(_text);

	return *this;
} // render
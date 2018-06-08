#pragma once

#include "Button.h"

class Answer : public Button
{
protected:

	sf::Text _text;
	
	Animation *_notPressed;
	Animation *_correctAnswer;
	Animation *_incorrectAnswer;

public:
	bool isCorrect;

	Answer(sf::Image &sheet,
		   sf::Font &font,
		   sf::IntRect firstFrame,
		   sf::IntRect correctFrame,
		   sf::IntRect incorrectFrame,
		   unsigned int characterSize,
		   sf::Color textColor);
	virtual ~Answer();

	virtual Answer& setPosition(const sf::Vector2f &position);
	virtual Answer& setPosition(float x, float y);

	virtual Answer& move(const sf::Vector2f &offset);
	virtual Answer& move(float offsetX, float offsetY);

	virtual Answer& setText(sf::String text);
	virtual Answer& setFont(sf::Font &font);
	virtual Answer& setCharacterSize(unsigned int characterSize);
	virtual Answer& setTextColor(sf::Color textColor);

	// returns true only once while state changed
	virtual bool isPressed(sf::Event &event, sf::Vector2i &point);
	virtual Answer& reset();

	virtual Answer& update(float dt);
	virtual Answer& render(sf::RenderTarget &target);

};
#pragma once

#include <random>
#include <SFML\Graphics.hpp>

struct QuizAnswerData
{
	bool isCorrect;
	sf::String answer;

	QuizAnswerData();
	virtual QuizAnswerData& clear();
};

struct QuizQuestionData
{

	float duration;
	float waitDuration;

	sf::String question;
	sf::String reactionOnCorrect;
	sf::String reactionOnIncorrect;
	sf::String reactionOnTimelimit;
	QuizAnswerData answers[3];

	QuizQuestionData();
	virtual QuizQuestionData& clear();

	virtual QuizQuestionData& pushAnswer(sf::String answer, bool isCorrect);
	virtual bool hasFreeSpace();
	
};
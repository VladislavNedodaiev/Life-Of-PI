#pragma once

#include "SFML\Audio.hpp"

#include "GameHelper.h"
#include "Question.h"
#include "Answer.h"
#include "CounterBar.h"
#include "QuizQuestionData.h"

class Quiz
{
protected:

	BasicSettings *_settings;

	sf::Sound _correctAnswerSound;
	sf::Sound _incorrectAnswerSound;
	sf::Sound _tictacSound;

	QuizQuestionData *_quizData;

	Question _question;
	GameObject _answers;
	Answer _answer1;
	Answer _answer2;
	Answer _answer3;

	CounterBar _timeBar;

	float _initialTime;
	float _timeLeft;
	float _waitTime;

	int _quizState;

	virtual Quiz& correctAnswer();
	virtual Quiz& incorrectAnswer();
	virtual Quiz& timelimit();

public:

	enum eInput
	{
		NoneInput = 0,
		Correct = 1,
		Incorrect = 2
	};

	enum eQuizState
	{
		None = 0,
		Active = 1,
		Paused = 2,
		Wait = 3
	};

	enum eUpdateResult
	{
		NoResult = 0,
		Closed = 1,
		TimelimitExceed = 2
	};

	Quiz(sf::Image &quiz,
		 sf::Font &font,
		 BasicSettings &settings,
		 sf::SoundBuffer &correctSound, 
		 sf::SoundBuffer &incorrectSound,
		 sf::SoundBuffer &tictacSound);
	virtual ~Quiz();

	virtual int input(sf::Event &event, sf::Vector2i mousePos);

	virtual Quiz& start(QuizQuestionData &quizData);
	virtual Quiz& pause();
	virtual Quiz& unpause();
	virtual Quiz& stop();

	virtual int getQuizState();

	virtual int update(float dt);
	virtual Quiz& render(sf::RenderTarget &target);

};
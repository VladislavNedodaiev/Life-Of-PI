#include "Quiz.h"

Quiz::Quiz(sf::Image &quiz,
		   sf::Font &font,
		   BasicSettings &settings,
		   sf::SoundBuffer &correctSound,
		   sf::SoundBuffer &incorrectSound,
		   sf::SoundBuffer &tictacSound) :
				_question(quiz, 
					font, 
					sf::IntRect(183, 22, 183, 25),
					5,
					sf::Color::Black),
				_answers(quiz, 1, 0, 
					sf::IntRect(0, 22, 183, 43)),
				_answer1(quiz, font, 
					sf::IntRect(0, 0, 175, 11),
					sf::IntRect(0, 11, 175, 11),
					sf::IntRect(175, 11, 175, 11),
					5, sf::Color::Black),
				_answer2(quiz, font,
					sf::IntRect(0, 0, 175, 11),
					sf::IntRect(0, 11, 175, 11),
					sf::IntRect(175, 11, 175, 11),
					5, sf::Color::Black),
				_answer3(quiz, font,
					sf::IntRect(0, 0, 175, 11),
					sf::IntRect(0, 11, 175, 11),
					sf::IntRect(175, 11, 175, 11),
					5, sf::Color::Black),
				_timeBar(sf::Vector2f(175, 5), sf::Color::Green, 1.0)
{

	_question.setPosition(4, 7);
	_answers.setPosition(5, 64);
	_answer1.setPosition(9, 68);
	_answer2.setPosition(9, 79);
	_answer3.setPosition(9, 90);
	_timeBar.setPosition(9, 1);

	_settings = &settings;

	_correctAnswerSound.setBuffer(correctSound);
	_incorrectAnswerSound.setBuffer(incorrectSound);
	_tictacSound.setBuffer(tictacSound);

	_initialTime = 10;
	_timeLeft = 0;
	_waitTime = 3;

	_quizState = eQuizState::None;

} // constructor

Quiz::~Quiz() {} // destructor

int Quiz::input(sf::Event &event, sf::Vector2i mousePos)
{
	if (_quizState == eQuizState::Active)
	{
		if (_answer1.isPressed(event, mousePos))
		{
			if (_answer1.isCorrect)
				return correctAnswer().Correct;
			else
				return incorrectAnswer().Incorrect;
		} // if
		else if (_answer2.isPressed(event, mousePos))
		{
			if (_answer2.isCorrect)
				return correctAnswer().Correct;
			else
				return incorrectAnswer().Incorrect;
		} // else if
		else if (_answer3.isPressed(event, mousePos))
		{
			if (_answer3.isCorrect)
				return correctAnswer().Correct;
			else
				return incorrectAnswer().Incorrect;
		} // else if
	} // if active
	else {
		_answer1.pointIsOver(mousePos);
		_answer2.pointIsOver(mousePos);
		_answer3.pointIsOver(mousePos);
	}

	return eInput::NoneInput;
} // input

Quiz& Quiz::start(QuizQuestionData &quizData)
{
	_quizData = &quizData;

	if (_quizData != nullptr)
	{
		_tictacSound.play();

		_initialTime = _quizData->duration;
		_waitTime = _quizData->waitDuration;

		_timeLeft = _initialTime;
		_timeBar.setFull();
		_quizState = eQuizState::Active;

		_question.setText(_quizData->question);

		_answer1.reset().setText(_quizData->answers[0].answer)
			.isCorrect = _quizData->answers[0].isCorrect;

		_answer2.reset().setText(_quizData->answers[1].answer)
			.isCorrect = _quizData->answers[1].isCorrect;

		_answer3.reset().setText(_quizData->answers[2].answer)
			.isCorrect = _quizData->answers[2].isCorrect;
	}

	return *this;
} // start

Quiz& Quiz::pause()
{
	_quizState = eQuizState::Paused;
	_tictacSound.pause();

	return *this;
} // pause

Quiz& Quiz::unpause()
{
	_quizState = eQuizState::Active;
	_tictacSound.play();

	return *this;
} // pause

Quiz& Quiz::stop()
{
	_quizData = nullptr;
	_timeLeft = 0;
	_quizState = eQuizState::None;
	_tictacSound.stop();

	return *this;
} // stop

int Quiz::getQuizState()
{
	return (int)_quizState;
} // getting quiz state

int Quiz::update(float dt)
{
	if (_quizState == eQuizState::Paused ||
		_quizState == eQuizState::None)
		return eUpdateResult::NoResult;

	_timeLeft -= dt;

	if (_quizState == eQuizState::Active)
	{
		if (_timeLeft <= 0)
		{
			timelimit();
			return eUpdateResult::TimelimitExceed;
		} // if

		_timeBar.setRate(_timeLeft / _initialTime);
	} // if
	else if (_timeLeft <= 0)
	{
		stop();
		return eUpdateResult::Closed;
	} // else if

	return NoResult;
} // update

Quiz& Quiz::render(sf::RenderTarget &target)
{
	if (_quizState != eQuizState::None)
	{
		_question.render(target);
		_answers.render(target);
		_answer1.render(target);
		_answer2.render(target);
		_answer3.render(target);

		_timeBar.render(target);
	} // if

	return *this;
} // render

Quiz& Quiz::correctAnswer()
{
	if (_quizData != nullptr)
		_question.setText(_quizData->reactionOnCorrect);
	if (_settings->sounds)
		_correctAnswerSound.play();
	_timeLeft = _waitTime;
	_quizState = eQuizState::Wait;
	_tictacSound.stop();

	return *this;
} // correctAnswer

Quiz& Quiz::incorrectAnswer()
{
	if (_quizData != nullptr)
		_question.setText(_quizData->reactionOnIncorrect);
	_timeBar.setEmpty();
	if (_settings->sounds)
		_incorrectAnswerSound.play();
	_timeLeft = _waitTime;
	_quizState = eQuizState::Wait;
	_tictacSound.stop();

	return *this;
} // incorectAnswer

Quiz& Quiz::timelimit()
{
	if (_quizData != nullptr)
		_question.setText(_quizData->reactionOnTimelimit);
	_timeBar.setEmpty();
	if (_settings->sounds)
		_incorrectAnswerSound.play();
	_timeLeft = _waitTime;
	_quizState = eQuizState::Wait;
	_tictacSound.stop();

	return *this;
} // on time limit exceeded

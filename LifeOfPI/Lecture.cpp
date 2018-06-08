#include "Lecture.h"

Lecture::Lecture(GameHelper &gameHelper) : State(gameHelper) 
{
	loadContent().initialize();
} // constructor

Lecture::~Lecture()
{
	unloadContent();
} // destructor

Lecture& Lecture::startWait()
{
	_wait = std::rand() % (_maxWait - _minWait) + _minWait;

	return *this;
} // start waiting for next quiz

Lecture& Lecture::initialize()
{
	_minWait = 5;
	_maxWait = 15;
	_lectureState = eLectureState::None;

	_quiz = new Quiz(_quizSheet.getSheet(),
		_gameHelper->font,
		_gameHelper->settings,
		_correctAnswerBuffer,
		_incorrectAnswerBuffer,
		_tictacBuffer);

	return *this;
} // initializing

Lecture& Lecture::loadContent()
{
	_correctAnswerBuffer.loadFromFile("Data/Levels/CorrectAnswer.wav");
	_incorrectAnswerBuffer.loadFromFile("Data/Levels/IncorrectAnswer.wav");
	_tictacBuffer.loadFromFile("Data/Levels/Tic-Tac.wav");

	_quizSheet.load("Data/Levels/QuizSheet.png");

	return *this;
} // loading content

Lecture& Lecture::unloadContent()
{
	delete _background;
	delete _foreground;
	delete _quiz;

	_speakings.clear();
	_correctAnswers.clear();
	_incorrectAnswers.clear();
	_timelimitExceeded.clear();

	_backgroundMusic.stop();

	return *this;
} // unloading content
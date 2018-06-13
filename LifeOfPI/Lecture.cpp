#include "Lecture.h"

Lecture::Lecture(GameHelper &gameHelper) : State(gameHelper) 
{
	loadContent().initialize();
} // constructor

Lecture::~Lecture()
{
	unloadContent();
} // destructor

Lecture& Lecture::initialize()
{
	_quizType = eQuizType::Easy;
	_lectureTime = 90.0;
	_timePassed = 0;
	_easyCount = 0;
	_mediumCount = 0;
	_hardCount = 0;
	_quizCount = 0;
	generateWait();
	
	_endLecture = false;

	TextInfo textinfo;
	textinfo.horizontalAlign = TextInfo::eHorizontalAlign::Left;
	textinfo.verticalAlign = TextInfo::eVerticalAlign::Top;
	textinfo.font = &_gameHelper->font;
	textinfo.characterSize = 5;
	textinfo.backgroundColor = sf::Color::Transparent;
	//_timer.setTextInfo(textinfo).setPosition(sf::Vector2f(_gameHelper->settings.VIEW_SIZEX, 0));
	_timer.setTextInfo(textinfo).setPosition(sf::Vector2f(0, 0));

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
	delete _lecturer;

	_speakings.clear();
	_correctAnswers.clear();
	_incorrectAnswers.clear();
	_timelimitExceeded.clear();

	_backgroundMusic.stop();

	return *this;
} // unloading content

Lecture& Lecture::generateWait()
{
	int icase = (int)(_timePassed / _lectureTime * 3.0);

	switch (icase)
	{
	default:
		if ((int)((_timePassed + 5.0) / _lectureTime * 3.0) != icase)
			_wait = _lectureTime * 3.0 - _timePassed;
		else _wait = 5.0;
		break;
	case 1:
		if ((int)((_timePassed + 5.0) / _lectureTime * 3.0) != icase)
			_wait = _lectureTime / 3.0 * 2.0 - _timePassed;
		else _wait = 3.0;
		break;
	case 2:
		_wait = 0.0;
		break;
	} // switch

	return *this;
} // generating wait time (waiting for the next question)

Lecture& Lecture::generateQuiz()
{
	if (_quiz == nullptr)
		return *this;

	if (_lecturer != nullptr)
		_lecturer->setState(Lecturer::eLecturerState::Question);

	_quizData.clear();

	switch ((int)(_timePassed / _lectureTime * 3.0))
	{
	default:
		generateEasy();
		break;
	case 1:
		generateMedium();
		break;
	case 2:
		generateHard();
		break;
	} // switch
	_quizCount++;
	

	if (_correctAnswers.size() > 0)
		_quizData.reactionOnCorrect = _correctAnswers[std::rand() % _correctAnswers.size()];
	if (_incorrectAnswers.size() > 0)
		_quizData.reactionOnIncorrect = _incorrectAnswers[std::rand() % _incorrectAnswers.size()];
	if (_timelimitExceeded.size() > 0)
		_quizData.reactionOnTimelimit = _timelimitExceeded[std::rand() % _timelimitExceeded.size()];

	_quiz->start(_quizData);

	return *this;
} // generating quiz

double Lecture::generateTotal()
{
	double mark = 0;

	mark += _easyCount / _quizCount * 50.0;
	mark += _mediumCount / _quizCount * 30.0;
	mark += _hardCount / _quizCount * 20.0;

	return mark;
} // generating mark

Lecture& Lecture::input()
{
	sf::Vector2i mousePos = sf::Vector2i(_gameHelper->renderWindow.mapPixelToCoords(sf::Mouse::getPosition(_gameHelper->renderWindow)));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		toDelete = true;
	if (_quiz != nullptr)
	{
		int inp = _quiz->input(_gameHelper->event, mousePos);
		if (inp == Quiz::eInput::Correct)
		{ 
			if (_quizType == eQuizType::Easy)
				_easyCount++;
			else if (_quizType == eQuizType::Medium)
				_mediumCount++;
			else _hardCount++;
		} // if
	} // if

	return *this;
} // input

Lecture& Lecture::update(float dt)
{
	//
	// timer
	//
	if ((int)(_timePassed + dt) != (int)_timePassed)
	{
		std::string tm = "";

		int minutes = (_lectureTime - _timePassed) / 60.0;
		if (minutes < 0)
			minutes = 0;
		double seconds = (_lectureTime - _timePassed) - minutes * 60;
		if (seconds < 0)
			seconds = 0;

		if (minutes < 10)
			tm += "0";
		if (minutes < 1)
			tm += "0";
		else tm += std::to_string(minutes);
		tm += ":";

		if ((int)seconds < 10)
			tm += "0";
		if ((int)seconds < 1)
			tm += "0";
		else tm += std::to_string((int)seconds);

		_timer = sf::String(tm);
	} // if

	// update
	_timePassed += dt;
	if (_timePassed < _lectureTime)
	{
		if (_quiz != nullptr)
		{
			if (_quiz->getQuizState() == Quiz::eQuizState::None)
			{
				_wait -= dt;
				if (_wait < 0)
					generateQuiz();
			} // if
			else if (_quiz->update(dt) == Quiz::eUpdateResult::Closed)
			{
				_lecturer->setState(Lecturer::eLecturerState::Idle);
				generateWait();
			} // else if
		} // if
	} // if
	else
	{
		if (!_endLecture)
		{
			if (_quiz == nullptr ||
				_quiz->getQuizState() == Quiz::eQuizState::None ||
				_quiz->update(dt) == Quiz::eUpdateResult::Closed)
			{
				_wait = 5.0;
				if (_lecturer != nullptr && _finalWords.size() > 0)
					_lecturer->say(_finalWords[std::rand() % _finalWords.size()], 3.0);
			} // if
		} // if
		else
		{
			_wait -= dt;
			if (_wait <= 0.0)
				toDelete = true;
		} // else
	} // else
	if (_lecturer != nullptr)
		_lecturer->update(dt);

	return *this;
} // update

Lecture& Lecture::render()
{
	if (_background != nullptr)
		_background->render(_gameHelper->renderWindow);

	if (_lecturer != nullptr)
		_lecturer->render(_gameHelper->renderWindow);

	if (_foreground != nullptr)
		_foreground->render(_gameHelper->renderWindow);

	if (_quiz != nullptr)
		_quiz->render(_gameHelper->renderWindow);

	_timer.render(_gameHelper->renderWindow);

	return *this;
} // rendering
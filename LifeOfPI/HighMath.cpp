#include "HighMath.h"

HighMath::HighMath(GameHelper &gameHelper) : Lecture(gameHelper)
{
	this->loadContent().initialize();
} // constructor

HighMath::~HighMath() 
{
	unloadContent();
} // destructor

HighMath& HighMath::initialize()
{
	TextInfo textinfo;
	textinfo.horizontalAlign = TextInfo::eHorizontalAlign::Middle;
	textinfo.verticalAlign = TextInfo::eVerticalAlign::Top;
	textinfo.font = &_gameHelper->font;
	textinfo.characterSize = 5;
	textinfo.backgroundColor = sf::Color::Transparent;
	text.setTextInfo(textinfo);
	//text = sf::String(L"ÓÂÀÃÀ ÑÒÓÄÅÍÒÈ, ÓÂÀÃÀ!");
	text.setPosition(sf::Vector2f(_gameHelper->settings.VIEW_SIZEX / 2, _gameHelper->settings.VIEW_SIZEY / 2));

	_currentQuiz = 0;
	_easyCount = 2;
	_mediumCount = 1;
	_hardCount = 1;
	_insaneCount = 1;
	_quizCount = _easyCount + _mediumCount + _hardCount + _insaneCount;

	_handwrite.setBuffer(_handwriteBuffer);
	_handwrite.setLoop(true);
	if (_gameHelper->settings.sounds)
		_handwrite.play();

	_background = new GameObject(_backgroundSheet.getSheet());
	_foreground = new GameObject(_foregroundSheet.getSheet());
	_foreground->setPosition(0, _gameHelper->settings.VIEW_SIZEY - _foreground->getSize().y);
	_litvinog = new Litvinog(_lecturerSheet.getSheet(), 32, 163);

	return *this;
} // initialize

HighMath& HighMath::loadContent()
{
	loadSpeakings().loadCorrectAnswers().loadIncorrectAnswers().loadTimelimitExceeded();

	_handwriteBuffer.loadFromFile("Data/Levels/HighMath/Handwriting.wav");

	_backgroundSheet.load("Data/Levels/HighMath/Background.png");
	_foregroundSheet.load("Data/Levels/HighMath/Foreground.png");
	_lecturerSheet.load("Data/Levels/HighMath/LitvinogSheet.png");

	return *this;
} // load content

HighMath& HighMath::unloadContent()
{
	delete _litvinog;
	_handwrite.stop();

	return *this;
} // unload

HighMath& HighMath::loadSpeakings()
{
	std::wstring string;
	std::wifstream ifstream("Data/Levels/HighMath/Speakings.dat");
	 
	while (ifstream.is_open() && !ifstream.eof())
	{
		std::getline(ifstream, string);
		_speakings.push_back(sf::String(string));
	} // while

	ifstream.close();

	return *this;
} // load speakings

HighMath& HighMath::loadCorrectAnswers()
{
	std::wstring string;
	std::wifstream ifstream("Data/Levels/HighMath/CorrectAnswer.dat");

	while (ifstream.is_open() && !ifstream.eof())
	{
		std::getline(ifstream, string);
		_correctAnswers.push_back(sf::String(string));
	} // while

	ifstream.close();

	return *this;
} // load correct answers

HighMath& HighMath::loadIncorrectAnswers()
{
	std::wstring string;
	std::wifstream ifstream("Data/Levels/HighMath/IncorrectAnswer.dat");

	while (ifstream.is_open() && !ifstream.eof())
	{
		std::getline(ifstream, string);
		_incorrectAnswers.push_back(sf::String(string));
	} // while

	ifstream.close();

	return *this;
} // load incorrect answers

HighMath& HighMath::loadTimelimitExceeded()
{
	std::wstring string;
	std::wifstream ifstream("Data/Levels/HighMath/TimelimitExceeded.dat");

	while (ifstream.is_open() && !ifstream.eof())
	{
		std::getline(ifstream, string);
		_timelimitExceeded.push_back(sf::String(string));
	} // while

	ifstream.close();

	return *this;
} // loading timelimitexceeded

HighMath& HighMath::generateQuiz()
{
	if (_quiz == nullptr)
		return *this;

	_quizData.clear();

	_litvinog->setState(Lecturer::eLecturerState::Question);

	generateEasy();

	if (_correctAnswers.size() > 0)
		_quizData.reactionOnCorrect = _correctAnswers[std::rand() % _correctAnswers.size()];
	if (_incorrectAnswers.size() > 0)
		_quizData.reactionOnIncorrect = _incorrectAnswers[std::rand() % _incorrectAnswers.size()];
	if (_timelimitExceeded.size() > 0)
		_quizData.reactionOnTimelimit = _timelimitExceeded[std::rand() % _timelimitExceeded.size()];

	_quiz->start(_quizData);

	return *this;
} // input

HighMath& HighMath::generateEasy()
{
	int x;
	int y;
	wchar_t operation;
	int result;

	switch (std::rand() % 5)
	{
	default:
		operation = '+';
		x = std::rand() % 45 + 5;
		y = std::rand() % 45 + 5;
		result = x + y;
		break;
	case 1:
		operation = '-';
		x = std::rand() % 45 + 5;
		y = std::rand() % 45 + 5;
		result = x - y;
		break;
	case 2:
		operation = 'x';
		x = std::rand() % 45 + 5;
		y = std::rand() % 8 + 2;
		result = x * y;
		break;
	case 3:
		operation = '/';
		result = std::rand() % 48 + 2;
		y = std::rand() % (100 / result - 1) + 2;
		x = result * y;
		break;
	} // operations

	_quizData.duration = 8;
	_quizData.waitDuration = 3;

	_quizData.question = L"Ïîðàõóéòå " + std::to_wstring(x) + operation + std::to_wstring(y) + L" = ?";
	_quizData.pushAnswer(std::to_wstring(result), true);
	_quizData.pushAnswer(std::to_wstring(result + std::rand() % 10 + 2), false);
	_quizData.pushAnswer(std::to_wstring(result + std::rand() % 30 + 15), false);

	return *this;
} // generate easy

HighMath& HighMath::generateMedium()
{

	return *this;
} // generate easy
HighMath& HighMath::generateHard()
{

	return *this;
} // generate easy
HighMath& HighMath::generateInsane()
{

	return *this;
} // generate easy
HighMath& HighMath::startWait()
{
	_wait = std::rand() % 10 + 5;

	return *this;
} // start waiting (wait = rand)

State& HighMath::input()
{
	sf::Vector2i mousePos = sf::Vector2i(_gameHelper->renderWindow.mapPixelToCoords(sf::Mouse::getPosition(_gameHelper->renderWindow)));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		toDelete = true;
	if (_quiz != nullptr)
	{
		int inp = _quiz->input(_gameHelper->event, mousePos);
		if (inp == Quiz::eInput::Correct)
			_gameHelper->addMarkToTotal(100);
		else if (inp == Quiz::eInput::Incorrect)
			_gameHelper->addMarkToTotal(0);
	} // if

	return *this;
} // input

HighMath& HighMath::update(float dt)
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
			_litvinog->setState(Lecturer::eLecturerState::Idle);
			startWait();
			/*_quizCurrentCount++;
			if (_quizCurrentCount > 2)
			{
				toDelete = true;
				printf("%f", _gameHelper->getTotal());
			}*/
		} // else if
	} // if
	if (_litvinog != nullptr)
		_litvinog->update(dt);
	return *this;
} // update

HighMath& HighMath::render()
{
	if (_background != nullptr)
		_background->render(_gameHelper->renderWindow);

	if (_litvinog != nullptr)
		_litvinog->render(_gameHelper->renderWindow);

	if (_foreground != nullptr)
		_foreground->render(_gameHelper->renderWindow);

	if (_quiz != nullptr)
		_quiz->render(_gameHelper->renderWindow);

	//text.render(_gameHelper->renderWindow);

	return *this;
} // rendering
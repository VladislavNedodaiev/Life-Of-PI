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
	_handwrite.setBuffer(_handwriteBuffer);
	_handwrite.setLoop(true);
	if (_gameHelper->settings.sounds)
		_handwrite.play();

	_background = new GameObject(_backgroundSheet.getSheet());
	_foreground = new GameObject(_foregroundSheet.getSheet());
	_foreground->setPosition(0, _gameHelper->settings.VIEW_SIZEY - _foreground->getSize().y);
	_lecturer = new Litvinog(_lecturerSheet.getSheet(), 32, 163, &_gameHelper->font);

	_backgroundMusic.setVolume(70);

	return *this;
} // initialize

HighMath& HighMath::loadContent()
{
	loadSpeakings().loadCorrectAnswers().loadIncorrectAnswers().loadTimelimitExceeded().loadFinalWords();

	_handwriteBuffer.loadFromFile("Data/Levels/HighMath/Handwriting.wav");
	_backgroundMusic.openFromFile("Data/Levels/HighMath/BackgroundMusic.ogg");

	_backgroundSheet.load("Data/Levels/HighMath/Background.png");
	_foregroundSheet.load("Data/Levels/HighMath/Foreground.png");
	_lecturerSheet.load("Data/Levels/HighMath/LitvinogSheet.png");

	return *this;
} // load content

HighMath& HighMath::unloadContent()
{
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

HighMath& HighMath::loadFinalWords()
{
	std::wstring string;
	std::wifstream ifstream("Data/Levels/HighMath/FinalWords.dat");

	while (ifstream.is_open() && !ifstream.eof())
	{
		std::getline(ifstream, string);
		_finalWords.push_back(sf::String(string));
	} // while

	ifstream.close();

	return *this;
} // load final words

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

	if (_easyCount + 3 < 5)
		_quizData.duration = 5 - _easyCount;
	else _quizData.duration = 3;
	_quizData.waitDuration = 2;

	_quizData.question = L"Порахуйте " + std::to_wstring(x) + operation + std::to_wstring(y) + L" = ?";
	_quizData.pushAnswer(std::to_wstring(result), true);
	_quizData.pushAnswer(std::to_wstring(result + std::rand() % 10 + 2), false);
	_quizData.pushAnswer(std::to_wstring(result + std::rand() % 30 + 15), false);

	return *this;
} // generate easy

HighMath& HighMath::generateMedium()
{
	int x;
	int y;
	int z;
	int num;
	wchar_t operationA, operationB;
	int result;
	switch (std::rand() % 2)
	{
	default:
		result = std::rand() % 10 + 2;
		num = result * result;
		switch (std::rand() % 3)
		{
		default:
			operationA = '+';
			x = std::rand() % (num - 2) + 1;
			y = num - x;
			break;
		case 1:
			operationA = '-';
			x = std::rand() % num + num + 1;
			y = x - num;
			break;
		case 2:
			operationA = '/';
			x = (std::rand() % (900 / num) + 1) * num;
			y = x / num;
			break;
		} // switch
		_quizData.question = L"Порахуйте SQRT(" + std::to_wstring(x) + operationA + std::to_wstring(y) + L") = ?";
		break;
	case 1:
		num = 0;
		// A
		switch (std::rand() % 3)
		{
		default:
			operationA = '+';
			x = std::rand() % 45 + 5;
			y = std::rand() % 45 + 5;
			num = x + y;
			break;
		case 1:
			operationA = '-';
			x = std::rand() % 45 + 5;
			y = std::rand() % 45 + 5;
			num = x - y;
			break;
		case 2:
			operationA = 'x';
			x = std::rand() % 45 + 5;
			y = std::rand() % 8 + 2;
			num = x * y;
			break;
		} // switch

		// B
		switch (std::rand() % 3)
		{
		default:
			operationB = '+';
			z = std::rand() % 45 + 5;
			result = num + z;
			break;
		case 1:
			operationB = '-';
			z = std::rand() % 45 + 5;
			result = num - z;
			break;
		case 2:
			operationB = 'x';
			z = std::rand() % 8 + 2;
			if (operationA == 'x')
				result = x * y * z;
			else result = x + y * z;
			break;
		} // switch
		_quizData.question = L"Порахуйте " + std::to_wstring(x) + operationA + std::to_wstring(y) + operationB + std::to_wstring(z) + L" = ?";
		break;
	} // switch

	if (_easyCount + 3 < 8)
		_quizData.duration = 8 - _mediumCount;
	else _quizData.duration = 3;
	_quizData.waitDuration = 1;

	_quizData.pushAnswer(std::to_wstring(result), true);
	_quizData.pushAnswer(std::to_wstring(result + std::rand() % 10 + 2), false);
	_quizData.pushAnswer(std::to_wstring(result + std::rand() % 30 + 15), false);

	return *this;
} // generate easy

HighMath& HighMath::generateHard()
{
	int x;
	int y;
	int z;
	int num;
	wchar_t operationA, operationB;
	int result;
	
	switch (std::rand() % 3)
	{
	default:
		switch (std::rand() % 4)
		{
		default:
			operationA = '+';
			x = std::rand() % 450 + 50;
			y = std::rand() % 450 + 50;
			result = x + y;
			break;
		case 1:
			operationA = '-';
			x = std::rand() % 450 + 50;
			y = std::rand() % 450 + 50;
			result = x - y;
			break;
		case 2:
			operationA = 'x';
			x = std::rand() % 400 + 5;
			y = std::rand() % (1000 / x) + 2;
			result = x * y;
			break;
		case 3:
			operationA = '/';
			result = std::rand() % 480 + 20;
			y = std::rand() % (1000 / result - 10) + 20;
			x = result * y;
			break;
		} // operations
		_quizData.question = L"Порахуйте " + std::to_wstring(x) + operationA + std::to_wstring(y) + L" = ?";
		break;
	case 1:
		result = std::rand() % 30 + 2;
		num = result * result;
		switch (std::rand() % 2)
		{
		default:
			operationA = '+';
			x = std::rand() % (num - 2) + 1;
			y = num - x;
			break;
		case 1:
			operationA = '-';
			x = std::rand() % num + num + 1;
			y = x - num;
			break;
		} // switch
		_quizData.question = L"Порахуйте SQRT(" + std::to_wstring(x) + operationA + std::to_wstring(y) + L") = ?";
		break;
	case 2:
		num = 0;
		// A
		switch (std::rand() % 3)
		{
		default:
			operationA = '+';
			x = std::rand() % 450 + 50;
			y = std::rand() % 450 + 50;
			num = x + y;
			break;
		case 1:
			operationA = '-';
			x = std::rand() % 450 + 50;
			y = std::rand() % 450 + 50;
			num = x - y;
			break;
		case 2:
			operationA = 'x';
			x = std::rand() % 400 + 5;
			y = std::rand() % (1000 / x) + 2;
			num = x * y;
			break;
		} // switch

		// B
		switch (std::rand() % 3)
		{
		default:
			operationB = '+';
			z = std::rand() % 450 + 50;
			result = num + z;
			break;
		case 1:
			operationB = '-';
			z = std::rand() % 450 + 50;
			result = num - z;
			break;
		case 2:
			operationB = 'x';
			z = std::rand() % 8 + 2;
			if (operationA == 'x')
				result = x * y * z;
			else result = x + y * z;
			break;
		} // switch
		_quizData.question = L"Порахуйте " + std::to_wstring(x) + operationA + std::to_wstring(y) + operationB + std::to_wstring(z) + L" = ?";
		break;
	} // switch

	if (_hardCount + 3 < 8)
		_quizData.duration = 8 - _hardCount;
	else _quizData.duration = 3;
	_quizData.waitDuration = 1;

	_quizData.pushAnswer(std::to_wstring(result), true);
	_quizData.pushAnswer(std::to_wstring(result + std::rand() % 10 + 2), false);
	_quizData.pushAnswer(std::to_wstring(result + std::rand() % 30 + 15), false);

	return *this;
} // generate easy
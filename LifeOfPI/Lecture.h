#pragma once

#include <cwchar>
#include <string>
#include <vector>
#include <fstream>

#include "State.h"
#include "Lecturer.h"
#include "Quiz.h"
#include "Text.h"

class Lecture : public State
{
protected:

	sf::SoundBuffer _correctAnswerBuffer;
	sf::SoundBuffer _incorrectAnswerBuffer;
	sf::SoundBuffer _tictacBuffer;

	SpriteSheet _backgroundSheet;
	SpriteSheet _foregroundSheet;
	SpriteSheet _lecturerSheet;
	SpriteSheet _quizSheet;

	// Objects
	GameObject *_background;
	GameObject *_foreground;

	Quiz *_quiz;
	QuizQuestionData _quizData;

	std::vector <sf::String> _speakings;
	std::vector <sf::String> _correctAnswers;
	std::vector <sf::String> _incorrectAnswers;
	std::vector <sf::String> _timelimitExceeded;

	sf::Music _backgroundMusic;

	// Quizing
	int _easyCount;
	int _mediumCount;
	int _hardCount;
	int _insaneCount;
	int _currentQuiz;
	int _quizCount;

	int _minWait;
	int _maxWait;
	float _wait;
	virtual Lecture& startWait();

	virtual Lecture& initialize();
	virtual Lecture& loadContent();
	virtual Lecture& unloadContent();

	virtual Lecture& loadSpeakings() = 0;
	virtual Lecture& loadCorrectAnswers() = 0;
	virtual Lecture& loadIncorrectAnswers() = 0;
	virtual Lecture& loadTimelimitExceeded() = 0;

	virtual Lecture& generateQuiz() = 0;
	virtual Lecture& generateEasy() = 0;
	virtual Lecture& generateMedium() = 0;
	virtual Lecture& generateHard() = 0;
	virtual Lecture& generateInsane() = 0;

	enum eLectureState
	{
		None = 0,
		Question = 1
	};
	eLectureState _lectureState;

public:

	Lecture(GameHelper &gameHelper);
	virtual ~Lecture();

};
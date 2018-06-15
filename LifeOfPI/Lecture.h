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
	sf::SoundBuffer _ringBuffer;

	SpriteSheet _backgroundSheet;
	SpriteSheet _foregroundSheet;
	SpriteSheet _lecturerSheet;
	SpriteSheet _quizSheet;

	// Objects
	GameObject *_background;
	GameObject *_foreground;

	Quiz *_quiz;
	QuizQuestionData _quizData;
	Lecturer *_lecturer;
	Text _timer;

	std::vector <sf::String> _speakings;
	std::vector <sf::String> _correctAnswers;
	std::vector <sf::String> _incorrectAnswers;
	std::vector <sf::String> _timelimitExceeded;
	std::vector <sf::String> _finalWords;

	sf::Music _backgroundMusic;
	sf::Sound _ringSound;

	// Quizing
	enum eQuizType
	{
		Easy = 0,
		Medium = 1,
		Hard = 2
	};
	eQuizType _quizType;

	float _lectureTime;
	float _timePassed;

	int _easyCount;
	int _easyCorrect;
	float _easyMarkPercentage; // how much of mark is for this type of questions

	int _mediumCount;
	int _mediumCorrect;
	float _mediumMarkPercentage; // how much of mark is for this type of questions

	int _hardCount;
	int _hardCorrect;
	float _hardMarkPercentage; // how much of mark is for this type of questions

	float _wait;
	bool _endLecture;

	virtual Lecture& initialize();
	virtual Lecture& loadContent();
	virtual Lecture& unloadContent();

	virtual Lecture& loadSpeakings() = 0;
	virtual Lecture& loadCorrectAnswers() = 0;
	virtual Lecture& loadIncorrectAnswers() = 0;
	virtual Lecture& loadTimelimitExceeded() = 0;
	virtual Lecture& loadFinalWords() = 0;

	virtual Lecture& generateWait();
	virtual Lecture& generateQuiz();
	virtual Lecture& generateEasy() = 0;
	virtual Lecture& generateMedium() = 0;
	virtual Lecture& generateHard() = 0;
	virtual double generateTotal();

	enum eLectureState
	{
		None = 0,
		Question = 1
	};
	eLectureState _lectureState;

public:

	Lecture(GameHelper &gameHelper);
	virtual ~Lecture();

	virtual Lecture& input();

	virtual Lecture& update(float dt);

	virtual Lecture& render();
};
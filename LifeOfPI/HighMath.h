#pragma once

#include "Lecture.h"
#include "Litvinog.h"

class HighMath : public Lecture
{
protected:

	Litvinog *_litvinog;
	Text text;

	sf::SoundBuffer _handwriteBuffer;
	sf::Sound _handwrite;

	virtual HighMath& initialize();
	virtual HighMath& loadContent();
	virtual HighMath& unloadContent();

	virtual HighMath& loadSpeakings();
	virtual HighMath& loadCorrectAnswers();
	virtual HighMath& loadIncorrectAnswers();
	virtual HighMath& loadTimelimitExceeded();

	virtual HighMath& generateQuiz();
	virtual HighMath& generateEasy();
	virtual HighMath& generateMedium();
	virtual HighMath& generateHard();
	virtual HighMath& generateInsane();
	virtual HighMath& startWait();

public:

	HighMath(GameHelper &gameHelper);
	virtual ~HighMath();

	virtual State& input();

	virtual HighMath& update(float dt);

	virtual HighMath& render();
};
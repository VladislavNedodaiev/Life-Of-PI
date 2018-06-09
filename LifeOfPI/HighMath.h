#pragma once

#include "Lecture.h"
#include "Litvinog.h"

class HighMath : public Lecture
{
protected:

	sf::SoundBuffer _handwriteBuffer;
	sf::Sound _handwrite;

	virtual HighMath& initialize();
	virtual HighMath& loadContent();
	virtual HighMath& unloadContent();

	virtual HighMath& loadSpeakings();
	virtual HighMath& loadCorrectAnswers();
	virtual HighMath& loadIncorrectAnswers();
	virtual HighMath& loadTimelimitExceeded();
	virtual HighMath& loadFinalWords();

	virtual HighMath& generateEasy();
	virtual HighMath& generateMedium();
	virtual HighMath& generateHard();

public:

	HighMath(GameHelper &gameHelper);
	virtual ~HighMath();
};
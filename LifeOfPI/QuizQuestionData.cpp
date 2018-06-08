#include "QuizQuestionData.h"

QuizAnswerData::QuizAnswerData()
{
	this->clear();
} // constructor

QuizAnswerData& QuizAnswerData::clear()
{
	isCorrect = false;
	answer = L"";

	return *this;
} // clear

QuizQuestionData::QuizQuestionData()
{
	clear();
} // default constructor

QuizQuestionData& QuizQuestionData::clear()
{
	duration = 10;
	waitDuration = 3;

	question = L"";
	reactionOnCorrect = L"";
	reactionOnIncorrect = L"";
	reactionOnTimelimit = L"";

	for (int i = 0; i < 3; i++)
		answers[i].clear();

	return *this;
} // clear 

QuizQuestionData& QuizQuestionData::pushAnswer(sf::String answer, bool isCorrect)
{
	if (hasFreeSpace())
	{
		int pos = std::rand() % 3;
		while (answers[pos].answer != L"")
			pos = std::rand() % 3;

		answers[pos].answer = answer;
		answers[pos].isCorrect = isCorrect;
	} // if

	return *this;
} // push answer

bool QuizQuestionData::hasFreeSpace()
{
	for (int i = 0; i < 3; i++)
	{
		if (answers[i].answer == L"")
			return true;
	} // for

	return false;
} // check
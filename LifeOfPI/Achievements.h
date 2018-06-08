#pragma once

#include <string>
#include <bitset>
#include <fstream>

struct Achievements
{
protected:

	bool *_achievements;

	int _unlocked;

public:
	enum eAchievementType
	{
		Survive = 0,
		MeetLitvinog = 1,
		Earn75 = 2,
		Unlock3Achievements = 3,
		PressNext = 4,
		PressHome = 5,
		MeetMrBond = 6,
		Earn100 = 7
	};
	static const int count = 8;

	Achievements();
	~Achievements();

	virtual Achievements& loadFromFile();
	virtual Achievements& saveToFile();

	virtual bool getAchievementState(eAchievementType type);
	virtual Achievements& unlockAchievement(eAchievementType type);

};
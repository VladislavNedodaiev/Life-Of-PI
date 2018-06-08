#include "Achievements.h"

Achievements::Achievements()
{
	_achievements = new bool[count];
	for (int i = 0; i < count; i++)
		_achievements[i] = false;

	loadFromFile();

	// counting unlocked achievements to give another achievements (yay)
	for (int i = 0; i < count; i++)
	{
		if (_achievements[i])
			_unlocked++;
	} // for
	
	if (_unlocked >= 3)
		_achievements[eAchievementType::Unlock3Achievements] = true;
} // constructor

Achievements::~Achievements()
{
	saveToFile();
	delete [] _achievements;
} // destructor

Achievements& Achievements::loadFromFile()
{
	std::string data;
	std::ifstream ifs("Achievements.dat");
	if (ifs.is_open() && !ifs.eof())
		ifs >> data;
	ifs.close();

	for (int i = 0; i < data.length() && i < count; i++)
		_achievements[i] = data[i] - 48;

	return *this;
} // load from file

Achievements& Achievements::saveToFile()
{
	std::string data = "";
	for (int i = 0; i < count; i++)
		data += (char)_achievements[i] + 48;

	std::ofstream ofs("Achievements.dat");
	if (ofs.is_open())
		ofs << data;
	ofs.close();

	return *this;
} // save to file

bool Achievements::getAchievementState(eAchievementType type)
{
	return _achievements[(int)type];
} // get state

Achievements& Achievements::unlockAchievement(eAchievementType type)
{
	if (!_achievements[(int)type])
	{
		_achievements[(int)type] = true;
		_unlocked++;
		if (_unlocked >= 3)
			_achievements[eAchievementType::Unlock3Achievements] = true;
	} // if

	return *this;
} // set state
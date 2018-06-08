#include "BasicSettings.h"

BasicSettings::BasicSettings()
{

	this->fullscreen = true;
	this->music = true;
	this->sounds = true;

	loadFromFile();

} // Settings constructor

BasicSettings::~BasicSettings()
{
	saveToFile();
} // destructor

sf::VideoMode BasicSettings::getVideoMode()
{
	if (fullscreen)
		return sf::VideoMode::getFullscreenModes()[0];

	return sf::VideoMode::getDesktopMode();
} // get videomode

sf::String BasicSettings::getWindowName()
{
	return sf::String("Life of PI");
} // get window name

sf::ContextSettings BasicSettings::getContextSettings()
{
	return sf::ContextSettings();
} // get window context settings

sf::Uint32 BasicSettings::getWindowStyle()
{
	if (fullscreen)
		return sf::Style::Fullscreen;

	return sf::Style::Default;
} // get window style

BasicSettings& BasicSettings::loadFromFile()
{
	std::string data;
	std::ifstream ifs("Settings.dat");
	if (ifs.is_open() && !ifs.eof())
		ifs >> data;
	ifs.close();

	if (data.length() >= 3)
	{
		fullscreen = data[0] - 48;
		music = data[1] - 48;
		sounds = data[2] - 48;
	} // if

	return *this;
} // load from file

BasicSettings& BasicSettings::saveToFile()
{
	std::string data = "";
	data += (char)fullscreen + 48;
	data += (char)music + 48;
	data += (char)sounds + 48;

	std::ofstream ofs("Settings.dat");
	if (ofs.is_open())
		ofs << data;
	ofs.close();

	return *this;
} // save to file
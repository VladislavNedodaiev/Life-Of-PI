#pragma once

#include <string>
#include <bitset>
#include <fstream>
#include <SFML\Graphics.hpp>

struct BasicSettings
{
	static const int VIEW_SIZEX = 192;
	static const int VIEW_SIZEY = 108;

	static const int WINDOW_SIZEX = 1920;
	static const int WINDOW_SIZEY = 1080;

	bool fullscreen;
	bool music;
	bool sounds;

	BasicSettings();
	~BasicSettings();

	sf::VideoMode getVideoMode();
	sf::String getWindowName();
	sf::ContextSettings getContextSettings();
	sf::Uint32 getWindowStyle();

	BasicSettings& loadFromFile();
	BasicSettings& saveToFile();
};
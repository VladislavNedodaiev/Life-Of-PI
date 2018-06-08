#pragma once

#include "Phone.h"
#include "Toggle.h"
#include "Achievement.h"

class MainMenuPhone : public Phone
{
protected:

	// home
	Button _playButton;
	Button _settingsButton;
	Button _achievementsButton;
	Button _exitButton;
	Button _backButton;

	// settings
	Toggle _fullscreenToggle;
	Toggle _musicToggle;
	Toggle _soundsToggle;

	// achievements
	Achievements *_achievementsData;
	Button _achievementsPrevButton;
	Button _achievementsNextButton;
	GameObject _achievementsPage;
	std::vector <Achievement*> _achievements;

public:

	enum ePhoneState
	{
		TurnedOffState = 0,
		HomeState = 10,
		SettingsState = 20,
		AchievementsState = 30
	};

	enum eInputType
	{
		None = 0,
		HomeButton = 10,
		PlayButton = 20,
		SettingsButton = 30,
		SettingsFullscreenToggle = 31,
		SettingsMusicToggle = 32,
		SettingsSoundsToggle = 33,
		AchievementsButton = 40,
		AchievementsPrevButton = 41,
		AchievementsNextButton = 42,
		ExitButton = 50,
		BackButton = 60
	};

	MainMenuPhone(sf::Image &spriteSheet,
				  sf::SoundBuffer &homeButtonClickSB,
				  sf::SoundBuffer &tapSB,
				  BasicSettings &settings,
				  Achievements &achievements);
	virtual ~MainMenuPhone();

	virtual MainMenuPhone& setPosition(const sf::Vector2f &position);
	virtual MainMenuPhone& setPosition(float x, float y);

	virtual MainMenuPhone& move(const sf::Vector2f &offset);
	virtual MainMenuPhone& move(float offsetX, float offsetY);

	virtual int input(sf::Event &event, sf::Vector2i mousePos);

	virtual MainMenuPhone& update(float dt);
	virtual MainMenuPhone& render(sf::RenderTarget &target);

protected:

	virtual eInputType handleInputHome(sf::Event &event, sf::Vector2i mousePos);
	virtual eInputType handleInputSettings(sf::Event &event, sf::Vector2i mousePos);
	virtual eInputType handleInputAchievements(sf::Event &event, sf::Vector2i mousePos);
	virtual void openSettings();
	virtual void openAchievements();

	virtual MainMenuPhone& renderHome(sf::RenderTarget &target);
	virtual MainMenuPhone& renderSettings(sf::RenderTarget &target);
	virtual MainMenuPhone& renderAchievements(sf::RenderTarget &target);
};

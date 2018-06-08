#include "MainMenuPhone.h"

MainMenuPhone::MainMenuPhone(sf::Image &spriteSheet,
							 sf::SoundBuffer &homeButtonClickSB,
							 sf::SoundBuffer &tapSB,
							 BasicSettings &settings,
							 Achievements &achievements) :
								Phone(spriteSheet,
									  homeButtonClickSB,
									  tapSB,
									  settings),
								_playButton(spriteSheet,
									sf::IntRect(70, 0, 45, 19)),
								_settingsButton(spriteSheet,
									sf::IntRect(70, 19, 45, 19)),
								_achievementsButton(spriteSheet,
									sf::IntRect(70, 38, 45, 19)),
								_exitButton(spriteSheet,
									sf::IntRect(70, 57, 45, 19)),
								_backButton(spriteSheet,
									sf::IntRect(70, 76, 45, 7)),
								_fullscreenToggle(spriteSheet,
									sf::IntRect(160, 0, 45, 12),
									sf::IntRect(160, 12, 45, 12)),
								_musicToggle(spriteSheet,
									sf::IntRect(160, 24, 45, 12),
									sf::IntRect(160, 36, 45, 12)),
								_soundsToggle(spriteSheet,
									sf::IntRect(160, 48, 45, 12),
									sf::IntRect(160, 60, 45, 12)),
								_achievementsPrevButton(spriteSheet,
									sf::IntRect(70, 83, 17, 10)),
								_achievementsNextButton(spriteSheet,
									sf::IntRect(104, 83, 17, 10)),
								_achievementsPage(spriteSheet, 9, 0, sf::IntRect(70, 93, 11, 10))
{	
	// home
	_playButton.setPosition(9, 17);
	_settingsButton.setPosition(9, 36);
	_achievementsButton.setPosition(9, 55);
	_exitButton.setPosition(9, 74);
	_backButton.setPosition(9, 17);

	// settings
	_fullscreenToggle.setPosition(9, 24);
	_fullscreenToggle.setToggle(_settings->fullscreen);

	_musicToggle.setPosition(9, 36);
	_musicToggle.setToggle(_settings->music);

	_soundsToggle.setPosition(9, 48);
	_soundsToggle.setToggle(_settings->sounds);

	// achievements
	_achievementsData = &achievements;
	_achievementsPrevButton.setPosition(9, 84);
	_achievementsNextButton.setPosition(37, 84);
	_achievementsPage.setPosition(26, 84);
	_achievements.push_back(new Achievement(spriteSheet, sf::IntRect(250, 0, 45, 13), achievements.Survive, achievements));
	_achievements.push_back(new Achievement(spriteSheet, sf::IntRect(250, 13, 45, 17), achievements.MeetLitvinog, achievements));
	_achievements.push_back(new Achievement(spriteSheet, sf::IntRect(250, 30, 45, 13), achievements.Earn75, achievements));
	_achievements.push_back(new Achievement(spriteSheet, sf::IntRect(250, 43, 45, 17), achievements.Unlock3Achievements, achievements));
	_achievements.push_back(new Achievement(spriteSheet, sf::IntRect(250, 60, 45, 13), achievements.PressNext, achievements));
	_achievements.push_back(new Achievement(spriteSheet, sf::IntRect(250, 73, 45, 13), achievements.PressHome, achievements));
	_achievements.push_back(new Achievement(spriteSheet, sf::IntRect(250, 86, 45, 17), achievements.MeetMrBond, achievements));
	_achievements.push_back(new Achievement(spriteSheet, sf::IntRect(250, 103, 45, 17), achievements.Earn100, achievements));

	int firsty = 24,
		iy = 24;
	for (int i = 0; i < _achievements.size(); i++)
	{
		if (iy + _achievements[i]->getSize().y > 84)
			iy = firsty;
		_achievements[i]->setPosition(9, iy);
		iy += _achievements[i]->getSize().y;
	} // for (positioning)

} // Phone constructor

MainMenuPhone::~MainMenuPhone() {} // destructor

MainMenuPhone& MainMenuPhone::setPosition(const sf::Vector2f &position)
{

	sf::Vector2f deltaPos = position - this->getPosition();

	Phone::setPosition(position);

	// home
	_playButton.setPosition(_playButton.getPosition() + deltaPos);
	_settingsButton.setPosition(_settingsButton.getPosition() + deltaPos);
	_achievementsButton.setPosition(_achievementsButton.getPosition() + deltaPos);
	_exitButton.setPosition(_exitButton.getPosition() + deltaPos);
	_backButton.setPosition(_backButton.getPosition() + deltaPos);

	// settings
	_fullscreenToggle.setPosition(_fullscreenToggle.getPosition() + deltaPos);
	_musicToggle.setPosition(_musicToggle.getPosition() + deltaPos);
	_soundsToggle.setPosition(_soundsToggle.getPosition() + deltaPos);

	// achievements
	_achievementsPrevButton.setPosition(_achievementsPrevButton.getPosition() + deltaPos);
	_achievementsNextButton.setPosition(_achievementsNextButton.getPosition() + deltaPos);
	_achievementsPage.setPosition(_achievementsPage.getPosition() + deltaPos);
	for (int i = 0; i < _achievements.size(); i++)
		_achievements[i]->setPosition(_achievements[i]->getPosition() + deltaPos);

	return *this;
} // setPosition overload, which is needed to change pos of every child element

MainMenuPhone& MainMenuPhone::setPosition(float x, float y)
{
	return this->setPosition(sf::Vector2f(x, y));
} // setPosition overload, which is needed to change pos of every child element

MainMenuPhone& MainMenuPhone::move(const sf::Vector2f &offset)
{
	Phone::move(offset);
	if (isMovable)
	{
		// home
		_playButton.move(offset);
		_settingsButton.move(offset);
		_achievementsButton.move(offset);
		_exitButton.move(offset);
		_backButton.move(offset);

		// settings
		_fullscreenToggle.move(offset);
		_musicToggle.move(offset);
		_soundsToggle.move(offset);

		// achievements
		_achievementsPrevButton.move(offset);
		_achievementsNextButton.move(offset);
		_achievementsPage.move(offset);
		for (int i = 0; i < _achievements.size(); i++)
			_achievements[i]->move(offset);
	} // if

	return *this;
} // recshape move overload #1

MainMenuPhone& MainMenuPhone::move(float offsetX, float offsetY)
{
	return this->move(sf::Vector2f(offsetX, offsetY));
} // recshape move overload #2

int MainMenuPhone::input(sf::Event &event, sf::Vector2i mousePos)
{
	int reaction = Phone::input(event, mousePos);
	if (reaction == eInputType::HomeButton)
	{
		_achievementsData->unlockAchievement(_achievementsData->PressHome);
		_achievements[_achievementsData->PressHome]->updateState();
		_achievements[_achievementsData->Unlock3Achievements]->updateState();

		if (_ePhoneState != ePhoneState::HomeState)
		{
			_display.setFrame(1);
			_ePhoneState = ePhoneState::HomeState;
		}
		else
		{
			_display.setFrame(0);
			_ePhoneState = ePhoneState::TurnedOffState;
		} // else
	} // if home button is pressed
	else if (_ePhoneState == ePhoneState::HomeState)
		reaction = handleInputHome(event, mousePos);
	else if (_ePhoneState == ePhoneState::SettingsState)
		reaction = handleInputSettings(event, mousePos);
	else if (_ePhoneState == ePhoneState::AchievementsState)
		reaction = handleInputAchievements(event, mousePos);

	return reaction;
} // reading input

MainMenuPhone::eInputType MainMenuPhone::handleInputHome(sf::Event &event, sf::Vector2i mousePos)
{
	if (_playButton.isPressed(event, mousePos))
	{
		if (_settings->sounds)
			_tapSound.play();
		return eInputType::PlayButton;
	} // if
	else if (_settingsButton.isPressed(event, mousePos))
	{
		openSettings();

		if (_settings->sounds)
			_tapSound.play();

		return eInputType::SettingsButton;
	} // else if
	else if (_achievementsButton.isPressed(event, mousePos))
	{
		openAchievements();

		if (_settings->sounds)
			_tapSound.play();

		return eInputType::AchievementsButton;
	} // else if
	else if (_exitButton.isPressed(event, mousePos))
	{
		if (_settings->sounds)
			_tapSound.play();

		return eInputType::ExitButton;
	} // else if

	return eInputType::None;
} // handleInputHome

MainMenuPhone::eInputType MainMenuPhone::handleInputSettings(sf::Event &event, sf::Vector2i mousePos)
{
	if (_backButton.isPressed(event, mousePos))
	{
		_display.setFrame(1);
		_ePhoneState = ePhoneState::HomeState;

		if (_settings->sounds)
			_tapSound.play();

		return eInputType::BackButton;
	} // if
	else if (_fullscreenToggle.isPressed(event, mousePos))
	{
		if (_fullscreenToggle.getToggle())
			_settings->fullscreen = true;
		else
			_settings->fullscreen = false;

		if (_settings->sounds)
			_tapSound.play();

		return eInputType::SettingsFullscreenToggle;
	} // else if
	else if (_musicToggle.isPressed(event, mousePos))
	{
		if (_musicToggle.getToggle())
			_settings->music = true;
		else
			_settings->music = false;

		if (_settings->sounds)
			_tapSound.play();

		return eInputType::SettingsMusicToggle;
	} // else if
	else if (_soundsToggle.isPressed(event, mousePos))
	{
		if (_soundsToggle.getToggle())
			_settings->sounds = true;
		else
			_settings->sounds = false;

		if (_settings->sounds)
			_tapSound.play();

		return eInputType::SettingsSoundsToggle;
	} // else if

	return eInputType::None;
} // handleInputSettings

MainMenuPhone::eInputType MainMenuPhone::handleInputAchievements(sf::Event &event, sf::Vector2i mousePos)
{
	if (_backButton.isPressed(event, mousePos))
	{
		_display.setFrame(1);
		_ePhoneState = ePhoneState::HomeState;

		if (_settings->sounds)
			_tapSound.play();

		return eInputType::BackButton;
	} // if
	else if (_achievementsPrevButton.isPressed(event, mousePos))
	{
		if (!_achievementsPage.getAnimation()->getFrame())
			_achievementsPage.setFrame(_achievements.size() / 4 - 1);
		else 
			_achievementsPage.setFrame(_achievementsPage.getAnimation()->getFrame() - 1);

		_achievementsPage.getAnimation()->updateTexture();

		if (_settings->sounds)
			_tapSound.play();

		return eInputType::AchievementsPrevButton;
	} // else if
	else if (_achievementsNextButton.isPressed(event, mousePos))
	{
		_achievementsPage.setFrame((_achievementsPage.getAnimation()->getFrame() + 1) % (_achievements.size() / 4));
		_achievementsPage.getAnimation()->updateTexture();

		_achievementsData->unlockAchievement(_achievementsData->PressNext);
		_achievements[_achievementsData->PressNext]->updateState();
		_achievements[_achievementsData->Unlock3Achievements]->updateState();

		if (_settings->sounds)
			_tapSound.play();

		return eInputType::AchievementsNextButton;
	} // else if

	return eInputType::None;
} // handleInputAchievements

void MainMenuPhone::openSettings()
{
	_display.setFrame(2);
	_ePhoneState = ePhoneState::SettingsState;
} // open settings

void MainMenuPhone::openAchievements()
{
	for (int i = 0; i < _achievements.size(); i++)
		_achievements[i]->updateState();

	_achievementsPage.setFrame(0);
	_achievementsPage.getAnimation()->updateTexture();

	_display.setFrame(2);
	_ePhoneState = ePhoneState::AchievementsState;
} // open achievements

MainMenuPhone& MainMenuPhone::update(float dt)
{
	Phone::update(dt);

	return *this;
} // update

MainMenuPhone& MainMenuPhone::render(sf::RenderTarget &target)
{
	Phone::render(target);
	if (isVisible)
	{
		switch (_ePhoneState)
		{
		default:
			break;
		case ePhoneState::HomeState:
			renderHome(target);
			break;
		case ePhoneState::SettingsState:
			renderSettings(target);
			_backButton.render(target);
			break;
		case ePhoneState::AchievementsState:
			renderAchievements(target);
			_backButton.render(target);
			break;
		} // switch
		if (_ePhoneState != ePhoneState::TurnedOffState)
			_topPanel.render(target);
	} // if

	return *this;
} // render

MainMenuPhone& MainMenuPhone::renderHome(sf::RenderTarget &target)
{
	_playButton.render(target);
	_settingsButton.render(target);
	_achievementsButton.render(target);
	_exitButton.render(target);

	return *this;
} // 

MainMenuPhone& MainMenuPhone::renderSettings(sf::RenderTarget &target)
{
	_fullscreenToggle.render(target);
	_musicToggle.render(target);
	_soundsToggle.render(target);

	return *this;
} // 

MainMenuPhone& MainMenuPhone::renderAchievements(sf::RenderTarget &target)
{
	int achieve = _achievementsPage.getAnimation()->getFrame() * 4;
	for (int i = achieve; i < _achievements.size() && i < achieve + 4; i++)
		_achievements[i]->render(target);

	_achievementsPrevButton.render(target);
	_achievementsNextButton.render(target);
	_achievementsPage.render(target);

	return *this;
} // 
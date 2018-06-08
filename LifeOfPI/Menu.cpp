#include "Menu.h"

Menu::Menu(GameHelper &gameHelper) : State(gameHelper)
{
	loadContent().initialize();
} // constructor

Menu::~Menu()
{
	unloadContent();
} // destructor

Menu& Menu::initialize()
{
	//_stateFader = new StateFader(_stateFaderSheet.getSheet());
	//_stateFader->start(6);

	_background = new GameObject(_backgroundSheet.getSheet());

	_pressSpace = new GameObject(_pressSpaceSheet.getSheet());
	_pressSpace->setPosition(_gameHelper->settings.VIEW_SIZEX / 2 - _pressSpace->getGlobalBounds().width / 2, 18);
	_pressSpace->createBlinker(2).setLooping(true).setPlaying(true);

	_phone = new MainMenuPhone(_phoneSpriteSheet.getSheet(),
							   _homeButtonClickSB,
							   _tapSB,
							   _gameHelper->settings,
							   _gameHelper->achievements);
	_phone->setPosition(_gameHelper->settings.VIEW_SIZEX / 2 - _phone->getSize().x / 2, 0);

	_backgroundMusic.setVolume(100 * _gameHelper->settings.music);
	_backgroundMusic.play();

	return *this;
} // initializing 

Menu& Menu::loadContent()
{
	_stateFaderSheet.load("Data/FaderSheet.png");

	_backgroundSheet.load("Data/MainMenu/NURE.png");
	_pressSpaceSheet.load("Data/MainMenu/PressSpace.png");
	_phoneSpriteSheet.load("Data/Phone/PhoneSheet.png");

	_backgroundMusic.openFromFile("Data/MainMenu/TownSounds.ogg");
	_pressSpaceSound.loadFromFile("Data/MainMenu/PressSpace.wav");
	_homeButtonClickSB.loadFromFile("Data/Phone/HomeClick.wav");
	_tapSB.loadFromFile("Data/Phone/Tap.wav");

	return *this;
} // loading content

Menu& Menu::unloadContent()
{
	//delete _stateFader;
	delete _background;
	delete _pressSpace;
	delete _phone;
	_backgroundMusic.stop();

	return *this;
} // unloading content

State& Menu::input()
{
	sf::Vector2i mousePos = sf::Vector2i(_gameHelper->renderWindow.mapPixelToCoords(sf::Mouse::getPosition(_gameHelper->renderWindow)));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) 
	 && _pressSpace != nullptr)
	{
		_pressSpace->isVisible = false;
		delete _pressSpace;
		_pressSpace = nullptr;
		_menuSound.setBuffer(_pressSpaceSound);
		if (_gameHelper->settings.sounds)
			_menuSound.play();
	} // if
	else if (_pressSpace == nullptr)
	{
		int iInput = _phone->input(_gameHelper->event, mousePos);
		if (iInput == MainMenuPhone::eInputType::ExitButton)
			this->toDelete = true;
		else if (iInput == MainMenuPhone::eInputType::SettingsFullscreenToggle)
			_gameHelper->resetWindow();
		else if (iInput == MainMenuPhone::eInputType::SettingsMusicToggle)
			_backgroundMusic.setVolume(100 * _gameHelper->settings.music);
		else if (iInput == MainMenuPhone::eInputType::PlayButton)
		{
			_backgroundMusic.pause();
			return *(new HighMath(*_gameHelper));
		}
	} // else if

	return *this;
} // inputing

Menu& Menu::update(float dt)
{
	//_stateFader->update(dt);
	if (_backgroundMusic.getStatus() == _backgroundMusic.Paused)
		_backgroundMusic.play();
	_background->update(dt);
	if (_pressSpace != nullptr) 
		_pressSpace->update(dt);

	return *this;
} // updating 

Menu& Menu::render()
{
	_background->render(_gameHelper->renderWindow);
	if (_pressSpace != nullptr)
		_pressSpace->render(_gameHelper->renderWindow);
	else
		_phone->render(_gameHelper->renderWindow);

	//_stateFader->render(_gameHelper->renderWindow);

	return *this;
} // rendering
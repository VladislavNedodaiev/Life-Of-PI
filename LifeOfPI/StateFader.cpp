#include "StateFader.h"

/*StateFader::StateFader(sf::Image &spriteSheet) : GameObject(spriteSheet, 12, 0, sf::IntRect(0, 0, 12, 12))
{
	this->setSize(sf::Vector2f(BasicSettings::VIEW_SIZEX, BasicSettings::VIEW_SIZEY));
	_texture.create(BasicSettings::VIEW_SIZEX, BasicSettings::VIEW_SIZEY);
	_texture.setRepeated(true);

	_currentAnimation->setLooping(false);
	_currentAnimation->setFrame(_currentAnimation->getFramesCount() - 1);
	_currentAnimation->updateTexture();

} // constructor

StateFader& StateFader::start(float fps)
{
	_currentAnimation->setDPS(fps);
	_currentAnimation->setPlaying(true);

	return *this;
} // start fading

bool StateFader::isFading()
{
	return _currentAnimation->getDPS();
} // start */
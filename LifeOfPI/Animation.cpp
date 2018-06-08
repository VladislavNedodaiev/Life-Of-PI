#include "Animation.h"

Animation::Animation(sf::IntRect firstFrame,
					 float fps,
					 sf::Image &sheet,
					 sf::Texture &texture)
{
	this->_dps = fps;
	this->_frame = 0;

	this->_sheet = &sheet;
	this->_texture = &texture;

	if (firstFrame.width > sheet.getSize().x
		|| firstFrame.height > sheet.getSize().y)
	{
		this->_framesCount = 0;
		return;
	}



	while (firstFrame.top < _sheet->getSize().y)
	{
		_frames.push_back(firstFrame);

		firstFrame.left += firstFrame.width;
		if (firstFrame.left >= sheet.getSize().x)
		{
			firstFrame.left = 0;
			firstFrame.top += firstFrame.height;
		} // if
	} // for

	this->_framesCount = this->_frames.size();
} // constructor (creates animation from firstframe to the end of the spritesheet)

Animation::Animation(sf::IntRect firstFrame,
					 int framesCount,
					 float fps,
					 sf::Image &sheet,
					 sf::Texture &texture)
{
	this->_framesCount = framesCount;
	this->_dps = fps;
	this->_frame = 0;

	this->_sheet = &sheet;
	this->_texture = &texture;

	if (firstFrame.width > sheet.getSize().x
		|| firstFrame.height > sheet.getSize().y)
	{
		this->_framesCount = 0;
		return;
	}

	for (int i = 0; i < framesCount; i++)
	{
		if (firstFrame.left + firstFrame.width > sheet.getSize().x)
		{
			firstFrame.left = 0;
			firstFrame.top += firstFrame.height;

			if (firstFrame.top + firstFrame.height > sheet.getSize().y)
				firstFrame.top = 0;
		} // if
		_frames.push_back(firstFrame);
		
		firstFrame.left += firstFrame.width;
	} // for

	this->_framesCount = this->_frames.size();
} // constructor

Animation::~Animation()
{
	this->_frames.clear();
} // ~Animation

Animation& Animation::setPlaying(bool playing)
{
	if (this->_framesCount != 0)
		this->_playing = playing;

	return *this;
} // start animation

Animation& Animation::setFrame(int frame)
{
	if (frame >= 0 && frame < this->_framesCount)
		this->_frame = frame;

	return *this;
} // setting current frame

int Animation::getFrame() const
{
	return _frame;
} // getting current frame

int Animation::getFramesCount() const
{
	return _framesCount;
} // getting frames count

Animation& Animation::update(float dt)
{
	if (!_playing)
		return *this;

	int frame = this->_frame;

	this->_frame += this->_dps * dt;

	if (this->_frame >= this->_framesCount)
	{
		if (!this->_looping)
		{
			this->_frame = 0;
			this->_playing = false;
		} // not looping
		else
		{
			this->_frame -= ((int)this->_frame / this->_framesCount) * this->_framesCount;
		} // looping
	} // if
	else if (this->_frame < 0)
	{
		if (!this->_looping)
		{
			this->_frame = this->_framesCount;
			this->_playing = false;
		} // not looping
		else
		{
			this->_frame += this->_framesCount + ((int)-this->_frame / this->_framesCount) * this->_framesCount;
		} // looping
	} // if

	if ((int)this->_frame != frame)
	{
		if (this->_frame == this->_framesCount)
			frame = this->_framesCount - 1;
		else frame = this->_frame;

		this->_texture->loadFromImage(*this->_sheet, this->_frames[frame]);
	} // if

	return *this;
} // updating

Animation& Animation::updateTexture()
{
	if (_frame >= 0 && _frame < this->_framesCount)
		this->_texture->loadFromImage(*this->_sheet, this->_frames[_frame]);

	return *this;
} // update texture only
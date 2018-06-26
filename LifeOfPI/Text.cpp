#include "Text.h"

Text::Text()
{
	_position = sf::Vector2f(0, 0);
	_size = sf::Vector2f(0, 0);
} // constructor

Text::~Text()
{
	_strings.clear();
} // destructor

Text& Text::setPosition(const sf::Vector2f &position)
{
	this->_position = position;
	_box.setPosition(sf::Vector2f(sf::Vector2i(position)));

	if (_textinfo.horizontalAlign == TextInfo::eHorizontalAlign::Middle)
		_box.move((int)(-_size.x / 2), 0);
	else if (_textinfo.horizontalAlign == TextInfo::eHorizontalAlign::Right)
		_box.move((int)(-_size.x), 0);
	if (_textinfo.verticalAlign == TextInfo::eVerticalAlign::Center)
		_box.move(0, (int)(-_size.y / 2));
	else if (_textinfo.verticalAlign == TextInfo::eVerticalAlign::Bottom)
		_box.move(0, (int)(-_size.y));

	return *this;
} // setting _position

Text& Text::setPosition(float x, float y)
{
	return setPosition(sf::Vector2f(x, y));
} // setting _position

Text& Text::move(const sf::Vector2f &offset)
{
	return setPosition(_position + offset);
} // moving

Text& Text::move(float offsetX, float offsetY)
{
	return move(sf::Vector2f(offsetX, offsetY));
} // moving

Text& Text::setTextInfo(TextInfo &textinfo)
{
	if (_textinfo.font == nullptr && textinfo.font == nullptr)
		return *this;
	_textinfo = textinfo;
	
	_text.setFont(*_textinfo.font);
	_text.setCharacterSize(_textinfo.characterSize);
	const_cast<sf::Texture&>(_text.getFont()->getTexture(_textinfo.characterSize)).setSmooth(false);
	_text.setFillColor(_textinfo.textColor);

	int maxWidth = 0;
	int height = 0;
	int size = _strings.size();
	for (int i = 0; i < size; i++)
	{
		_text.setString(_strings[i]);
		int width = _text.getGlobalBounds().width;
		if (width > maxWidth)
			maxWidth = width;
		height += _text.getGlobalBounds().height + _textinfo.lineSpacing;
	} // for

	if (_textinfo.font != nullptr)
	{
		_size = sf::Vector2f(sf::Vector2i(maxWidth + _textinfo.margin.x * 2, height + _textinfo.margin.y * 2));
		_box.setSize(_size);
		createTexture();
	} // if

	return *this;
} // setting textinfo

TextInfo Text::getTextInfo()
{
	return _textinfo;
} // getting textinfo

Text& Text::operator=(const sf::String &string)
{
	sf::Clock cl;
	sf::Time time;

	cl.restart();
	_strings.clear();

	int startPos = 0;
	int endPos = 0;

	int size = string.getSize();

	float maxWidth = 0;
	float height = 0;

	while (endPos < size)
	{
		if (string[endPos] == '\n')
		{
			_strings.push_back(string.substring(startPos, endPos - startPos));
			startPos = endPos + 1;

			if (_textinfo.font != nullptr)
			{
				_text.setString(_strings[_strings.size() - 1]);
				int width = _text.getGlobalBounds().width;
				if (width > maxWidth)
					maxWidth = width;
				height += _text.getGlobalBounds().height + _textinfo.lineSpacing;
			}
		} // if
		endPos++;
	} // while

	if (endPos != startPos)
	{
		_strings.push_back(string.substring(startPos, endPos - startPos));

		if (_textinfo.font != nullptr)
		{
			_text.setString(_strings[_strings.size() - 1]);
			int width = _text.getGlobalBounds().width;
			if (width > maxWidth)
				maxWidth = width;
			height += _text.getGlobalBounds().height + _textinfo.lineSpacing;
		}
	} // if
	time = cl.restart();

	std::cout << "\nText: " << string.getData();
	std::cout << "\nTime spent on prepare: " << time.asSeconds();

	if (_textinfo.font != nullptr)
	{
		_size = sf::Vector2f(sf::Vector2i(maxWidth + _textinfo.margin.x * 2, height + _textinfo.margin.y * 2));
		_box.setSize(_size);
		createTexture();
	} // if
	
	return *this;
} // setting string

Text& Text::render(sf::RenderTarget &target)
{
	target.draw(_box);

	return *this;
} // drawing text

Text& Text::createTexture()
{
	sf::Clock cl;
	sf::Time time;
	cl.restart();

	if (!_strings.size() || _textinfo.font == nullptr)
		return *this;

	this->setPosition(_position);

	// made for optimizing, cause sf::RenderTexture::create(...) requires lots of time
	sf::Vector2u rsize = _renderTexture.getSize();
	if (rsize.x < _size.x)
	{
		rsize.x = _size.x;
		if (rsize.y < _size.y)
			rsize.y = _size.y;
		_renderTexture.create(rsize.x, rsize.y);
	} // if (rsize.x < _size.x)
	else if (rsize.y < _size.y)
	{
		rsize.y = _size.y;
		if (rsize.x < _size.x)
			rsize.x = _size.x;
		_renderTexture.create(rsize.x, rsize.y);
	} // else if (rsize.y < _size.y)

	_renderTexture.clear(_textinfo.backgroundColor);

	_text.setString(_strings[0]);
	_text.setPosition(0, 0);
	_text.move(sf::Vector2f(sf::Vector2i(_textinfo.margin)));

	// horizontal align
	if (_textinfo.horizontalAlign == TextInfo::eHorizontalAlign::Middle)
		_text.setPosition(sf::Vector2f(sf::Vector2i(_size.x / 2 - _text.getGlobalBounds().width / 2, _text.getPosition().y + _textinfo.margin.y)));
	else if (_textinfo.horizontalAlign == TextInfo::eHorizontalAlign::Right)
		_text.setPosition(sf::Vector2f(sf::Vector2i(_size.x - _textinfo.margin.x - _text.getGlobalBounds().width, _text.getPosition().y + _textinfo.margin.y)));

	//_image.
	_renderTexture.draw(_text);

	int size = _strings.size();
	for (int i = 1; i < size; i++)
	{
		_text.move(0, _text.getGlobalBounds().height + _textinfo.lineSpacing);
		_text.setString(_strings[i]);

		if (_textinfo.horizontalAlign == TextInfo::eHorizontalAlign::Middle)
			_text.setPosition(sf::Vector2f(sf::Vector2i(_size.x / 2 - _text.getGlobalBounds().width / 2, _text.getPosition().y + _textinfo.margin.y)));
		else if (_textinfo.horizontalAlign == TextInfo::eHorizontalAlign::Right)
			_text.setPosition(sf::Vector2f(sf::Vector2i(_size.x - _textinfo.margin.x - _text.getGlobalBounds().width, _text.getPosition().y + _textinfo.margin.y)));

		_renderTexture.draw(_text);
	} // for

	_renderTexture.display();
	_box.setTexture(&_renderTexture.getTexture(), true);

	return *this;
} // creating texture
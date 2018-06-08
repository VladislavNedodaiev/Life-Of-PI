#include "TextInfo.h"

TextInfo::TextInfo()
{
	horizontalAlign = eHorizontalAlign::Left;
	verticalAlign = eVerticalAlign::Top;

	font = nullptr;
	characterSize = 12;
	lineSpacing = 1;
	margin.x = 1;
	margin.y = 1;
	textColor = sf::Color::Black;
	backgroundColor = sf::Color::Transparent;
} // constructor

TextInfo::TextInfo(const TextInfo &textinfo)
{
	*this = textinfo;
} // copy constructor

void TextInfo::operator=(const TextInfo &textinfo)
{
	horizontalAlign = textinfo.horizontalAlign;
	verticalAlign = textinfo.verticalAlign;

	if (textinfo.font != nullptr)
		font = textinfo.font;
	characterSize = textinfo.characterSize;
	lineSpacing = textinfo.lineSpacing;
	textColor = textinfo.textColor;
	backgroundColor = textinfo.backgroundColor;
} // operator = overloading
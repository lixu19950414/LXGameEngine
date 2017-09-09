#include "stdafx.h"
#include "Label.h"


Label::Label()
{
}


Label::~Label()
{
}

void Label::setContentSize(GLfloat width, GLfloat height)
{
	if (_contentSize.x != width || _contentSize.y != height)
	{
		_contentSize = glm::vec2(width, height);
		_vertsDirty = true;
		_aabbDirty = true;
	}
}

void Label::setAnchorPoint(GLfloat x, GLfloat y)
{
	if (_anchorPoint.x != x || _contentSize.y != y)
	{
		_anchorPoint = glm::vec2(x, y);
		_vertsDirty = true;
		_aabbDirty = true;
	}
}

void Label::setOpacity(GLubyte opacity)
{
	if (_opacity != opacity)
	{
		_opacity = opacity;
		_vertsDirty = true;
	}
}

void Label::setColor(GLubyte r, GLubyte g, GLubyte b)
{
	if (_color[0] != r || _color[1] != g || _color[2] != b) {
		_color[0] = r;
		_color[1] = g;
		_color[2] = b;
		_vertsDirty = true;
	}
}

void Label::setString(const std::string & s)
{
	if (_currentString != s) {
		_currentString = s;
		_vertsDirty = true;
	}
	
}

void Label::setFontSize(int fontSize)
{
	if (_fontSize != fontSize) {
		_fontSize = fontSize;
		_vertsDirty = true;
	}
}



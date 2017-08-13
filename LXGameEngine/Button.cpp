#include "stdafx.h"
#include "Button.h"
#include "math.h"


Button::Button():
	_callback(nullptr),
	_clickPos(0.0f, 0.0f)
{
}


Button::~Button()
{
}

bool Button::onTouchBegin(int x, int y)
{
	_clickPos = convertToNodeSpace(x, y);
	return true;
}

void Button::onTouchMove(int x, int y)
{
}

void Button::onTouchEnd(int x, int y)
{
	glm::vec2 endPos = convertToNodeSpace(x, y);
	if (_callback && abs(endPos.x - _clickPos.x) <= 10 && (endPos.y - _clickPos.y) <= 10)
		_callback(x, y);
}

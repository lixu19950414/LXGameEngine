#include "stdafx.h"
#include "Button.h"


Button::Button():
	_callback(nullptr)
{
}


Button::~Button()
{
}

bool Button::onTouchBegin(int x, int y)
{
	if (_callback)
		_callback(x, y);
	return false;
}

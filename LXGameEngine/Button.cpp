#include "stdafx.h"
#include "Button.h"


Button::Button():
	_callback(nullptr)
{
}

void Button::handleTouch(int x, int y)
{
	if (_callback)
		_callback(x, y);
}


Button::~Button()
{
}

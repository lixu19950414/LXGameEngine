#include "stdafx.h"
#include "Rect.h"


Rect::Rect():
_origin(0.0f, 0.0f),
_size(0.0f, 0.0f)
{
}

Rect::Rect(glm::vec2 origin, glm::vec2 size)
{
	_origin = origin;
	_size = size;
}

Rect::Rect(GLfloat oriX, GLfloat oriY, GLfloat sizeX, GLfloat sizeY)
{
	_origin = glm::vec2(oriX, oriY);
	_size = glm::vec2(sizeX, sizeY);
}


bool Rect::containPoint(const glm::vec2& point)
{
	return (_origin.x <= point.x && point.x <= _origin.x + _size.x) && (_origin.y <= point.y && point.y <= _origin.y + _size.y);
}


bool Rect::containPoint(GLfloat x, GLfloat y)
{
	return (_origin.x <= x && x <= _origin.x + _size.x) && (_origin.y <= y && y <= _origin.y + _size.y);
}

Rect::~Rect()
{
}

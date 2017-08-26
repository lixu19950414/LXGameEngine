#include "stdafx.h"
#include "SpriteFrame.h"


SpriteFrame::SpriteFrame():
_pixelRect(Rect()),
_texture(nullptr),
_lbTexCoord(0.0f, 0.0f),
_ltTexCoord(0.0f, 0.0f),
_rbTexCoord(0.0f, 0.0f),
_rtTexCoord(0.0f, 0.0f)
{
}

bool SpriteFrame::initWithTextureRect(Texture2D * texture, const Rect & rect)
{
	if (_texture != nullptr) {
		_texture->release();
	}
	_texture = texture;
	_pixelRect = rect;
	_texture->retain();
	calTexCoord();
	return true;
}

void SpriteFrame::calTexCoord()
{
	GLint texWidth = _texture->getPixelWidth();
	GLint texHeight =  _texture->getPixelHeight();
	glm::vec2 origin = _pixelRect.getOrigin();
	glm::vec2 size = _pixelRect.getSize();

	_lbTexCoord.x = origin.x / texWidth;
	_lbTexCoord.y = origin.y / texHeight;
	_ltTexCoord.x = origin.x / texWidth;
	_ltTexCoord.y = (origin.y + size.y) / texHeight;
	_rbTexCoord.x = (origin.x + size.x) / texWidth;
	_rbTexCoord.y = origin.y / texHeight;
	_rtTexCoord.x = (origin.x + size.x) / texWidth;
	_rtTexCoord.y = (origin.y + size.y) / texHeight;

	// LX_LOG("%f %f %f %f %f %f %f %f", _lbTexCoord.x, _lbTexCoord.y, _ltTexCoord.x, _ltTexCoord.y, _rbTexCoord.x, _rbTexCoord.y, _rtTexCoord.x, _rtTexCoord.y)
}

SpriteFrame::~SpriteFrame()
{
	if (_texture != nullptr) {
		_texture->release();
	}
}

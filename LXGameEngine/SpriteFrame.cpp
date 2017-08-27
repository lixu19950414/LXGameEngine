#include "stdafx.h"
#include "SpriteFrame.h"


SpriteFrame::SpriteFrame():
_pixelRect(Rect()),
_texture(nullptr),
_textureGrid(nullptr),
_lbTexCoord(0.0f, 0.0f),
_ltTexCoord(0.0f, 0.0f),
_rbTexCoord(0.0f, 0.0f),
_rtTexCoord(0.0f, 0.0f),
_gridPoint(255, 255),
_useTextureGrid(false)
{
}

bool SpriteFrame::initWithTextureRect(Texture2D * texture, const Rect & rect)
{
	_texture = texture;
	_pixelRect = rect;
	_texture->retain();
	_useTextureGrid = false;
	calTexCoord();
	return true;
}

bool SpriteFrame::initWithTextureGrid(TextureGrid * tg, const GridPoint & gp, const Rect & rect)
{
	_textureGrid = tg;
	_textureGrid->retain();
	_gridPoint = gp;
	_pixelRect = rect;
	_useTextureGrid = true;
	calTexCoord();
	return true;
}

void SpriteFrame::bindTexture()
{
	if (_useTextureGrid) {
		glBindTexture(GL_TEXTURE_2D, _textureGrid->getName());
	}
	else {
		glBindTexture(GL_TEXTURE_2D, _texture->getName());
	}
}

void SpriteFrame::calTexCoord()
{
	GLint texWidth, texHeight;
	if (!_useTextureGrid) {
		texWidth = _texture->getPixelWidth();
		texHeight = _texture->getPixelHeight();
	}
	else {
		texWidth = _textureGrid->getPixelWidth();
		texHeight = _textureGrid->getPixelHeight();
	}
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

	// LX_LOG("%f %f %f %f %f %f %f %f\n", _lbTexCoord.x, _lbTexCoord.y, _ltTexCoord.x, _ltTexCoord.y, _rbTexCoord.x, _rbTexCoord.y, _rtTexCoord.x, _rtTexCoord.y)
}

SpriteFrame::~SpriteFrame()
{
	if (_texture != nullptr) {
		_texture->release();
	}
	if (_textureGrid != nullptr) {
		_textureGrid->pushOneFreeGridPoint(_gridPoint);
		_textureGrid->release();
	}
}

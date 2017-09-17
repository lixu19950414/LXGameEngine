#include "stdafx.h"
#include "Label.h"


Label::Label() :
	_fontSize(24),
	_fontOutlineSize(0),
	_fontOpacity(255),
	_needRecreateSprites(true),
	_needRefreshSpritesPos(true),
	_currentString(""),
	_fontName("")
{
	_fontColor[0] = 0;
	_fontColor[1] = 0;
	_fontColor[2] = 0;
	_fontOutlineColor[0] = 0;
	_fontOutlineColor[1] = 0;
	_fontOutlineColor[2] = 0;
	//memset(_fontOutlineColor, 0, 3);
}


Label::~Label()
{
	releaseCurrentSprites();
}

bool Label::initWithFont(const std::string & fontName, int fontSize, const std::string & s)
{
	setFontName(fontName);
	setFontSize(fontSize);
	setString(s);
	return true;
}

void Label::visit(glm::mat4 & parentTransform)
{
	setupSprites();
	sortChildren();
	updateTransform();
	_modelTransform = parentTransform * _transform;
	updateAABB();
	auto start = _children.begin();
	// visit nodes with z < 0
	for (; start != _children.end(); ++start) {
		if ((*start)->getLocalZ() < 0) {
			(*start)->visit(_modelTransform);
		}
		else {
			break;
		}
	}
	draw();
	// visit nodes with z >= 0
	for (; start != _children.end(); ++start) {
		(*start)->visit(_modelTransform);
	}
}

void Label::setContentSize(GLfloat width, GLfloat height)
{
	if (_contentSize.x != width || _contentSize.y != height)
	{
		_contentSize = glm::vec2(width, height);
		_aabbDirty = true;
		_needRefreshSpritesPos = true;
	}
}

void Label::setAnchorPoint(GLfloat x, GLfloat y)
{
	if (_anchorPoint.x != x || _contentSize.y != y)
	{
		_anchorPoint = glm::vec2(x, y);
		_aabbDirty = true;
		_needRefreshSpritesPos = true;
	}
}

void Label::setOpacity(GLubyte opacity)
{
	if (_fontOpacity != opacity) {
		_fontOpacity = opacity;
		for (auto sprite : _sprites) {
			sprite->setOpacity(opacity);
		}
		for (auto sprite : _outlineSprites) {
			sprite->setOpacity(opacity);
		}
	}
}

void Label::setColor(GLubyte r, GLubyte g, GLubyte b)
{
	if (_fontColor[0] != r || _fontColor[1] != g || _fontColor[2] != b) {
		_fontColor[0] = r;
		_fontColor[1] = g;
		_fontColor[2] = b;
		for (auto sprite : _sprites) {
			sprite->setColor(r, g, b);
		}
	}
}

void Label::setOutlineColor(GLubyte r, GLubyte g, GLubyte b)
{
	if (_fontOutlineColor[0] != r || _fontOutlineColor[1] != g || _fontOutlineColor[2] != b) {
		_fontOutlineColor[0] = r;
		_fontOutlineColor[1] = g;
		_fontOutlineColor[2] = b;
		for (auto sprite : _outlineSprites) {
			sprite->setColor(r, g, b);
		}
	}
}

void Label::setString(const std::string & s)
{
	if (_currentString != s) {
		_currentString = s;
		_needRecreateSprites = true;
	}
}

void Label::setFontName(const std::string & s)
{
	if (_fontName != s) {
		_fontName = s;
		_needRecreateSprites = true;
	}
}

void Label::setFontSize(int fontSize)
{
	if (_fontSize != fontSize) {
		_fontSize = fontSize;
		_needRecreateSprites = true;
	}
}

void Label::setOutlineSize(int outlineSize)
{
	if (outlineSize != _fontOutlineSize) {
		_fontOutlineSize = outlineSize;
		_needRecreateSprites = true;
	}
}

void Label::setupSprites()
{
	if (_needRecreateSprites) {
		createSprites();
		refreshSpritesPos();
	}
	else if(_needRefreshSpritesPos) {
		refreshSpritesPos();
	}
	_needRecreateSprites = false;
	_needRefreshSpritesPos = false;
}

void Label::createSprites()
{
	releaseCurrentSprites();
	if (_fontOutlineSize > 0) {
		for (auto it = _currentString.begin(); it != _currentString.end(); ++it) {
			LabelSprite* ls = new (std::nothrow) LabelSprite();
			std::string temp;
			temp.push_back(*it);
			ls->initWithString(_fontName, temp, _fontSize, false, 0);
			ls->setColor(_fontColor[0], _fontColor[1], _fontColor[2]);
			ls->setOpacity(_fontOpacity);

			LabelSprite* outline = new (std::nothrow) LabelSprite();
			std::string temp2;
			temp2.push_back(*it);
			outline->initWithString(_fontName, temp, _fontSize, true, _fontOutlineSize);
			outline->setColor(_fontOutlineColor[0], _fontOutlineColor[1], _fontOutlineColor[2]);
			outline->setOpacity(_fontOpacity);

			addChild(outline);
			addChild(ls);
			_sprites.push_back(ls);
			_outlineSprites.push_back(outline);
		}
	}
	else {
		for (auto it = _currentString.begin(); it != _currentString.end(); ++it) {
			LabelSprite* ls = new (std::nothrow) LabelSprite();
			std::string temp;
			temp.push_back(*it);
			ls->initWithString(_fontName, temp, _fontSize, false, 0);
			ls->setColor(_fontColor[0], _fontColor[1], _fontColor[2]);
			ls->setOpacity(_fontOpacity);
			addChild(ls);
			_sprites.push_back(ls);
		}
	}
}

void Label::refreshSpritesPos()
{
	glm::vec2 startPos = _contentSize * -_anchorPoint;
	if (_fontOutlineSize > 0) {
		for (int i = 0; i < _sprites.size(); ++i) {
			CharacterInfo* characterInfo = _sprites.at(i)->getCharacterInfo();
			glm::vec2 bearing = characterInfo->getBearing();
			glm::vec2 size = characterInfo->getSize();
			_sprites.at(i)->setPosition(startPos.x + bearing.x, startPos.y - (size.y - bearing.y));

			CharacterInfo* outlineInfo = _outlineSprites.at(i)->getCharacterInfo();
			glm::vec2 outlineSize = outlineInfo->getSize();
			glm::vec2 offset = size - outlineSize;
			//LX_LOG("offset: x: %f, y: %f\n", offset.x, offset.y);
			//glm::vec2 offset;
			_outlineSprites.at(i)->setPosition(startPos.x + bearing.x + offset.x / 2.0, startPos.y - (size.y - bearing.y) + offset.y / 2.0);

			startPos.x += characterInfo->getAdvance() >> 6;
		}
	}
	else {
		for (auto sprite : _sprites) {
			CharacterInfo* characterInfo = sprite->getCharacterInfo();
			glm::vec2 bearing = characterInfo->getBearing();
			glm::vec2 size = characterInfo->getSize();
			sprite->setPosition(startPos.x + bearing.x, startPos.y - (size.y - bearing.y));
			startPos.x += characterInfo->getAdvance() >> 6;
		}
	}
}

void Label::releaseCurrentSprites()
{
	removeAllChildren();
	for (auto sprite : _sprites) {
		sprite->release();
	}
	for (auto sprite : _outlineSprites) {
		sprite->release();
	}
	_sprites.clear();
	_outlineSprites.clear();
}



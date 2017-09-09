#include "stdafx.h"
#include "LabelSprite.h"
#include "ShaderCache.h"


LabelSprite::LabelSprite()
{
	if (_shader != nullptr) {
		_shader->release();
	}
	_shader = ShaderCache::getInstance()->getGlobalShader(ShaderCache::LX_SHADERS_PVM_FONT);
	_shader->retain();
}


LabelSprite::~LabelSprite()
{
}

bool LabelSprite::initWithString(const std::string& fontName, const std::string & s, int fontSize, bool hasOutLine, int outLineSize)
{
	char ss = s.c_str()[0];
	_characterInfo = FontCache::getInstance()->getCharacterInfo(fontName, s, fontSize, false, 0);
	return this->initWithSpriteFrame(_characterInfo->getSpriteFrame());
}


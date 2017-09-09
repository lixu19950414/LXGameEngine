#ifndef LABEL_SPRITE_H
#define LABEL_SPRITE_H

#include "Sprite.h"
#include "FontCache.h"
class LabelSprite :
	public Sprite
{
public:
	LabelSprite();
	~LabelSprite();
	bool initWithString(const std::string& fontName, const std::string& s, int fontSize, bool hasOutLine, int outLineSize);
private:
	CharacterInfo* _characterInfo;
};

#endif

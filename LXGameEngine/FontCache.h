#ifndef FONT_CACHE_H
#define FONT_CACHE_H

#include <unordered_map>
#include <string>
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_STROKER_H
#include "SpriteFrame.h"

class CharacterInfo {
public:
	CharacterInfo();
	bool initWithGlyph(FT_GlyphSlot glyph, SpriteFrame* sp);
	bool initWithOutlineInfo(int width, int height, SpriteFrame* sp);
	inline SpriteFrame* getSpriteFrame() { return _spriteFrame; };
	inline GLuint getAdvance() { return _advance; };
	inline glm::ivec2 getSize() { return _size; };
	inline glm::ivec2 getBearing() { return _bearing; };
	void dump();
	~CharacterInfo();
private:
	glm::ivec2 _size;
	glm::ivec2 _bearing;
	GLuint     _advance;
	SpriteFrame* _spriteFrame;
};

class FontCache
{
public:
	static FontCache* getInstance();
	static std::size_t getHash(const std::string& fontName, const std::string& character, int fontSize, bool isOutLine, int outLineSize);
	FontCache();
	
	FT_Face getFaceWithKey(const std::string& key);
	CharacterInfo* getCharacterInfo(const std::string& fontName, const std::string& character, int fontSize, bool isOutLine, int outLineSize);
	~FontCache();
private:
	std::unordered_map <std::string, FT_Face> _faces;
	std::unordered_map <std::size_t, CharacterInfo*> _characters;
	FT_Stroker _stroker;
};

#endif

#include "stdafx.h"
#include "FontCache.h"
#include "SpriteFrame.h"
#include "TextureGridCache.h"
#include <LXFileUtil\LXFileUtil.h>

FontCache* g_pFontCache = nullptr;
FT_Library g_FTLibrary;

FontCache * FontCache::getInstance()
{
	if (g_pFontCache == nullptr) {
		g_pFontCache = new (std::nothrow) FontCache();
	}
	return g_pFontCache;
}

std::size_t FontCache::getHash(const std::string & fontName, const std::string & character, int fontSize, bool isOutLine, int outLineSize)
{
	if (isOutLine) {
		std::size_t h1 = std::hash<std::string>{}(fontName);
		std::size_t h2 = std::hash<std::string>{}(character);
		std::size_t h3 = std::hash<int>{}(fontSize);
		std::size_t h4 = std::hash<bool>{}(isOutLine);
		std::size_t h5 = std::hash<int>{}(outLineSize);
		return (((h1 ^ (h2 << 1)) ^ (h3 << 1)) ^ (h4 << 1)) ^ (h5 << 1);
	}
	else{
		std::size_t h1 = std::hash<std::string>{}(fontName);
		std::size_t h2 = std::hash<std::string>{}(character);
		std::size_t h3 = std::hash<int>{}(fontSize);
		return (h1 ^ (h2 << 1)) ^ (h3 << 1);
	}
}

FontCache::FontCache()
{
	if (FT_Init_FreeType(&g_FTLibrary))
		LX_LOG("[FontCache]-->Could not init FreeType Library\n");
}

FT_Face FontCache::getFaceWithKey(const std::string & key)
{
	auto it = _faces.find(key);
	if (it != _faces.end()) {
		return it->second;
	}
	else {
		FT_Face face;
		const std::string& wholePath = LX_FU::getAbsolutePath(key);
		if (!FT_New_Face(g_FTLibrary, wholePath.c_str(), 0, &face)) {
			_faces.emplace(key, face);
			LX_LOG("[FontCache]-->Create new font face with key, %s\n", key.c_str());
			return face;
		}
		else {
			LX_LOG("[FontCache]-->Failed to load font with key: %s\n", key.c_str());
			return nullptr;
		}
	}
	return nullptr;
}

CharacterInfo * FontCache::getCharacterInfo(const std::string & fontName, const std::string & character, int fontSize, bool isOutLine, int outLineSize)
{
	std::size_t thisHash = getHash(fontName, character, fontSize, isOutLine, outLineSize);
	auto it = _characters.find(thisHash);
	if (it == _characters.end()) {
		FT_Face face = getFaceWithKey(fontName);
		FT_Set_Char_Size(face, 0, fontSize * 64, 72, 72);
		if (FT_Load_Char(face, character.c_str()[0], FT_LOAD_RENDER)) {
			LX_LOG("Failed to load char\n");
			return nullptr;
		}
		TextureGrid* tg = TextureGridCache::getInstance()->getFontsGrid();
		GridPoint gp = tg->autoFitAndGetGridPoint(face->glyph->bitmap.width, face->glyph->bitmap.rows, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
		SpriteFrame* spriteFrame = new (std::nothrow) SpriteFrame();
		Rect rect(glm::vec2(tg->getPartPixelWidth() * gp._x, tg->getPartPixelHeight() * gp._y), glm::vec2(face->glyph->bitmap.width, face->glyph->bitmap.rows));
		spriteFrame->initWithTextureGrid(tg, gp, rect);
		spriteFrame->autoRelease();

		CharacterInfo* characterInfo = new CharacterInfo();
		characterInfo->initWithGlyph(face->glyph, spriteFrame);
		_characters.emplace(thisHash, characterInfo);
		
		return characterInfo;
	}
	else{
		return it->second;
	}
}


FontCache::~FontCache()
{
	for (auto it : _faces) {
		FT_Done_Face(it.second);
	}
	_faces.clear();
	for (auto it2 : _characters) {
		delete it2.second;
	}
	_characters.clear();
	FT_Done_FreeType(g_FTLibrary);
	g_pFontCache = nullptr;
}

CharacterInfo::CharacterInfo()
{
}

bool CharacterInfo::initWithGlyph(FT_GlyphSlot glyph, SpriteFrame* sp)
{
	_size.x = glyph->bitmap.width;
	_size.y = glyph->bitmap.rows;
	_advance = glyph->advance.x;
	_bearing.x = glyph->bitmap_left;
	_bearing.y = glyph->bitmap_top;
	sp->retain();
	_spriteFrame = sp;
	return true;
}

void CharacterInfo::dump()
{
	LX_LOG("CharacterInfo::dump\n");
	LX_LOG("Advance: %d\n", _advance>>6);
	LX_LOG("Size: %d, %d\n", _size.x, _size.y);
	LX_LOG("Bearing: %d, %d\n", _bearing.x, _bearing.y);
}

CharacterInfo::~CharacterInfo()
{
	if (_spriteFrame != nullptr) {
		_spriteFrame->release();
	}
}

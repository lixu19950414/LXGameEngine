#include "stdafx.h"
#include "FontCache.h"
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

FontCache::FontCache()
{
	if (FT_Init_FreeType(&g_FTLibrary))
		LX_LOG("ERROR::FREETYPE: Could not init FreeType Library\n");
}

FT_Face FontCache::getFaceWithKey(const std::string & key)
{
	auto it = _faces.find(key);
	if (it != _faces.end()) {
		return it->second;
	}
	else {
		FT_Face face;
		if (FT_New_Face(g_FTLibrary, key.c_str(), 0, &face)) {
			_faces.emplace(key, face);
			return face;
		}
		else {
			LX_LOG("ERROR::FREETYPE: Failed to load font\n");
			return nullptr;
		}
	}
	return nullptr;
}


FontCache::~FontCache()
{
}

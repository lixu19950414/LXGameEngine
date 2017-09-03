#ifndef FONT_CACHE_H
#define FONT_CACHE_H

#include <unordered_map>
#include <string>
#include <ft2build.h>
#include FT_FREETYPE_H 

class FontCache
{
public:
	static FontCache* getInstance();
	FontCache();
	FT_Face getFaceWithKey(const std::string& key);
	~FontCache();
private:
	std::unordered_map <std::string, FT_Face> _faces;
};

#endif

#ifndef TEXTURE_GRID_CACHE_H
#define TEXTURE_GRID_CACHE_H

#include <unordered_map>
#include "TextureGrid.h"

class TextureGridCache
{
public:
	TextureGridCache();
	static TextureGridCache* getInstance();
	~TextureGridCache();

	TextureGrid* getTextureGridForKey(const std::string& key);
	TextureGrid* addTextureGridWithKey(const std::string& key, GLint pixelWidth, GLint pixelHeight, unsigned short partPixelWidth, unsigned short partPixelHeight, GLenum internalFormat = GL_RGBA);
	bool enableTextureGridWithKey(const std::string& key);
	void disableTextureGridCache();
	inline TextureGrid* getCurrentTextureGrid() { return _enabledTextureGrid; };

private:
	std::unordered_map<std::string, TextureGrid*> _cachedTextureGrids;
	TextureGrid* _enabledTextureGrid; // weak ref
};

#endif

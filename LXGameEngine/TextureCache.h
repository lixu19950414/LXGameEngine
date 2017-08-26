#ifndef TEXTURE_CACHE_H
#define TEXTURE_CACHE_H

#include <unordered_map>
#include "Texture2D.h"

class TextureCache
{
public:
	TextureCache();
	~TextureCache();
	static TextureCache* getInstance();
	Texture2D* getTextureForKey(const std::string& key);
	Texture2D* addTextureWithFileName(const std::string& key, Image::ImageDataType type=Image::ImageDataType::IMAGE_RGBA);
	int removeUnusedTextures();
private:
	std::unordered_map<std::string, Texture2D*> _cachedTextures;
};

#endif

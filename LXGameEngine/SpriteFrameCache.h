#ifndef SPRITE_FRAME_CACHE_H
#define SPRITE_FRAME_CACHE_H

#include <unordered_map>
#include <string>
#include "SpriteFrame.h"
#include "Texture2D.h"
#include "Rect.h"
#include "Image.h"
#include "Texture2D.h"
#include "TextureCache.h"
#include "TextureGridCache.h"

class SpriteFrameCache
{
public:
	SpriteFrameCache();
	~SpriteFrameCache();
	static SpriteFrameCache* getInstance();
	int removeUnusedSpriteFrames();
	SpriteFrame* getSpriteFrameForKey(const std::string& key);
	SpriteFrame* addSpriteFrameWithKey(const std::string& key, Texture2D* texture, const Rect& rect);
	SpriteFrame* addSpriteFrameWithTextureGrid(const std::string & key, TextureGrid* tg, const GridPoint& gp, Rect rect);
	SpriteFrame* addSpriteFrameWithFileName(const std::string& key, Image::ImageDataType type = Image::ImageDataType::IMAGE_RGBA);
private:
	std::unordered_map<std::string, SpriteFrame*> _cachedSpriteFrames;
};

#endif
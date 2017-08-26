#include "stdafx.h"
#include "SpriteFrameCache.h"


SpriteFrameCache* g_pSpriteFrameCache = nullptr;

SpriteFrameCache::SpriteFrameCache()
{
}

SpriteFrameCache::~SpriteFrameCache()
{
	for (auto it : _cachedSpriteFrames) {
		it.second->release();
	}
	_cachedSpriteFrames.clear();
}

SpriteFrameCache * SpriteFrameCache::getInstance()
{
	if (g_pSpriteFrameCache == nullptr) {
		g_pSpriteFrameCache = new (std::nothrow) SpriteFrameCache();
	}
	return g_pSpriteFrameCache;
}

int SpriteFrameCache::removeUnusedSpriteFrames()
{
	int cnt = 0;
	auto it = _cachedSpriteFrames.begin();
	while (it != _cachedSpriteFrames.end()) {
		if (it->second->getReferenceCount() == 1) {
			it->second->release();
			it = _cachedSpriteFrames.erase(it);
		}
		else {
			++it;
		}
	}
	return 0;
}

SpriteFrame * SpriteFrameCache::getSpriteFrameForKey(const std::string& key)
{
	auto it = _cachedSpriteFrames.find(key);
	if (it == _cachedSpriteFrames.end()) {
		return nullptr;
	}
	else{
		return it->second;
	}
}

SpriteFrame * SpriteFrameCache::addSpriteFrameWithKey(const std::string & key, Texture2D * texture, const Rect & rect)
{
	SpriteFrame* spriteFrame = getSpriteFrameForKey(key);
	if (spriteFrame == nullptr) {
		spriteFrame = new (std::nothrow) SpriteFrame();
		bool ret = spriteFrame->initWithTextureRect(texture, rect);
		if (ret) {
			_cachedSpriteFrames.emplace(key, spriteFrame);
			return spriteFrame;
		}
		else {
			delete spriteFrame;
			return nullptr;
		}
	}
	else{
		return spriteFrame;
	}
	
}

SpriteFrame * SpriteFrameCache::addSpriteFrameWithFileName(const std::string & key, Image::ImageDataType type)
{
	TextureCache* ins = TextureCache::getInstance();
	Texture2D* tex = ins->addTextureWithFileName(key, type);
	SpriteFrame* spriteFrame = this->addSpriteFrameWithKey(key, tex, Rect(glm::vec2(0.0f, 0.0f), glm::vec2(tex->getPixelWidth(), tex->getPixelHeight())));
	return spriteFrame;
}

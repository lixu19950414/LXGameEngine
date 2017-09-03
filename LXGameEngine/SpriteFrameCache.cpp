#include "stdafx.h"
#include "SpriteFrameCache.h"
#include "Image.h"


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
	g_pSpriteFrameCache = nullptr;
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
			++cnt;
		}
		else {
			++it;
		}
	}
	return cnt;
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

SpriteFrame * SpriteFrameCache::addSpriteFrameWithTextureGrid(const std::string & key, TextureGrid * tg, const GridPoint & gp, Rect rect)
{
	SpriteFrame* spriteFrame = getSpriteFrameForKey(key);
	if (spriteFrame == nullptr) {
		spriteFrame = new (std::nothrow) SpriteFrame();
		bool ret = spriteFrame->initWithTextureGrid(tg, gp, rect);
		if (ret) {
			_cachedSpriteFrames.emplace(key, spriteFrame);
			return spriteFrame;
		}
		else {
			delete spriteFrame;
			return nullptr;
		}
	}
	else {
		return spriteFrame;
	}
}

SpriteFrame * SpriteFrameCache::addSpriteFrameWithFileName(const std::string & key, Image::ImageDataType type)
{
	// If spriteFrameCache has this key, return directly.
	SpriteFrame* spriteFrame = getSpriteFrameForKey(key);
	if (spriteFrame != nullptr) {
		return spriteFrame;
	}
	// If textureCache has this key, generate spriteFrame and return.
	TextureCache* ins = TextureCache::getInstance();
	Texture2D* t2d = ins->getTextureForKey(key);
	if (t2d != nullptr) {
		spriteFrame = this->addSpriteFrameWithKey(key, t2d, Rect(glm::vec2(0.0f, 0.0f), glm::vec2(t2d->getPixelWidth(), t2d->getPixelHeight())));
		return spriteFrame;
	}
	// Create image first.
	Image* image = new (std::nothrow) Image(key, type);
	if (!image->getLoadSuccess()) {
		delete image;
		return nullptr;
	}

	// Can we use texture grid?
	TextureGridCache* inss = TextureGridCache::getInstance();
	TextureGrid* curTG = inss->getCurrentTextureGrid();
	if (curTG != nullptr) {
		GridPoint gp = curTG->autoFitAndGetGridPoint(image->getWidth(), image->getHeight(), GL_UNSIGNED_BYTE, image->getData());
		if (!curTG->isInvalidGridPoint(gp)) {
			Rect rect(glm::vec2(curTG->getPartPixelWidth() * gp._x, curTG->getPartPixelHeight() * gp._y), glm::vec2(image->getWidth(), image->getHeight()));
			spriteFrame = this->addSpriteFrameWithTextureGrid(key, curTG, gp, rect);
			delete image;
			return spriteFrame;
		}
	}
	
	// Finally use texture to create spriteFrame.	
	Texture2D* tex = ins->addTextureWithImage(key, image);
	delete image;
	if (tex == nullptr) {
		return nullptr;
	}
	spriteFrame = this->addSpriteFrameWithKey(key, tex, Rect(glm::vec2(0.0f, 0.0f), glm::vec2(tex->getPixelWidth(), tex->getPixelHeight())));
	return spriteFrame;
}

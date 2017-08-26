#include "stdafx.h"
#include "TextureCache.h"
#include "Image.h"

TextureCache* g_pTextureCache = nullptr;

TextureCache::TextureCache()
{
}


TextureCache::~TextureCache()
{
	for (auto it : _cachedTextures) {
		it.second->release();
	}
	_cachedTextures.clear();
}

TextureCache * TextureCache::getInstance()
{
	if (g_pTextureCache == nullptr) {
		g_pTextureCache = new (std::nothrow) TextureCache();
	}
	return g_pTextureCache;
}

Texture2D * TextureCache::getTextureForKey(const std::string & key)
{
	auto it = _cachedTextures.find(key);
	if (it == _cachedTextures.end()) {
		return nullptr;
	}
	else {
		return it->second;
	}
}

Texture2D * TextureCache::addTextureWithFileName(const std::string & key, Image::ImageDataType type)
{
	Texture2D* find = getTextureForKey(key);
	if (find == nullptr) {
		find = new (std::nothrow) Texture2D();
		bool ret = find->initWithFileName(key, type);
		if (ret) {
			_cachedTextures.emplace(key, find);
			return find;
		}
		else {
			delete find;
			return nullptr;
		}
	}
	else {
		return find;
	}
}

int TextureCache::removeUnusedTextures()
{
	int cnt = 0;
	auto it = _cachedTextures.begin();
	while (it != _cachedTextures.end()) {
		if (it->second->getReferenceCount() == 1) {
			it->second->release();
			it = _cachedTextures.erase(it);
			++cnt;
		}
		else{
			++it;
		}
	}
	return cnt;
}

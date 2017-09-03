#include "stdafx.h"
#include "TextureGridCache.h"


TextureGridCache* g_pTextureGridCache = nullptr;

TextureGridCache::TextureGridCache():
	_enabledTextureGrid(nullptr)
{
}

TextureGridCache * TextureGridCache::getInstance()
{
	if (g_pTextureGridCache == nullptr) {
		g_pTextureGridCache = new (std::nothrow) TextureGridCache();
	}
	return g_pTextureGridCache;
}


TextureGridCache::~TextureGridCache()
{
	for (auto it : _cachedTextureGrids) {
		it.second->release();
	}
	_cachedTextureGrids.clear();
	g_pTextureGridCache = nullptr;
}

TextureGrid * TextureGridCache::getTextureGridForKey(const std::string & key)
{
	auto it = _cachedTextureGrids.find(key);
	if (it != _cachedTextureGrids.end()) {
		return it->second;
	}
	else {
		return nullptr;
	}
}

TextureGrid * TextureGridCache::addTextureGridWithKey(const std::string & key, GLint pixelWidth, GLint pixelHeight, unsigned short partPixelWidth, unsigned short partPixelHeight, GLenum internalFormat)
{
	auto it = _cachedTextureGrids.find(key);
	if (it != _cachedTextureGrids.end()) {
		return it->second;
	}
	else{
		TextureGrid* tg = new (std::nothrow) TextureGrid();
		bool ret = tg->initWithGridPixelSize(pixelWidth, pixelHeight, partPixelWidth, partPixelHeight, internalFormat);
		if (ret){
			_cachedTextureGrids.emplace(key, tg);
			return tg;
		}
		else{
			delete tg;
			return nullptr;
		}

	}
	return nullptr;
}

bool TextureGridCache::enableTextureGridWithKey(const std::string & key)
{
	TextureGrid* tg = getTextureGridForKey(key);
	if (tg == nullptr) {
		_enabledTextureGrid = nullptr;
		return false;
	}
	else{
		_enabledTextureGrid = tg;
		return true;
	}

}

void TextureGridCache::disableTextureGridCache()
{
	_enabledTextureGrid = nullptr;
}

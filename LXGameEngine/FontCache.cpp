#include "stdafx.h"
#include "FontCache.h"
#include "SpriteFrame.h"
#include "TextureGridCache.h"
#include <LXFileUtil\LXFileUtil.h>


FontCache* g_pFontCache = nullptr;
FT_Library g_FTLibrary;


struct FontSpan
{
	FontSpan() { }
	FontSpan(int _x, int _y, int _width, int _coverage)
		: x(_x), y(_y), width(_width), coverage(_coverage) { }

	int x, y, width, coverage;
};

struct FontRect
{
	FontRect() { }
	FontRect(float left, float top, float right, float bottom)
		: xmin(left), xmax(right), ymin(top), ymax(bottom) { }

	void Include(const glm::vec2 &r)
	{
		xmin = std::min(xmin, r.x);
		ymin = std::min(ymin, r.y);
		xmax = std::max(xmax, r.x);
		ymax = std::max(ymax, r.y);
	}

	float Width() const { return xmax - xmin + 1; }
	float Height() const { return ymax - ymin + 1; }

	float xmin, xmax, ymin, ymax;
};

void RasterCallback(const int y, const int count, const FT_Span * const spans, void * const user)
{
	//    std::cout<<count<<std::endl;
	std::vector<FontSpan> *sptr = (std::vector<FontSpan> *)user;
	for (int i = 0; i < count; ++i) {
		sptr->push_back(FontSpan(spans[i].x, y, spans[i].len, spans[i].coverage));
	}
}



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
	FT_Stroker_New(g_FTLibrary, &_stroker);
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
		if (isOutLine) {
			FT_Face face = getFaceWithKey(fontName);
			FT_Set_Char_Size(face, 0, fontSize * 64, 72, 72);

			std::vector<FontSpan> outlineSpans;
			FT_Raster_Params params;
			memset(&params, 0, sizeof(params));
			params.flags = FT_RASTER_FLAG_AA | FT_RASTER_FLAG_DIRECT;
			params.gray_spans = RasterCallback;
			params.user = &outlineSpans;

			GLuint index = FT_Get_Char_Index(face, character.c_str()[0]);
			FT_Load_Glyph(face, index, FT_LOAD_NO_BITMAP);
			/*FT_Stroker stroker;
			FT_Stroker_New(g_FTLibrary, &stroker);*/
			FT_Stroker_Set(_stroker, outLineSize << 6, FT_STROKER_LINECAP_ROUND, FT_STROKER_LINEJOIN_ROUND, 0);
			FT_Glyph glyph;
			FT_Get_Glyph(face->glyph, &glyph);
			FT_Glyph_StrokeBorder(&glyph, _stroker, 0, 1);
			FT_Outline *o = &reinterpret_cast<FT_OutlineGlyph>(glyph)->outline;
			FT_Outline_Render(g_FTLibrary, o, &params);

			FontRect fontRect(outlineSpans.front().x, outlineSpans.front().y, outlineSpans.front().x, outlineSpans.front().y);
			for (auto s = outlineSpans.begin(); s != outlineSpans.end(); ++s)
			{
				fontRect.Include(glm::vec2(s->x, s->y));
				fontRect.Include(glm::vec2(s->x + s->width - 1, s->y));
			}
			int imgWidth = fontRect.Width();
			int imgHeight = fontRect.Height();
			int imgSize = imgWidth * imgHeight;
			unsigned char* outlineBitMap = new unsigned char[imgSize];
			memset(outlineBitMap, 0, imgSize);
			for (auto s = outlineSpans.begin(); s != outlineSpans.end(); ++s)
				for (int w = 0; w < s->width; ++w)
					outlineBitMap[(int)((imgHeight - 1 - (s->y - fontRect.ymin)) * imgWidth + s->x - fontRect.xmin + w)] = s->coverage;


			TextureGrid* tg = TextureGridCache::getInstance()->getFontsGrid();
			GridPoint gp = tg->autoFitAndGetGridPoint(imgWidth, imgHeight, GL_UNSIGNED_BYTE, outlineBitMap);
			SpriteFrame* spriteFrame = new (std::nothrow) SpriteFrame();
			Rect rect(glm::vec2(tg->getPartPixelWidth() * gp._x, tg->getPartPixelHeight() * gp._y), glm::vec2(imgWidth, imgHeight));
			spriteFrame->initWithTextureGrid(tg, gp, rect);
			spriteFrame->autoRelease();

			CharacterInfo* characterInfo = new CharacterInfo();
			characterInfo->initWithOutlineInfo(imgWidth, imgHeight, spriteFrame);
			_characters.emplace(thisHash, characterInfo);

			delete outlineBitMap;
			return characterInfo;
		}
		else {
			FT_Face face = getFaceWithKey(fontName);
			FT_Set_Char_Size(face, 0, fontSize * 64, 72, 72);
			GLuint index = FT_Get_Char_Index(face, character.c_str()[0]);
			FT_Load_Glyph(face, index, FT_LOAD_DEFAULT);
			if (FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL)) {
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

bool CharacterInfo::initWithOutlineInfo(int width, int height, SpriteFrame * sp)
{
	_size.x = width;
	_size.y = height;
	_spriteFrame = sp;
	sp->retain();
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

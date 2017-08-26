#ifndef SPRITE_FRAME_H
#define SPRITE_FRAME_H

#include "Ref.h"
#include "Texture2D.h"
#include "Rect.h"

class SpriteFrame :
	public Ref
{
public:
	SpriteFrame();
	bool initWithTextureRect(Texture2D* texture, const Rect& rect);
	~SpriteFrame();

	inline const glm::vec2& getLBTexCoord() { return _lbTexCoord; };
	inline const glm::vec2& getLTTexCoord() { return _ltTexCoord; };
	inline const glm::vec2& getRBTexCoord() { return _rbTexCoord; };
	inline const glm::vec2& getRTTexCoord() { return _rtTexCoord; };

	inline Texture2D* getTexture() { return _texture; };
	inline Rect getPixelRect() { return _pixelRect; };

private:
	void calTexCoord();
	Rect _pixelRect;
	Texture2D* _texture;
	glm::vec2 _lbTexCoord;
	glm::vec2 _ltTexCoord;
	glm::vec2 _rbTexCoord;
	glm::vec2 _rtTexCoord;
};

#endif


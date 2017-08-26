#ifndef SPRITE_H
#define SPRITE_H

#include "Node.h"
#include "PolygonInfo.h"
#include "Shader.h"
#include "SpriteFrame.h"
#include "SpriteFrameCache.h"

class Sprite : public Node
{
public:
	Sprite();
	virtual ~Sprite();
	bool initWithFile(const std::string& filename);
	bool initWithSpriteFrame(SpriteFrame* spriteFrame);
	virtual void draw() override;
	void dump();
	void setContentSize(GLfloat width, GLfloat height) override;
	void setAnchorPoint(GLfloat x, GLfloat y) override;
	void setOpacity(GLubyte opacity) override;
	void setColor(GLubyte r, GLubyte g, GLubyte b);

protected:
	// verts
	bool _vertsDirty;
	PolygonInfo _polyInfo;
	SpriteFrame* _spriteFrame;
	Shader* _shader;
	GLubyte _color[3];
private:
	void releaseCurrentSpriteFrame();
	void fillPolygonInfo();
	void setupVAOAndVBO();
private:
	V3F_C4B_T2F _lb;
	V3F_C4B_T2F _lt;
	V3F_C4B_T2F _rb;
	V3F_C4B_T2F _rt;
};

#endif


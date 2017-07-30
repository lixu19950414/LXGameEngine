#ifndef SPRITE_H
#define SPRITE_H

#include "Node.h"
#include "PolygonInfo.h"
#include "Texture2D.h"
#include "Shader.h"

class Sprite : public Node
{
public:
	Sprite();
	virtual ~Sprite();
	bool initWithFile(const std::string& filename);
	bool initWithTexture(Texture2D* texture);
	virtual void draw() override;
	void dump();
	void setContentSize(GLfloat width, GLfloat height);
	void setAnchorPoint(GLfloat x, GLfloat y);
	void setOpacity(GLubyte opacity);

protected:
	// verts
	glm::vec2 _contentSize;
	glm::vec2 _anchorPoint;
	bool _vertsDirty;
	PolygonInfo _polyInfo;
	Texture2D* _texture;
	Shader* _shader;
	GLubyte _opacity;
private:
	void releaseCurrentTexture();
	void fillPolygonInfo();
	void setupVAOAndVBO();
private:
	V3F_C4B_T2F _lb;
	V3F_C4B_T2F _lt;
	V3F_C4B_T2F _rb;
	V3F_C4B_T2F _rt;
};

#endif


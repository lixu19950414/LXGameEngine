#ifndef LABEL_H
#define LABEL_H

#include "Node.h"
#include "PolygonInfo.h"
#include "Shader.h"
#include "SpriteFrame.h"
#include "SpriteFrameCache.h"
#include "Sprite.h"
#include <string>
#include <vector>

class Label :
	public Node
{
public:
	Label();
	virtual ~Label();
	//virtual void draw() override;
	void setContentSize(GLfloat width, GLfloat height) override;
	void setAnchorPoint(GLfloat x, GLfloat y) override;
	void setOpacity(GLubyte opacity) override;
	void setColor(GLubyte r, GLubyte g, GLubyte b);
	void setString(const std::string& s);
	void setFontSize(int fontSize);

protected:
	// verts
	bool _vertsDirty;
	std::string _currentString;
	std::vector<Sprite*> _sprites;
	int _fontSize;
	GLubyte _color[3];
};

#endif

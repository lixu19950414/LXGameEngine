#ifndef NODE_H
#define NODE_H

#include "Ref.h"
#include "Rect.h"
#include "stdafx.h"

class Node : public Ref
{
public:
	Node();
	virtual ~Node();

	virtual void visit(glm::mat4& parentTransform);
	virtual void draw();
	virtual void addChild(Node* child);
	void setPosition(GLfloat x, GLfloat y);
	void setScale(GLfloat scaleX, GLfloat scaleY);
	void setRotation(GLfloat rotate);
	void setLocalZ(short localZ);
	inline short getLocalZ() { return _localZ; };
	void sortChildren();
	inline void setNeedSortChildren() { _needSortChildren = true; };

	inline std::vector<Node*> getChildren() { return _children; };
	inline Node* getParent() { return _parent; };

	virtual void setContentSize(GLfloat width, GLfloat height);
	virtual void setAnchorPoint(GLfloat x, GLfloat y);
	virtual void setOpacity(GLubyte opacity);

protected:
	void updateTransform();
protected:
	glm::mat4 _modelTransform;

	// transform
	glm::mat4 _transform;
	glm::vec3 _position;
	GLfloat _rotation;
	glm::vec3 _scale;
	bool _transformDirty;
	bool _needSortChildren;

	short _localZ;

	std::vector<Node*> _children;
	Node* _parent;
	
	GLuint _vao;
	GLuint _vbo;
	GLuint _ebo;

	glm::vec2 _contentSize;
	glm::vec2 _anchorPoint;
	GLubyte _opacity;

};

#endif

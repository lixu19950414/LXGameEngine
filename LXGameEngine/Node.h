#ifndef NODE_H
#define NODE_H

#include "stdafx.h"
#include "Ref.h"
#include "Rect.h"
#include "Timer.h"


class Node : public Ref
{
public:
	Node();
	virtual ~Node();

	virtual void visit(glm::mat4& parentTransform);
	virtual void draw();
	virtual void addChild(Node* child);
	virtual void removeChild(Node* child);
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

	virtual bool touch(int x, int y);
	virtual bool onTouch(int x, int y);

	inline void setSwallowTouches(bool b) { _swallowTouches = b; };
	virtual bool onTouchBegin(int x, int y);
	virtual void onTouchMove(int x, int y);
	virtual void onTouchEnd(int x, int y);

	virtual glm::vec2 convertToNodeSpace(int x, int y);
	virtual glm::vec2 convertToWorldSpace(int x, int y);

	void scheduleUpdate(float interval, int leftTimes, std::function<void(float)> func, int priority = 0);
	void releaseCurrentTimer();

protected:
	void updateTransform();
	virtual void updateAABB();
protected:
	glm::mat4 _modelTransform;

	// transform
	glm::mat4 _transform;
	glm::vec3 _position;
	GLfloat _rotation;
	glm::vec3 _scale;
	bool _needSortChildren;
	AABB _aabb;

	// dirty
	bool _transformDirty;
	bool _aabbDirty;

	short _localZ;

	std::vector<Node*> _children;
	Node* _parent;
	
	GLuint _vao;
	GLuint _vbo;
	GLuint _ebo;

	glm::vec2 _contentSize;
	glm::vec2 _anchorPoint;
	GLubyte _opacity;

	bool _swallowTouches;

	Timer* _timer;
};

#endif

#ifndef NODE_H
#define NODE_H

#include "Ref.h"
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

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

	inline std::vector<Node*> getChildren() { return _children; };
	inline Node* getParent() { return _parent; };

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

	std::vector<Node*> _children;
	Node* _parent;
	
	GLuint _vao;
	GLuint _vbo;
	GLuint _ebo;

};

#endif

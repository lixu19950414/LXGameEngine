#include "stdafx.h"
#include "Node.h"
#include <glm/mat4x4.hpp>


Node::Node():
_position(0.0f, 0.0f, 0.0f),
_rotation(0.0f),
_scale(1.0f, 1.0f, 1.0f),
_transformDirty(false),
_parent(nullptr),
_vao(0),
_vbo(0),
_ebo(0)
{
}

Node::~Node()
{
	if (_vao) {
		glDeleteVertexArrays(1, &_vao);
	}
	if (_vbo) {
		glDeleteBuffers(1, &_vbo);
	}
	if (_ebo) {
		glDeleteBuffers(1, &_ebo);
	}
	for (auto child : _children) {
		child->release();
	}
	_children.clear();
	_parent = nullptr;
}

void Node::visit(glm::mat4 & parentTransform)
{
	updateTransform();
	_modelTransform = parentTransform * _transform;
	draw();
	for (auto child : _children) {
		child->visit(_modelTransform);
	}
}

void Node::draw()
{
}

void Node::addChild(Node * child)
{
	assert(child->_parent == nullptr);
	_children.push_back(child);
	child->retain();
	child->_parent = this;
}

void Node::setPosition(GLfloat x, GLfloat y)
{
	_position = glm::vec3(x, y, 0.0f);
	_transformDirty = true;
}

void Node::setScale(GLfloat scaleX, GLfloat scaleY)
{
	_scale = glm::vec3(scaleX, scaleY, 1.0f);
	_transformDirty = true;
}

void Node::setRotation(GLfloat rotate)
{
	_rotation = rotate;
	_transformDirty = true;
}

void Node::updateTransform()
{
	if (_transformDirty) {
		_transform = glm::mat4();
		_transform = glm::translate(_transform, _position);
		_transform = glm::rotate(_transform, glm::radians(_rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		_transform = glm::scale(_transform, _scale);
		_transformDirty = false;
	}
}




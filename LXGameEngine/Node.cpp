#include "stdafx.h"
#include "Node.h"
#include <glm/mat4x4.hpp>


Node::Node():
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
}

void Node::visit(glm::mat4 & parentTransform)
{
	_modelTransform = parentTransform * _transform;
	for (auto child : _children) {
		child->visit(_modelTransform);
	}
	draw();
}

void Node::draw()
{
}

#include "stdafx.h"
#include "Node.h"
#include <glm/mat4x4.hpp>


Node::Node()
{
}


Node::~Node()
{
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

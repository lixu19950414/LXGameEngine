#include "stdafx.h"
#include "Node.h"


Node::Node():
_position(0.0f, 0.0f, 0.0f),
_rotation(0.0f),
_scale(1.0f, 1.0f, 1.0f),
_transformDirty(false),
_parent(nullptr),
_vao(0),
_vbo(0),
_ebo(0),
_needSortChildren(false),
_localZ(0),
_contentSize(0.0f, 0.0f),
_anchorPoint(0.0f, 0.0f),
_opacity(255)
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
	sortChildren();
	updateTransform();
	_modelTransform = parentTransform * _transform;
	auto start = _children.begin();
	// visit nodes with z < 0
	for (; start != _children.end(); ++start) {
		if ((*start)->getLocalZ() < 0) {
			(*start)->visit(_modelTransform);
		}
		else{
			break;
		}
	}
	draw();
	// visit nodes with z >= 0
	for (; start != _children.end(); ++start) {
		(*start)->visit(_modelTransform);
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

void Node::setLocalZ(short localZ)
{
	_localZ = localZ;
	if (_parent != nullptr) {
		_parent->setNeedSortChildren();
	}
}

bool sortChildrenFunc(Node* i, Node* j)
{
	return i->getLocalZ() < j->getLocalZ();
}

void Node::sortChildren()
{
	std::sort(_children.begin(), _children.end(), sortChildrenFunc);
}

void Node::setContentSize(GLfloat width, GLfloat height)
{
	_contentSize = glm::vec2(width, height);
}

void Node::setAnchorPoint(GLfloat x, GLfloat y)
{
	_anchorPoint = glm::vec2(x, y);
}

void Node::setOpacity(GLubyte opacity)
{
	_opacity = opacity;
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




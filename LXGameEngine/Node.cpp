#include "stdafx.h"
#include "Node.h"


Node::Node() :
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
	_opacity(255),
	_aabb(),
	_swallowTouches(false)
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
	updateAABB();
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
	_aabbDirty = true;
}

void Node::setScale(GLfloat scaleX, GLfloat scaleY)
{
	_scale = glm::vec3(scaleX, scaleY, 1.0f);
	_transformDirty = true;
	_aabbDirty = true;
}

void Node::setRotation(GLfloat rotate)
{
	_rotation = rotate;
	_transformDirty = true;
	_aabbDirty = true;
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
	_aabbDirty = true;
}

void Node::setAnchorPoint(GLfloat x, GLfloat y)
{
	_anchorPoint = glm::vec2(x, y);
	_aabbDirty = true;
}

void Node::setOpacity(GLubyte opacity)
{
	_opacity = opacity;
}

bool Node::touch(int x, int y)
{
	int index = _children.size() - 1;
	for (; index >= 0; index--) {
		auto it = _children.at(index);
		if (it->getLocalZ() >= 0) {
			if (it->touch(x, y))
			{
				return true;
			}
		}
		else{
			break;
		}
	}
	bool ret = onTouch(x, y);
	if (ret) {
		return true;
	}
	for (; index >= 0; index--) {
		auto it = _children.at(index);
		if (it->touch(x, y))
		{
			return true;
		}
	}
	return false;
}

bool Node::onTouch(int x, int y)
{
	if (_aabb.containPoint(x, y)) {
		handleTouch(x, y);
		if (_swallowTouches)
			return true;
	}
	return false;
}

void Node::handleTouch(int x, int y)
{
	// LX_LOG("touch %d, %d\n", x, y);
}

glm::vec2 Node::convertToNodeSpace(int x, int y)
{
	glm::mat4 im = glm::inverse(_modelTransform);
	glm::vec4 position = im * (glm::vec4((float)x, (float)y, 0.0f, 1.0f));
	return glm::vec2(position);
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

void Node::updateAABB()
{
	if (true) {
		GLfloat width = _contentSize.x;
		GLfloat height = _contentSize.y;

		GLfloat anchorX = _anchorPoint.x;
		GLfloat anchorY = _anchorPoint.y;

		GLfloat offSetX = -(width * anchorX);
		GLfloat offSetY = -(height * anchorY);
		
		glm::vec4 point[4];
		point[0] = _modelTransform * glm::vec4(offSetX, offSetY, .0f, 1.0f); // lb
		point[1] = _modelTransform * glm::vec4(offSetX, height + offSetY, .0f, 1.0f); // lt
		point[2] = _modelTransform * glm::vec4(width + offSetX, offSetY, .0f, 1.0f); // rb
		point[3] = _modelTransform * glm::vec4(width + offSetX, height + offSetY, .0f, 1.0f); //rt

		GLfloat minX = point[0].x, minY = point[0].y, maxX = point[0].x, maxY = point[0].y;
		for (int i = 1; i < 4; ++i) {
			if (point[i].x < minX)
				minX = point[i].x;
			if (point[i].y < minY)
				minY = point[i].y;
			if (point[i].x > maxX)
				maxX = point[i].x;
			if (point[i].y > maxY)
				maxY = point[i].y;
		}

		_aabb = AABB(minX, minY, maxX - minX, maxY - minY);
		_aabbDirty = false;
	}
}




#include "stdafx.h"
#include "ScissorNode.h"
#include "Renderer.h"
#include "GLStateBlock.h"


ScissorNode::ScissorNode()
{
}

void ScissorNode::visit(glm::mat4 & parentTransform)
{
	sortChildren();
	updateTransform();
	_modelTransform = parentTransform * _transform;
	updateAABB();

	auto instance = Renderer::getInstance();
	//Copy top stateBlock
	GLStateBlock stateBlock = instance->getStateBlocks().top();
	stateBlock._flagScissorTest = true;
	stateBlock._scissorRect = _aabb;

	instance->getStateBlocks().push(stateBlock);
	instance->applyTopStateBlock();

	auto start = _children.begin();
	// visit nodes with z < 0
	for (; start != _children.end(); ++start) {
		if ((*start)->getLocalZ() < 0) {
			(*start)->visit(_modelTransform);
		}
		else {
			break;
		}
	}
	draw();
	// visit nodes with z >= 0
	for (; start != _children.end(); ++start) {
		(*start)->visit(_modelTransform);
	}

	instance->getStateBlocks().pop();
	instance->applyTopStateBlock();
}


ScissorNode::~ScissorNode()
{
}

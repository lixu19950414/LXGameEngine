#ifndef SCISSOR_NODE_H
#define SCISSOR_NODE_H

#include "Node.h"

class ScissorNode :
	public Node
{
public:
	ScissorNode();
	virtual void visit(glm::mat4& parentTransform) override;
	~ScissorNode();
};

#endif

#ifndef NODE_H
#define NODE_H

#include "Ref.h"
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

class Node : public Ref
{
public:
	Node();
	virtual ~Node();

	/*virtual void visit();
	virtual void draw();*/
protected:
	glm::mat4 _transform;
};

#endif

#ifndef RENDERER_H
#define RENDERER_H

#include <stack>
#include "GLStateBlock.h"

class Renderer
{
public:
	static Renderer* getInstance();
public:
	Renderer();
	~Renderer();
	inline std::stack<GLStateBlock>& getStateBlocks() { return _glStateBlocks; };
	void applyTopStateBlock();
	inline void clearStateBlocks() { _glStateBlocks.empty(); };
	void pushDefault2DStateBlock();
protected:
	std::stack<GLStateBlock> _glStateBlocks;
};


#endif

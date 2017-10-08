#ifndef GL_STATE_BLOCK_H
#define GL_STATE_BLOCK_H

#include "Rect.h"

class GLStateBlock
{
public:
	GLStateBlock();
	~GLStateBlock();
	void apply();
	bool _flagScissorTest;
	Rect _scissorRect;
};

#endif

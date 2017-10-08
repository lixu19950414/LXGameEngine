#include "stdafx.h"
#include "GLStateBlock.h"


GLStateBlock::GLStateBlock():
	_flagScissorTest(false)
{
}


GLStateBlock::~GLStateBlock()
{
}

void GLStateBlock::apply()
{
	if (_flagScissorTest) {
		glEnable(GL_SCISSOR_TEST);
		glScissor(_scissorRect.getOrigin().x, _scissorRect.getOrigin().y, _scissorRect.getSize().x, _scissorRect.getSize().y);
	}
	else {
		glDisable(GL_SCISSOR_TEST);
	}
}

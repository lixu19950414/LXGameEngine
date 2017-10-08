#ifndef RENDER_COMMAND_H
#define RENDER_COMMAND_H

#include "Ref.h"
#include "Shader.h"

enum RenderCommandType {
	TRIANGLES_COMMAND = 0,
	CUSTOM_COMMAND = 1,
};

class RenderCommand :
	public Ref
{
public:
	RenderCommand();
	virtual ~RenderCommand();
protected:
	RenderCommandType _type;
	Shader* _shader;
	GLenum _blendSrc;
	GLenum _blendDst;

};

#endif

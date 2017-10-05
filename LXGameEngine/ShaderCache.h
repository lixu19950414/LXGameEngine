#ifndef SHADER_CACHE_H
#define SHADER_CACHE_H

#include <vector>
#include "Shader.h"


class ShaderCache
{
public:
	static ShaderCache* getInstance();
	enum GLOBAL_SHADERS {
		LX_SHADERS_PVM_DEFAULT = 0,
		LX_SHADERS_PVM_FONT,
		LX_SHADERS_PARTICLE,
	};
	ShaderCache();
	~ShaderCache();
	Shader* getGlobalShader(GLOBAL_SHADERS type);
private:
	std::vector<Shader*> _globalShaders;
};

#endif

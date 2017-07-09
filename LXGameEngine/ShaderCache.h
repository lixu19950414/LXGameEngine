#ifndef SHADER_CACHE_H
#define SHADER_CACHE_H

#include "Shader.h"
#include <vector>

class ShaderCache
{
public:
	static ShaderCache* getInstance();
	enum GLOBAL_SHADERS {
		LX_SHADERS_PVM_DEFAULT = 0,
	};
	ShaderCache();
	~ShaderCache();
	Shader* getGlobalShader(GLOBAL_SHADERS type);
private:
	std::vector<Shader*> _globalShaders;
};

#endif

#include "stdafx.h"
#include "ShaderCache.h"
#include "lx_shaders_pvm_default.frag"
#include "lx_shaders_pvm_default.vert"

ShaderCache* g_ShaderCache = nullptr;

ShaderCache * ShaderCache::getInstance()
{
	if (!g_ShaderCache) {
		g_ShaderCache = new ShaderCache();
	}
	return g_ShaderCache;
}

ShaderCache::ShaderCache()
{
	//Create shaders
	Shader* shaders_pvm_default = new Shader();
	shaders_pvm_default->initWithByteArrays(lx_shaders_pvm_default_vert, lx_shaders_pvm_default_frag);
	_globalShaders.push_back(shaders_pvm_default);
}


ShaderCache::~ShaderCache()
{
	for (auto it: _globalShaders)
	{
		it->clear();
	}
	_globalShaders.clear();
}

Shader * ShaderCache::getGlobalShader(GLOBAL_SHADERS type)
{
	return _globalShaders[type];
}

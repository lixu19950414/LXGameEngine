#include "stdafx.h"
#include "ShaderCache.h"
#include "lx_shaders_pvm_default.frag"
#include "lx_shaders_pvm_default.vert"
#include "lx_shaders_pvm_font.frag"
#include "lx_shaders_pvm_font.vert"

ShaderCache* g_pShaderCache = nullptr;

ShaderCache * ShaderCache::getInstance()
{
	if (!g_pShaderCache) {
		g_pShaderCache = new ShaderCache();
	}
	return g_pShaderCache;
}

ShaderCache::ShaderCache()
{
	//Create shaders
	Shader* shaders_pvm_default = new Shader();
	shaders_pvm_default->initWithByteArrays(lx_shaders_pvm_default_vert, lx_shaders_pvm_default_frag);
	_globalShaders.push_back(shaders_pvm_default);

	Shader* shaders_pvm_font = new Shader();
	shaders_pvm_font->initWithByteArrays(lx_shaders_pvm_font_vert, lx_shaders_pvm_font_frag);
	_globalShaders.push_back(shaders_pvm_font);
	
}


ShaderCache::~ShaderCache()
{
	for (auto it: _globalShaders)
	{
		it->clear();
	}
	_globalShaders.clear();
	g_pShaderCache = nullptr;
}

Shader * ShaderCache::getGlobalShader(GLOBAL_SHADERS type)
{
	return _globalShaders[type];
}

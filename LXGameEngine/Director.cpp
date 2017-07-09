#include "stdafx.h"
#include "Director.h"
#include "AutoReleasePool.h"
#include "ShaderCache.h"
#include <LXFileUtil/LXFileUtil.h>

Director* g_pDirector = nullptr;

Director* Director::getInstance()
{
	if (!g_pDirector)
	{
		g_pDirector = new Director();
	}
	return g_pDirector;
}

Director::Director()
{

}


Director::~Director()
{
}

bool Director::mainLoop()
{
	AutoReleasePool::getInstance()->executeClear();
	return true;
}

bool Director::start()
{
	/*Shader* s = new Shader();
	s->initWithFiles("Res\\Shaders\\default.vert", "Res\\Shaders\\default.frag");
	s->dump();*/

	//glCreateShader(GL_VERTEX_SHADER);
	/*Shader* shader = ShaderCache::getInstance()->getGlobalShader(ShaderCache::LX_SHADERS_PVM_DEFAULT);
	shader->dump();*/
	return true;
}

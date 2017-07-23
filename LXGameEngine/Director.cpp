#include "stdafx.h"
#include "Director.h"
#include "AutoReleasePool.h"
#include <LXFileUtil/LXFileUtil.h>
#include "ShaderCache.h"
#include "Texture2D.h"
#include "Sprite.h"

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
	// glClear(GL_COLOR_BUFFER_BIT);
	
	AutoReleasePool::getInstance()->executeClear();
	return true;
}

bool Director::start()
{
	glClear(GL_COLOR_BUFFER_BIT);
	Sprite* sprite = new (std::nothrow) Sprite();
	sprite->initWithFile("Res/wall.jpg");
	sprite->dump();
	sprite->draw();
	//sprite->autoRelease();
	/*Texture2D* texture = new Texture2D();
	texture->initWithFileName("Res/wall.jpg");
	texture->dump();
	texture->release();

	Texture2D* texture2 = new Texture2D();
	texture2->initWithFileName("Res/wall.jpg");
	texture2->dump();*/

	/*texture->initWithFileName("Res/wall.jpg", Image::IMAGE_RGB);
	texture->dump();*/
	/*Shader* s = new Shader();
	s->initWithFiles("Res\\Shaders\\default.vert", "Res\\Shaders\\default.frag");
	s->dump();*/

	//glCreateShader(GL_VERTEX_SHADER);
	/*Shader* shader = ShaderCache::getInstance()->getGlobalShader(ShaderCache::LX_SHADERS_PVM_DEFAULT);
	shader->dump();*/


	

	return true;
}

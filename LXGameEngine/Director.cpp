#include "stdafx.h"
#include "Director.h"
#include "AutoReleasePool.h"
#include "Scene.h"
#include "Game.h"

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
	glClear(GL_COLOR_BUFFER_BIT);
	Scene::getInstance()->visit();
	AutoReleasePool::getInstance()->executeClear();
	return Game::getInstance()->loop();
}

bool Director::start()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Game::getInstance()->start();
	
	return true;
}


#include "stdafx.h"
#include "Director.h"
#include "AutoReleasePool.h"
#include "Scene.h"
#include "Game.h"
#include "Common.h"
#include "Scheduler.h"

Director* g_pDirector = nullptr;

Director* Director::getInstance()
{
	if (!g_pDirector)
	{
		g_pDirector = new Director();
	}
	return g_pDirector;
}

Director::Director() :
	_FPS(60),
	_SPF(1.0f/60),
	_deltaTime(0.0f)
{
	_lastUpdateTime = std::chrono::steady_clock::now();
}


Director::~Director()
{
}

bool Director::mainLoop()
{
	// Update timer
	calculateDeltaTime();
	Scheduler::getInstance()->update(_deltaTime);

	// Draw scene
	onBeginResetGLState();
	Scene::getInstance()->visit();
	AutoReleasePool::getInstance()->executeClear();
	
	// Game loop
	return Game::getInstance()->loop();
}

bool Director::start()
{
	Game::getInstance()->start();
	
	return true;
}

void Director::onBeginResetGLState()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

float Director::calculateDeltaTime()
{
	auto thisUpdateTime = std::chrono::steady_clock::now();
	float tempTime = std::chrono::duration_cast<std::chrono::duration<float>>(thisUpdateTime - _lastUpdateTime).count();
	_lastUpdateTime = thisUpdateTime;
	_deltaTime = std::max(0.0f, tempTime);
	return _deltaTime;
}


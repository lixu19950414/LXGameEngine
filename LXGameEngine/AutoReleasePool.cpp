#include "stdafx.h"
#include "AutoReleasePool.h"

AutoReleasePool* g_pAutoReleasePool = nullptr;

AutoReleasePool* AutoReleasePool::getInstance()
{
	if (!g_pAutoReleasePool) {
		g_pAutoReleasePool = new AutoReleasePool();
	}
	return g_pAutoReleasePool;
}

AutoReleasePool::AutoReleasePool()
{
	_objToRelease.reserve(256);
}

AutoReleasePool::~AutoReleasePool()
{
	executeClear();
}

void AutoReleasePool::addObject(Ref * obj)
{
	_objToRelease.push_back(obj);
}

void AutoReleasePool::executeClear()
{
	for (auto it : _objToRelease) {
		it->release();
	}
	_objToRelease.clear();
}


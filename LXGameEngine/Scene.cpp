#include "stdafx.h"
#include "Scene.h"
#include "Director.h"

Scene* g_Scene = nullptr;

Scene::Scene()
{
}

Scene * Scene::getInstance()
{
	if (g_Scene == nullptr) {
		g_Scene = new (std::nothrow) Scene;
	}
	return g_Scene;
}

void Scene::visit()
{
	Node::visit(_transform);
}


Scene::~Scene()
{
}

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

std::vector<Node*> Scene::getTouchEventNodes()
{
	return _touchEventNodes;
}


void Scene::pushTouchEventNode(Node * node)
{
	node->retain();
	_touchEventNodes.push_back(node);
}

void Scene::clearTouchEventNodes()
{
	for (auto it : _touchEventNodes) {
		it->release();
	}
	_touchEventNodes.clear();
}

Scene::~Scene()
{
}

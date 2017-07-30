#ifndef SCENE_H
#define SCENE_H

#include "Node.h"
class Scene :
	public Node
{
public:
	Scene();
	static Scene* getInstance();
	void visit();
	~Scene();
};

#endif


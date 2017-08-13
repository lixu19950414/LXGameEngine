#ifndef SCENE_H
#define SCENE_H

#include "Node.h"
class Scene :
	public Node
{
public:
	Scene();
	~Scene();

	static Scene* getInstance();
	void visit();

	std::vector<Node*> getTouchEventNodes();
	void pushTouchEventNode(Node* node);
	void clearTouchEventNodes();

private:
	std::vector<Node*> _touchEventNodes;
};

#endif


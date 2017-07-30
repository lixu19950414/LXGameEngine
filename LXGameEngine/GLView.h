#ifndef GLVIEW_H
#define GLVIEW_H

#include "Ref.h"
class GLView :
	public Ref
{
public:
	static GLView* getInstance();
	inline GLFWwindow* getWindow() { return _window; };
	GLView();
	~GLView();
private:
	GLFWwindow* _window;
};

#endif


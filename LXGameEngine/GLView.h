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

	static void GLView::cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
private:
	GLFWwindow* _window;
};

#endif


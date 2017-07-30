#include "stdafx.h"
#include "GLView.h"
#include "Director.h"

GLView *g_GLView = nullptr;

GLView * GLView::getInstance()
{
	if (g_GLView == nullptr) {
		g_GLView = new (std::nothrow) GLView();
	}
	return g_GLView;
}

GLView::GLView():
_window(nullptr)
{
	LX_FU::INI::IniConfig config;
	config.loadFromFile("PlatformConfig.ini");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLuint winWidth = atoi(config.getConf("winwidth").c_str());
	GLuint winHeight = atoi(config.getConf("winheight").c_str());
	
	_window = glfwCreateWindow(winWidth, winHeight, config.getConf("wintitle").c_str(), NULL, NULL);
	
	//Setup callbakcs
	glfwSetMouseButtonCallback(_window, GLView::mouse_button_callback);
	glfwSetKeyCallback(_window, GLView::key_callback);
	glfwSetCursorPosCallback(_window, GLView::cursor_position_callback);
}

void GLView::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	int x = (int)xpos;
	int y = Director::getInstance()->getWinHeight() - (int)ypos;
	LX_LOG("Mouse move: %d, %d\n", x, y);
}

void GLView::mouse_button_callback(GLFWwindow * window, int button, int action, int mods)
{
	// GLFW_PRESS or GLFW_RELEASE 
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		int x = (int)xpos;
		int y = Director::getInstance()->getWinHeight() - (int)ypos;
		LX_LOG("Press mouse left: %d, %d\n", x, y);
	}
}


void GLView::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_UNKNOWN)
		return;

	// GLFW_PRESS, GLFW_REPEAT or GLFW_RELEASE
	if (key == GLFW_KEY_E && action == GLFW_PRESS) {

	}
		
}


GLView::~GLView()
{
	glfwDestroyWindow(_window);
}

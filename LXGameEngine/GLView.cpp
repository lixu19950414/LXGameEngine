#include "stdafx.h"
#include "GLView.h"
#include "Director.h"
#include "Camera.h"
#include "Scene.h"

GLView *g_pGLView = nullptr;
GLenum g_MouseState[GLFW_MOUSE_BUTTON_LAST];

GLView * GLView::getInstance()
{
	if (g_pGLView == nullptr) {
		g_pGLView = new (std::nothrow) GLView();
	}
	return g_pGLView;
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

	//Init states
	memset(g_MouseState, 0, GLFW_MOUSE_BUTTON_LAST * sizeof(GLenum));
	
	//Setup callbakcs
	glfwSetMouseButtonCallback(_window, GLView::mouse_button_callback);
	glfwSetKeyCallback(_window, GLView::key_callback);
	glfwSetCursorPosCallback(_window, GLView::cursor_position_callback);
}

void GLView::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	int x = (int)xpos;
	int y = Director::getInstance()->getWinHeight() - (int)ypos;
	if (g_MouseState[GLFW_MOUSE_BUTTON_LEFT] == GLFW_PRESS) {
		auto scene = Scene::getInstance();
		for (auto it : scene->getTouchEventNodes()) {
			it->onTouchMove(x, y);
		}
	}
}

void GLView::mouse_button_callback(GLFWwindow * window, int button, int action, int mods)
{
	g_MouseState[button] = action;

	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	int x = (int)xpos;
	int y = Director::getInstance()->getWinHeight() - (int)ypos;

	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		if (action == GLFW_PRESS) {
			//glm::vec4 pos = glm::inverse(Camera::getInstance()->getViewMatrix()) * glm::vec4(x, y, 0.0f, 1.0f);
			//LX_LOG("Press mouse left: %d, %d\n", x, y);
			auto scene = Scene::getInstance();
			scene->clearTouchEventNodes();
			scene->touch(x, y);
			// LX_LOG("Press mouse leftwithview: %d, %d\n", pos.x, pos.y);
		}
		else if(action == GLFW_RELEASE) {
			auto scene = Scene::getInstance();
			for (auto it : scene->getTouchEventNodes()) {
				it->onTouchEnd(x, y);
			}
			scene->clearTouchEventNodes();
		}
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

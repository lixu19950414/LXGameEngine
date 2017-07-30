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
}


GLView::~GLView()
{
	glfwDestroyWindow(_window);
}

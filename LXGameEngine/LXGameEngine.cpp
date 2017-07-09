// LXGameEngine.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "LXGameEngine.h"
#include "Director.h"



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
	
	// Init console
	if (AllocConsole())
	{
		freopen("CONOUT$", "w", stdout);
		freopen("CONOUT$", "w", stderr);
	}

	// Init paths
	LX_FU::setPathPrefix("C:\\Projects\\LXGameEngine\\LXGameEngine\\Resources");
	LX_FU::INI::IniConfig config;
	config.loadFromFile("PlatformConfig.ini");

	GLFWwindow* window;

	if (!glfwInit())
		exit(EXIT_FAILURE);	

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	
	window = glfwCreateWindow(atoi(config.getConf("winwidth").c_str()), atoi(config.getConf("winheight").c_str()), config.getConf("wintitle").c_str(), NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glClearColor(.0f, .0f, .0f, 1.0f);
	
	//GLEW初始化需要放到初始化GL上下文之后！！！
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		LX_LOG("GLEW Error: %s\n", glewGetErrorString(err));
		exit(EXIT_FAILURE);
	}

	if (!Director::getInstance()->start())
	{
		exit(EXIT_FAILURE);
	}

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);
		if (!Director::getInstance()->mainLoop()) {
			break;
		}
		glfwSwapBuffers(window);

		Sleep(1);
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);

    return 0;
}

// LXGameEngine.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "LXGameEngine.h"
#include "Director.h"
#include "GLView.h"



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

	if (!glfwInit())
		exit(EXIT_FAILURE);	

	GLFWwindow* window = GLView::getInstance()->getWindow();

	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	
	//GLEW初始化需要放到初始化GL上下文之后！！！
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		LX_LOG("GLEW Error: %s\n", glewGetErrorString(err));
		exit(EXIT_FAILURE);
	}

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	Director::getInstance()->setWinWidth(width);
	Director::getInstance()->setWinHeight(height);

	glClearColor(.0f, .0f, .0f, 1.0f);

	if (!Director::getInstance()->start())
	{
		exit(EXIT_FAILURE);
	}

	auto lastUpdateTime = std::chrono::steady_clock::now();

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		if (!Director::getInstance()->mainLoop()) {
			break;
		}
		glfwSwapBuffers(window);

		// calculate time
		float spf = Director::getInstance()->getSPF();

		auto thisUpdateTime = std::chrono::steady_clock::now();
		double timeExpend = std::chrono::duration_cast<std::chrono::duration<float>>(thisUpdateTime - lastUpdateTime).count();
		while (timeExpend < spf - 0.001) {
			Sleep(1);
			thisUpdateTime = std::chrono::steady_clock::now();
			timeExpend = std::chrono::duration_cast<std::chrono::duration<float>>(thisUpdateTime - lastUpdateTime).count();
		}
		// LX_LOG("frame time: %f\n", timeExpend);
		lastUpdateTime = thisUpdateTime;
	}

	GLView::getInstance()->release();

	glfwTerminate();
	exit(EXIT_SUCCESS);

    return 0;
}

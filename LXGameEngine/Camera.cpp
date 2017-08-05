#include "stdafx.h"
#include "Camera.h"
#include "Director.h"

Camera * g_pCamera = nullptr;

Camera * Camera::getInstance()
{
	if (g_pCamera == nullptr) {
		g_pCamera = new Camera();
	}
	return g_pCamera;
}

Camera::Camera()
{
	_viewMatrix = glm::lookAt(glm::vec3(.0f, .0f, 1.0f), glm::vec3(.0f, .0f, .0f), glm::vec3(.0f, 1.0f, .0f));
	auto instance = Director::getInstance();
	_projectionMatrix = glm::ortho(.0f, (float)instance->getWinWidth(), .0f, (float)instance->getWinHeight(), -1.0f, 1.0f);
}


Camera::~Camera()
{
}

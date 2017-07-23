#ifndef CAMERA_H
#define CAMERA_H

class Camera
{
public:
	Camera();
	~Camera();
	static Camera* getInstance();
	inline glm::mat4& getProjectionMatrix() { return _projectionMatrix; };
	inline glm::mat4& getViewMatrix() { return _viewMatrix; };
private:
	glm::mat4 _projectionMatrix;
	glm::mat4 _viewMatrix;
};

#endif

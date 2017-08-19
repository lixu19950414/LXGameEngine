#ifndef DIRECTOR_H
#define DIRECOTR_H

class Director
{
public:
	static Director* getInstance();

	Director();
	~Director();

	bool mainLoop();
	bool start();
	inline void setWinWidth(GLuint winWidth) { _winWidth = winWidth; };
	inline GLuint getWinWidth() { return _winWidth; };
	inline void setWinHeight(GLuint winHeight) { _winHeight = winHeight; };
	inline GLuint getWinHeight() { return _winHeight; };

	inline void setFPS(int FPS) {_FPS = FPS; _SPF = 1.0f / FPS;};
	int getFPS() {return _FPS;};
	inline float getSPF() { return _SPF; };

	void onBeginResetGLState();
	float calculateDeltaTime();
	inline float getDeltaTime() { return _deltaTime; };

private:
	GLuint _winWidth;
	GLuint _winHeight;
	int _FPS;
	float _SPF;
	std::chrono::steady_clock::time_point _lastUpdateTime;
	float _deltaTime;
};

#endif

#ifndef DIRECTOR_H
#define DIRECOTR_H

#include "PolygonInfo.h"
#include "ShaderCache.h"

#define LX_INCREASE_DRAW_CALL(drawCall) Director::getInstance()->addDrawCallsCount(drawCall);
#define LX_INCREASE_VERTS(verts) Director::getInstance()->addVertsCount(verts);

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

	//Debug methods
	void setDisplayLinkStatus(bool show) { _displayLinkStatus = show; };
	inline void addDrawCallsCount(int drawCalls) { _drawCallsCount += drawCalls; };
	inline void addVertsCount(int vertsCount) { _vertsCount += vertsCount; };
	inline void clearDisplayCounts() { _drawCallsCount = 0; _vertsCount = 0; };
	void drawDisplayStatus();

private:
	GLuint _winWidth;
	GLuint _winHeight;
	int _FPS;
	float _SPF;
	std::chrono::steady_clock::time_point _lastUpdateTime;
	float _deltaTime;

	//Debug attributes
	bool _displayLinkStatus;
	int _drawCallsCount;
	int _vertsCount;
	GLuint _vao;
	GLuint _vbo;
	GLuint _ebo;
	PolygonInfo _polyInfo;
	Shader* _shader;
};

#endif

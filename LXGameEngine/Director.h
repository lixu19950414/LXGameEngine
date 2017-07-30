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

private:
	GLuint _winWidth;
	GLuint _winHeight;
};

#endif

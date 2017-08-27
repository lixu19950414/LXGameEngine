#ifndef TEXTURE_GRID_H
#define TEXTURE_GRID_H

#include <vector>
#include "Ref.h"

typedef struct GridPoint {
	GridPoint(unsigned char x, unsigned char y) {
		_x = x;
		_y = y;
	}

	unsigned char _x;
	unsigned char _y;
	
} GridPoint;

const GridPoint GRID_POINT_INVALID = GridPoint(255, 255);

class TextureGrid :
	public Ref
{
public:
	TextureGrid();
	bool initWithGridPixelSize(GLint pixelWidth, GLint pixelHeight, unsigned short partPixelWidth, unsigned short partPixelHeight, GLenum internalFormat=GL_RGBA);
	bool initWithGridCount(GLint pixelWidth, GLint pixelHeight, unsigned char xPartCnt, unsigned char yPartCnt, GLenum internalFormat=GL_RGBA);
	void bind();
	void dump();
	~TextureGrid();

	// Getter
	inline int getXPartCount() { return _xPartCount; };
	inline int getYPartCount() { return _yPartCount; };
	inline int getPartPixelWidth() { return _partPixelWidth; };
	inline int getPartPixelHeight() { return _partPixelHeight; };
	inline int getPixelWidth() { return _pixelWidth; };
	inline int getPixelHeight() { return _pixelHeight; };
	inline GLenum getGLTextureInternalFormat() { return _glTextureInternalFormat; };
	inline GLuint getName() { return _name; };
	inline int getFreeGridsCount() { return _freeGrids.size(); };
	inline int getUsedGridsCount() { return _xPartCount * _yPartCount - _freeGrids.size(); };

public:
	void pushOneFreeGridPoint(const GridPoint& gridPoint);
	const GridPoint& autoFitAndGetGridPoint(int pixelWidth, int pixelHeight, GLenum dataType, GLvoid* data);
	inline bool isInvalidGridPoint(const GridPoint& gridPoint) { return gridPoint._x==255 && gridPoint._y==255; };

private:
	void createFreeGrids();
	bool createTexture();

private:
	// Grid info
	unsigned char _xPartCount;
	unsigned char _yPartCount;
	unsigned short _partPixelWidth;
	unsigned short _partPixelHeight;
	
	GLenum _glTextureInternalFormat;
	GLuint _name;
	GLint _pixelWidth;
	GLint _pixelHeight;

	std::vector<GridPoint> _freeGrids;
};

#endif

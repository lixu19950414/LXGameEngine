#include "stdafx.h"
#include "TextureGrid.h"


TextureGrid::TextureGrid():
	_xPartCount(0),
	_yPartCount(0),
	_partPixelWidth(0),
	_partPixelHeight(0),
	_glTextureInternalFormat(GL_RGBA),
	_name(0),
	_pixelWidth(0),
	_pixelHeight(0)
{
}

bool TextureGrid::initWithGridPixelSize(GLint pixelWidth, GLint pixelHeight, unsigned short partPixelWidth, unsigned short partPixelHeight, GLenum internalFormat)
{
	_pixelWidth = pixelWidth;
	_pixelHeight = pixelHeight;
	_partPixelWidth = partPixelWidth;
	_partPixelHeight = partPixelHeight;
	_glTextureInternalFormat = internalFormat;

	_xPartCount = pixelWidth / partPixelWidth;
	_yPartCount = pixelHeight / partPixelHeight;

	createFreeGrids();
	return createTexture();
}

bool TextureGrid::initWithGridCount(GLint pixelWidth, GLint pixelHeight, unsigned char xPartCnt, unsigned char yPartCnt, GLenum internalFormat)
{
	_pixelWidth = pixelWidth;
	_pixelHeight = pixelHeight;
	_xPartCount = xPartCnt;
	_yPartCount = yPartCnt;
	_glTextureInternalFormat = internalFormat;

	_partPixelWidth = pixelWidth / xPartCnt;
	_partPixelHeight = pixelHeight / yPartCnt;

	createFreeGrids();
	return createTexture();
}


void TextureGrid::bind()
{
	glBindTexture(GL_TEXTURE_2D, _name);
}

void TextureGrid::dump()
{
	LX_LOG("TextureGrid::dump\n");
	LX_LOG("pixelWidth&Height: %d * %d\n", _pixelWidth, _pixelHeight);
	LX_LOG("partWidth&Height: %d * %d\n", _partPixelWidth, _partPixelHeight);
	LX_LOG("partCount: %d * %d\n", _xPartCount, _yPartCount);
}

TextureGrid::~TextureGrid()
{
	if (_name != 0) {
		glDeleteTextures(1, &_name);
	}
	_freeGrids.clear();
}

void TextureGrid::pushOneFreeGridPoint(const GridPoint & gridPoint)
{
	_freeGrids.push_back(gridPoint);
}

const GridPoint & TextureGrid::autoFitAndGetGridPoint(int pixelWidth, int pixelHeight, GLenum dataType, GLvoid* data)
{
	if (_freeGrids.size() > 0 && pixelWidth <= _partPixelWidth && pixelHeight <= _partPixelHeight) {
		GridPoint& gp = _freeGrids.back();
		_freeGrids.pop_back();
		glBindTexture(GL_TEXTURE_2D, _name);
		//LX_LOG("glTexSubImage2D %d %d, %d, %d, %d %d\n", _name, gp._x * _partPixelWidth, gp._y * _partPixelHeight, pixelWidth, pixelHeight, strlen((const char*)data));
		glTexSubImage2D(GL_TEXTURE_2D, 0, gp._x * _partPixelWidth, _pixelHeight - gp._y * _partPixelHeight - pixelHeight, pixelWidth, pixelHeight, _glTextureInternalFormat, dataType, data);
		//glTexSubImage2D(GL_TEXTURE_2D, 0, gp._x * _partPixelWidth, gp._y * _partPixelHeight, pixelWidth, pixelHeight, _glTextureInternalFormat, dataType, data);
		//glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, pixelWidth, pixelHeight, _glTextureInternalFormat, dataType, data);
		
		// std::cout << data << std::endl;
		glBindTexture(GL_TEXTURE_2D, 0);
		return gp;
	}
	else {
		return GRID_POINT_INVALID;
	}
}

void TextureGrid::createFreeGrids()
{
	for (int i = 0; i < _xPartCount; ++i) {
		for (int j = 0; j < _yPartCount; ++j) {
			_freeGrids.push_back(GridPoint(i, j));
		}
	}
}

bool TextureGrid::createTexture()
{
	glGenTextures(1, &_name);
	if (_name == 0) {
		return false;
	}
	// 绑定当前的纹理
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, _name);
	glTexImage2D(GL_TEXTURE_2D, 0, _glTextureInternalFormat, _pixelWidth, _pixelHeight, 0, _glTextureInternalFormat, GL_UNSIGNED_BYTE, NULL);
	// 设置纹理环绕
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// 设置纹理过滤
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	return true;
}

//bool TextureGrid::isValidGridPoint(const GridPoint & gridPoint)
//{
//	return (gridPoint._x < _xPartCount && gridPoint._y < _yPartCount);
//}

#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include "Ref.h"
#include "Image.h"
class Texture2D :
	public Ref
{
public:
	Texture2D();
	~Texture2D();
	bool initWithFileName(const std::string& filename, Image::ImageDataType type = Image::IMAGE_RGBA);
	bool initWithImage(Image* image);
	inline GLuint getName() { return _name; };
	inline GLint getPixelWidth() { return _pixelWidth; };
	inline GLint getPixelHeight() { return _pixelHeight; };
	inline Image::ImageDataType getDataType() { return _dataType; };
	void dump();
private:
	void releaseCurrentTexture();
private:
	GLuint _name;
	GLint _pixelWidth;
	GLint _pixelHeight;
	Image::ImageDataType _dataType;
};

#endif

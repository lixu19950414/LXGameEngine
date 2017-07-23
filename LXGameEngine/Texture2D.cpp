#include "stdafx.h"
#include "Texture2D.h"


Texture2D::Texture2D() :
_name(0),
_pixelWidth(0),
_pixelHeight(0),
_dataType(Image::IMAGE_DEFAULT)
{
}


Texture2D::~Texture2D()
{
	releaseCurrentTexture();
}

bool Texture2D::initWithFileName(const std::string & filename, Image::ImageDataType type)
{
	Image* image = new (std::nothrow) Image(filename, type);
	bool ret = initWithImage(image);
	delete image;
	return ret;
}

bool Texture2D::initWithImage(Image * image)
{
	if (image && image->getLoadSuccess()) {
		releaseCurrentTexture();
		glGenTextures(1, &_name);
		if (_name == 0) {
			return false;
		}
		// 绑定当前的纹理
		glBindTexture(GL_TEXTURE_2D, _name);
		switch (image->getDataType())
		{
		case Image::IMAGE_RGBA:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->getWidth(), image->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image->getData());
			break;
		case Image::IMAGE_RGB:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->getWidth(), image->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, image->getData());
			break;
		default:
			releaseCurrentTexture();
			_name = 0;
			return false;
			break;
		}
		_pixelWidth = image->getWidth();
		_pixelHeight = image->getHeight();
		_dataType = image->getDataType();
		glGenerateMipmap(GL_TEXTURE_2D);
		// 设置纹理环绕
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// 设置纹理过滤
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
		return true;
	}
	return false;
}

void Texture2D::bind()
{
	glBindTexture(GL_TEXTURE_2D, _name);
}

void Texture2D::dump()
{
	LX_LOG("Texture2D::texture name: %d\n", _name);
	LX_LOG("pixelwidth: %d\n", _pixelWidth);
	LX_LOG("pixelheight: %d\n", _pixelWidth);
	LX_LOG("dataType: %d\n", _dataType);
}

void Texture2D::releaseCurrentTexture()
{
	if(_name != 0){
		glDeleteTextures(1, &_name);
		_name = 0;
		_pixelWidth = 0;
		_pixelHeight = 0;
		_dataType = Image::IMAGE_DEFAULT;
	}
}

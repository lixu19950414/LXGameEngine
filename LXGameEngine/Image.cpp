#include "stdafx.h"
#include "Image.h"
#include "Common.h"


unsigned char WHITE_2X2_IMAGE_DATA[4] = {0xff, 0xff, 0xff, 0xff};
std::string WHITE_2X2_IMAGE_NAME = "white_2x2_image";

Image::Image(const std::string& imageName, ImageDataType type) :
_loadSuccess(false),
_imageData(nullptr),
_width(0),
_height(0),
_imageName(imageName),
_type(type)
{
	switch (type)
	{
	case Image::IMAGE_RGBA:
		_imageData = SOIL_load_image(LX_FU::getAbsolutePath(imageName).c_str(), &_width, &_height, 0, SOIL_LOAD_RGBA);
		break;
	case Image::IMAGE_RGB:
		_imageData = SOIL_load_image(LX_FU::getAbsolutePath(imageName).c_str(), &_width, &_height, 0, SOIL_LOAD_RGB);
		break;
	default:
		break;
	}
	if (_imageData) {
		_loadSuccess = true;
		return;
	}
	_imageData = WHITE_2X2_IMAGE_DATA;
	_width = 2;
	_height = 2;
	_imageName = WHITE_2X2_IMAGE_NAME;
	_type = Image::IMAGE_RGBA;
}

Image::~Image()
{
	if (_loadSuccess) {
		SOIL_free_image_data(_imageData);
		_imageData = nullptr;
	}
}

void Image::dump()
{
	LX_LOG("width: %d, height: %d", _width, _height);
}


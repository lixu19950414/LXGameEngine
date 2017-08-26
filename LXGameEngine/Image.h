#ifndef IMAGE_H
#define IMAGE_H

#include <string>

class Image
{

public:
	typedef enum ImageDataType
	{
		IMAGE_DEFAULT = 0,
		IMAGE_RGBA,
		IMAGE_RGB,

	}ImageDataType;

	Image(std::string imageName, ImageDataType type=IMAGE_RGBA);
	~Image();

	inline unsigned char *getData() { return _imageData; };
	inline int getWidth() { return _width; };
	inline int getHeight() { return _height; };
	inline bool getLoadSuccess() { return _loadSuccess; };
	inline ImageDataType getDataType() { return _type; };
	void dump();

private:
	int _width;
	int _height;
	ImageDataType _type;
	bool _loadSuccess;
	unsigned char* _imageData;
	std::string _imageName;
};

#endif


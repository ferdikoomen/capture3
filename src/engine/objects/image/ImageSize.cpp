#include "ImageSize.h"


namespace Capture3
{

	ImageSize::ImageSize(const unsigned int width, const unsigned int height) :
		size(width, height),
		width(width),
		height(height),
		area(width * height),
		bytes(area * 3)
	{
		//
	}


	ImageSize::~ImageSize()
	{
		//
	}


	const cv::Size &ImageSize::getSize() const
	{
		return size;
	}


	const unsigned int ImageSize::getWidth() const
	{
		return width;
	}


	const unsigned int ImageSize::getHeight() const
	{
		return height;
	}


	const unsigned int ImageSize::getArea() const
	{
		return area;
	}


	const unsigned int ImageSize::getBytes() const
	{
		return bytes;
	}

}
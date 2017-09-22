#include "ImageChannel.h"


namespace Capture3
{

	ImageChannel::ImageChannel(const ImageSize &size) :
		size(size),
		mat(size.getSize(), CV_64FC3, cv::Scalar(0)),
		data((double *) mat.data)
	{
		//
	}


	ImageChannel::~ImageChannel()
	{
		data = nullptr;
		mat.release();
	}


	cv::Mat &ImageChannel::getMat()
	{
		return mat;
	}


	const cv::Mat &ImageChannel::getMat() const
	{
		return mat;
	}


	double *ImageChannel::getData()
	{
		return data;
	}


	const double *ImageChannel::getData() const
	{
		return data;
	}


	const ImageSize &ImageChannel::getSize() const
	{
		return size;
	}


}
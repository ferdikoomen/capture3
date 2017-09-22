#ifndef CAPTURE3_IMAGE_DATA_H
#define CAPTURE3_IMAGE_DATA_H


#include <opencv2/core.hpp>


#include "ImageSize.h"


namespace Capture3
{
	class ImageChannel final
	{

		public:
			ImageChannel(const ImageSize &size);

			virtual ~ImageChannel();

			cv::Mat &getMat();

			const cv::Mat &getMat() const;

			double *getData();

			const double *getData() const;

			const ImageSize &getSize() const;

		private:
			const ImageSize &size;
			cv::Mat mat;
			double *data;
	};
}

#endif // CAPTURE3_IMAGE_DATA_H

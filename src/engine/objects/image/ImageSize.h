#ifndef CAPTURE3_IMAGE_SIZE_H
#define CAPTURE3_IMAGE_SIZE_H


#include <opencv2/core.hpp>


namespace Capture3
{

	class ImageSize final
	{

		public:
			ImageSize(const unsigned int width, const unsigned int height);

			virtual ~ImageSize();

			const cv::Size &getSize() const;

			const unsigned int getWidth() const;

			const unsigned int getHeight() const;

			const unsigned int getArea() const;

			const unsigned int getBytes() const;

		private:
			const cv::Size size;
			const unsigned int width;
			const unsigned int height;
			const unsigned int area;
			const unsigned int bytes;
	};
}

#endif // CAPTURE3_IMAGE_SIZE_H

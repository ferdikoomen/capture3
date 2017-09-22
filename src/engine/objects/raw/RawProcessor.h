#ifndef CAPTURE3_RAW_PROCESSOR_H
#define CAPTURE3_RAW_PROCESSOR_H


#include <vector>
#include <cmath>
#include <omp.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <libraw/libraw.h>
#include <libraw/libraw_types.h>
#include <QtCore/QString>
#include <QtCore/QHash>


#include "RawFile.h"
#include "../../objects/image/Image.h"
#include "../../../engine/objects/image/ImageChannel.h"
#include "../../../constants/CameraConstants.h"
#include "../../../utils/ArrayUtils.h"


namespace Capture3
{
	class RawProcessor final
	{

		public:
			RawProcessor();

			virtual ~RawProcessor();

			void add(
				const unsigned int indexFocus,
				const unsigned int indexExposure,
				const unsigned int indexShot,
				RawFile *file
			);

			Image *process(
				const unsigned int mergeShots,
				const unsigned int mergeRange
			);

		private:
			void openImages(
				std::vector<cv::Mat> &images,
				const unsigned int mergeShots,
				const unsigned int mergeRange
			);

			cv::Mat mergeImages(std::vector<cv::Mat> &images, const unsigned int type);

			void alignImages(std::vector<cv::Mat> &images);

			Image *stackImages(std::vector<cv::Mat> &images);

			LibRaw processor;
			std::vector<std::vector<std::vector<RawFile *>>> files;
			unsigned int outputWidth;
			unsigned int outputHeight;
			unsigned int outputArea;
			cv::Size outputSize;
	};
}

#endif // CAPTURE3_RAW_PROCESSOR_H

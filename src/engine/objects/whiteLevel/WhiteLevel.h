#ifndef CAPTURE3_WHITE_LEVEL_H
#define CAPTURE3_WHITE_LEVEL_H


#include <vector>
#include <omp.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>


#include "../image/Image.h"
#include "../image/ImageChannel.h"
#include "../image/ImageSize.h"


namespace Capture3
{

	class WhiteLevel final
	{

		public:
			WhiteLevel(const Image *image);

			virtual ~WhiteLevel();

			void apply(Image *image);

		private:
			const unsigned int width;
			const unsigned int height;
			const unsigned int area;
			cv::Mat white;
			double *whiteData;
			double whiteLevelMinR;
			double whiteLevelMinG;
			double whiteLevelMinB;
			double whiteLevelMin;
			double whiteLevelMaxR;
			double whiteLevelMaxG;
			double whiteLevelMaxB;
			double whiteLevelMax;
			double whiteLevelR;
			double whiteLevelG;
			double whiteLevelB;
			double whiteLevel;
			double whiteLevelNormR;
			double whiteLevelNormG;
			double whiteLevelNormB;
	};
}

#endif // CAPTURE3_WHITE_LEVEL_H

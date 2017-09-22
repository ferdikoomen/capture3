#ifndef CAPTURE3_IMAGE_HISTOGRAM_UTILS_H
#define CAPTURE3_IMAGE_HISTOGRAM_UTILS_H


#include <cmath>
#include <vector>
#include <omp.h>
#include <QtGui/QImage>


#include "../engine/objects/image/ImageSize.h"
#include "../engine/objects/image/ImageChannel.h"


namespace Capture3
{

	static void generateHistogram(
		const ImageSize &imageSize,
		const ImageChannel &imageChannel,
		QImage &outputX,
		QImage &outputY,
		QImage &outputZ
	)
	{
		// Get image data and size
		const unsigned int imageBytes = imageSize.getBytes();
		const double *imageData = imageChannel.getData();
		const auto outputWidth = (unsigned int) outputX.width();
		const auto outputHeight = (unsigned int) outputX.height();
		unsigned char *outputDataX = outputX.bits();
		unsigned char *outputDataY = outputY.bits();
		unsigned char *outputDataZ = outputZ.bits();

		// Create buckets
		std::vector<unsigned int> bucketsX(outputWidth, 0);
		std::vector<unsigned int> bucketsY(outputWidth, 0);
		std::vector<unsigned int> bucketsZ(outputWidth, 0);
		const unsigned int bucketMax = outputWidth - 1;

		// Get number of pixels in each bucket
		for (unsigned int i = 0; i < imageBytes; i += 3) {

			// Get bucket index
			double valueX = imageData[i + 0];
			double valueY = imageData[i + 1];
			double valueZ = imageData[i + 2];
			valueX = valueX < 0 ? 0 : valueX > 1 ? 1 : valueX;
			valueY = valueY < 0 ? 0 : valueY > 1 ? 1 : valueY;
			valueZ = valueZ < 0 ? 0 : valueZ > 1 ? 1 : valueZ;
			auto bucketX = (unsigned int) lround(valueX * bucketMax);
			auto bucketY = (unsigned int) lround(valueY * bucketMax);
			auto bucketZ = (unsigned int) lround(valueZ * bucketMax);
			bucketX = bucketX > bucketMax ? bucketMax : bucketX;
			bucketY = bucketY > bucketMax ? bucketMax : bucketY;
			bucketZ = bucketZ > bucketMax ? bucketMax : bucketZ;

			// Increment buckets
			bucketsX[bucketX]++;
			bucketsY[bucketY]++;
			bucketsZ[bucketZ]++;
		}

		// Find max value
		double max = 0.0001;
		for (unsigned int i = 0; i < outputWidth; i++) {
			max = bucketsX[i] > max ? bucketsX[i] : max;
			max = bucketsY[i] > max ? bucketsY[i] : max;
			max = bucketsZ[i] > max ? bucketsZ[i] : max;
		}

		// Draw lines
		#pragma omp parallel for schedule(static)
		for (unsigned int x = 0; x < outputWidth; x++) {

			// Fetch and normalize values
			const double valueX = 1.0 - (bucketsX[x] / max);
			const double valueY = 1.0 - (bucketsY[x] / max);
			const double valueZ = 1.0 - (bucketsZ[x] / max);

			// Calculate line height
			const auto heightX = (unsigned int) lround(valueX * outputHeight);
			const auto heightY = (unsigned int) lround(valueY * outputHeight);
			const auto heightZ = (unsigned int) lround(valueZ * outputHeight);

			// Draw lines
			for (unsigned int y = 0; y < outputHeight; y++) {

				// Calculate color
				const auto colorX = (unsigned char) (y < heightX ? 40 : 170);
				const auto colorY = (unsigned char) (y < heightY ? 40 : 170);
				const auto colorZ = (unsigned char) (y < heightZ ? 40 : 170);
				const unsigned int index = (y * outputWidth + x) * 4;

				// Store values
				outputDataX[index + 0] = colorX;
				outputDataX[index + 1] = colorX;
				outputDataX[index + 2] = colorX;
				outputDataX[index + 3] = 255;

				outputDataY[index + 0] = colorY;
				outputDataY[index + 1] = colorY;
				outputDataY[index + 2] = colorY;
				outputDataY[index + 3] = 255;

				outputDataZ[index + 0] = colorZ;
				outputDataZ[index + 1] = colorZ;
				outputDataZ[index + 2] = colorZ;
				outputDataZ[index + 3] = 255;
			}
		}
	}
}


#endif // CAPTURE3_IMAGE_HISTOGRAM_UTILS_H

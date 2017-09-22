#ifndef CAPTURE3_IMAGE_WAVEFORM_UTILS_H
#define CAPTURE3_IMAGE_WAVEFORM_UTILS_H


#include <cmath>
#include <vector>
#include <omp.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <QtGui/QImage>


#include "../engine/objects/image/ImageSize.h"
#include "../engine/objects/image/ImageChannel.h"


namespace Capture3
{


	static void generateWaveform(
		const ImageSize &imageSize,
		const ImageChannel &imageChannel,
		QImage &outputX,
		QImage &outputY,
		QImage &outputZ
	)
	{
		// Get output data
		const auto outputWidth = (unsigned int) outputX.width();
		const auto outputHeight = (unsigned int) outputX.height();
		const unsigned int outputArea = outputWidth * outputHeight;
		const cv::Size outputSize(outputWidth, outputHeight);
		unsigned char *outputDataX = outputX.bits();
		unsigned char *outputDataY = outputY.bits();
		unsigned char *outputDataZ = outputZ.bits();

		// Get image data
		const unsigned int imageWidth = imageSize.getWidth();
		const unsigned int imageHeight = imageSize.getHeight();
		const double *imageData = imageChannel.getData();

		// Create height map
		const unsigned int mapWidth = std::min(imageWidth, outputWidth * 4);
		const unsigned int mapHeight = std::min(imageHeight, outputHeight * 4);
		const unsigned int mapMax = mapHeight - 1;
		const double mapScaleX = imageWidth / (double) mapWidth;
		const double mapScaleY = imageHeight / (double) mapHeight;
		const cv::Size mapSize(mapWidth, mapHeight);
		cv::Mat map(mapSize, CV_64FC3, cv::Scalar(0));
		auto *mapData = (double *) map.data;

		// Iterate over pixels and convert pixel value to position
		#pragma omp parallel for schedule(static)
		for (unsigned int x = 0; x < mapWidth; x++) {
			for (unsigned int y = 0; y < mapHeight; y++) {

				// Calculate position of pixel to sample
				const auto imageX = (unsigned int) lround(x * mapScaleX);
				const auto imageY = (unsigned int) lround(y * mapScaleY);

				// Fetch values from channels
				const unsigned int index = (imageY * imageWidth + imageX) * 3;
				double valueX = 1.0 - imageData[index + 0];
				double valueY = 1.0 - imageData[index + 1];
				double valueZ = 1.0 - imageData[index + 2];
				valueX = valueX < 0 ? 0 : valueX > 1 ? 1 : valueX;
				valueY = valueY < 0 ? 0 : valueY > 1 ? 1 : valueY;
				valueZ = valueZ < 0 ? 0 : valueZ > 1 ? 1 : valueZ;

				// Convert color to height
				const auto heightX = (unsigned int) lround(valueX * mapMax);
				const auto heightY = (unsigned int) lround(valueY * mapMax);
				const auto heightZ = (unsigned int) lround(valueZ * mapMax);

				// Store value
				mapData[(heightX * mapWidth + x) * 3 + 0] += valueX;
				mapData[(heightY * mapWidth + x) * 3 + 1] += valueY;
				mapData[(heightZ * mapWidth + x) * 3 + 2] += valueZ;
			}
		}

		// Scale map to output size
		cv::Mat scaled;
		cv::resize(map, scaled, outputSize, 0, 0, cv::INTER_AREA);
		const double *scaledData = (double *) scaled.data;

		// Find max value
		double maxX = 0.0001;
		double maxY = 0.0001;
		double maxZ = 0.0001;
		for (unsigned int i = 0; i < outputArea; i++) {
			const unsigned int index = i * 3;
			maxX = scaledData[index + 0] > maxX ? scaledData[index + 0] : maxX;
			maxY = scaledData[index + 1] > maxY ? scaledData[index + 1] : maxY;
			maxZ = scaledData[index + 2] > maxZ ? scaledData[index + 2] : maxZ;
		}

		#pragma omp parallel for schedule(static)
		for (unsigned int i = 0; i < outputArea; i++) {

			// Calculate input and output index
			const unsigned int indexInput = i * 3;
			const unsigned int indexOutput = i * 4;

			// Fetch and normalize values
			double valueX = scaledData[indexInput + 0] / maxX;
			double valueY = scaledData[indexInput + 1] / maxY;
			double valueZ = scaledData[indexInput + 2] / maxZ;
			valueX = std::sin(valueX * M_PI_2);
			valueY = std::sin(valueY * M_PI_2);
			valueZ = std::sin(valueZ * M_PI_2);
			valueX = valueX < 0 ? 0 : valueX > 1 ? 1 : valueX;
			valueY = valueY < 0 ? 0 : valueY > 1 ? 1 : valueY;
			valueZ = valueZ < 0 ? 0 : valueZ > 1 ? 1 : valueZ;

			// Calculate output colors
			const auto colorX = (unsigned int) lround((valueX * 130.0) + 40.0);
			const auto colorY = (unsigned int) lround((valueY * 130.0) + 40.0);
			const auto colorZ = (unsigned int) lround((valueZ * 130.0) + 40.0);

			// Store them
			outputDataX[indexOutput + 0] = (unsigned char) colorX;
			outputDataX[indexOutput + 1] = (unsigned char) colorX;
			outputDataX[indexOutput + 2] = (unsigned char) colorX;
			outputDataX[indexOutput + 3] = 255;

			outputDataY[indexOutput + 0] = (unsigned char) colorY;
			outputDataY[indexOutput + 1] = (unsigned char) colorY;
			outputDataY[indexOutput + 2] = (unsigned char) colorY;
			outputDataY[indexOutput + 3] = 255;

			outputDataZ[indexOutput + 0] = (unsigned char) colorZ;
			outputDataZ[indexOutput + 1] = (unsigned char) colorZ;
			outputDataZ[indexOutput + 2] = (unsigned char) colorZ;
			outputDataZ[indexOutput + 3] = 255;
		}

		map.release();
		scaled.release();
	}
}


#endif // CAPTURE3_IMAGE_WAVEFORM_UTILS_H

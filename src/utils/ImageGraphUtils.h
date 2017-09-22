#ifndef CAPTURE3_IMAGE_GRAPH_UTILS_H
#define CAPTURE3_IMAGE_GRAPH_UTILS_H


#include <cmath>
#include <vector>
#include <omp.h>


#include "BoundingBoxUtils.h"
#include "../engine/objects/image/ImageChannel.h"
#include "../engine/objects/image/ImageSize.h"


namespace Capture3
{

	static void generateGraph(
		const ImageSize &imageSize,
		const ImageChannel &imageRGB,
		const ImageChannel &imageHSB,
		const ImageChannel &imageXYZ,
		const ImageChannel &imageXYV,
		const ImageChannel &imageLAB,
		std::vector<float> &positionsRGB,
		std::vector<float> &positionsHSB,
		std::vector<float> &positionsXYZ,
		std::vector<float> &positionsXYV,
		std::vector<float> &positionsLAB,
		std::vector<float> &colors,
		unsigned int &countPoints,
		unsigned int &countLines
	)
	{
		// We want to sample a max of 250000 points
		const unsigned int outputMax = 250000;
		const unsigned int outputArea = imageSize.getArea();
		const unsigned int outputSize = std::min(outputArea, outputMax);
		const double outputScale = outputArea / (double) outputSize;
		const unsigned int outputBytes = (outputSize + 24) * 3;

		// Resize vectors to fit points and bounding box
		positionsRGB.resize(outputBytes);
		positionsHSB.resize(outputBytes);
		positionsXYZ.resize(outputBytes);
		positionsXYV.resize(outputBytes);
		positionsLAB.resize(outputBytes);
		colors.resize(outputBytes);

		// Fetch data pointers
		const double *dataRGB = imageRGB.getData();
		const double *dataHSB = imageHSB.getData();
		const double *dataXYZ = imageXYZ.getData();
		const double *dataXYV = imageXYV.getData();
		const double *dataLAB = imageLAB.getData();

		#pragma omp parallel for schedule(static)
		for (unsigned int i = 0; i < outputSize; i++) {

			// Calculate indexes
			const auto index = (unsigned int) lround(i * outputScale);
			const unsigned int indexInput = index * 3;
			const unsigned int indexOutput = i * 3;

			// Colors
			colors[indexOutput + 0] = (float) dataRGB[indexInput + 0];
			colors[indexOutput + 1] = (float) dataRGB[indexInput + 1];
			colors[indexOutput + 2] = (float) dataRGB[indexInput + 2];

			// RGB
			positionsRGB[indexOutput + 0] = (float) (dataRGB[indexInput + 1] - 0.5);
			positionsRGB[indexOutput + 1] = (float) (dataRGB[indexInput + 2] - 0.5);
			positionsRGB[indexOutput + 2] = (float) (dataRGB[indexInput + 0] - 0.5);

			// HSB:
			const double radians = dataHSB[indexInput + 0] * M_PI * 2.0;
			const double radius = (dataHSB[indexInput + 1] * dataHSB[indexInput + 2]) / 2.0;
			positionsHSB[indexOutput + 0] = (float) (radius * std::cos(radians));
			positionsHSB[indexOutput + 1] = (float) (radius * std::sin(radians));
			positionsHSB[indexOutput + 2] = (float) (dataHSB[indexInput + 2] - 0.5);

			// XYZ:
			positionsXYZ[indexOutput + 0] = (float) (dataXYZ[indexInput + 2] - 0.5);
			positionsXYZ[indexOutput + 1] = (float) (dataXYZ[indexInput + 0] - 0.5);
			positionsXYZ[indexOutput + 2] = (float) (dataXYZ[indexInput + 1] - 0.5);

			// XYV:
			positionsXYV[indexOutput + 0] = (float) (dataXYV[indexInput + 1] - 0.5);
			positionsXYV[indexOutput + 1] = (float) (dataXYV[indexInput + 0] - 0.5);
			positionsXYV[indexOutput + 2] = (float) (dataXYV[indexInput + 2] - 0.5);

			// LAB:
			positionsLAB[indexOutput + 0] = (float) (dataLAB[indexInput + 1] - 0.5);
			positionsLAB[indexOutput + 1] = (float) (dataLAB[indexInput + 2] - 0.5);
			positionsLAB[indexOutput + 2] = (float) (dataLAB[indexInput + 0] - 0.5);
		}

		// Add bounding box
		boundingBox(
			outputSize * 3,
			positionsRGB,
			positionsHSB,
			positionsXYZ,
			positionsXYV,
			positionsLAB,
			colors
		);

		// Store counts
		countPoints = outputSize;
		countLines = 24;
	}


}


#endif // CAPTURE3_IMAGE_GRAPH_UTILS_H

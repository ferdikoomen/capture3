#ifndef CAPTURE3_COLOR_CHART_GRAPH_UTILS_H
#define CAPTURE3_COLOR_CHART_GRAPH_UTILS_H


#include <cmath>
#include <vector>
#include <omp.h>


#include "BoundingBoxUtils.h"
#include "../engine/objects/colorChart/ColorChart.h"
#include "../engine/objects/colorChart/ColorChartPatch.h"
#include "../constants/ColorChartConstants.h"


namespace Capture3
{

	static void generateGraph(
		const ColorChart *colorChartReference,
		const ColorChart *colorChartDetected,
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
		// Calculate output size, this is the number of patches
		// in the color chart * 4, since we display both the
		// detected and reference patches, as the line connecting them
		const unsigned int outputSize = COLOR_CHART_COUNT * 2;
		const unsigned int outputBytes = (outputSize + 24) * 3;

		// Resize vectors to fit points and bounding box
		positionsRGB.resize(outputBytes);
		positionsHSB.resize(outputBytes);
		positionsXYZ.resize(outputBytes);
		positionsXYV.resize(outputBytes);
		positionsLAB.resize(outputBytes);
		colors.resize(outputBytes);

		// Indexes
		unsigned int indexColor = 0;
		unsigned int indexRGB = 0;
		unsigned int indexHSB = 0;
		unsigned int indexXYZ = 0;
		unsigned int indexXYV = 0;
		unsigned int indexLAB = 0;

		// Get patches
		const std::vector<ColorChartPatch *> &patchesReference = colorChartReference->getPatches();
		const std::vector<ColorChartPatch *> &patchesDetected = colorChartDetected->getPatches();

		for (unsigned int index = 0; index < COLOR_CHART_COUNT; index++) {

			// Fetch patches
			const ColorChartPatch *patchReference = patchesReference[index];
			const ColorChartPatch *patchDetected = patchesDetected[index];

			// Fetch colors
			const double *referenceRGB = patchReference->getRGB();
			const double *referenceHSB = patchReference->getHSB();
			const double *referenceXYZ = patchReference->getXYZ();
			const double *referenceXYV = patchReference->getXYV();
			const double *referenceLAB = patchReference->getLAB();
			const double *detectedRGB = patchDetected->getRGB();
			const double *detectedHSB = patchDetected->getHSB();
			const double *detectedXYZ = patchDetected->getXYZ();
			const double *detectedXYV = patchDetected->getXYV();
			const double *detectedLAB = patchDetected->getLAB();

			// Colors
			colors[indexColor++] = (float) detectedRGB[0];
			colors[indexColor++] = (float) detectedRGB[1];
			colors[indexColor++] = (float) detectedRGB[2];
			colors[indexColor++] = (float) referenceRGB[0];
			colors[indexColor++] = (float) referenceRGB[1];
			colors[indexColor++] = (float) referenceRGB[2];

			// RGB
			positionsRGB[indexRGB++] = (float) (detectedRGB[1] - 0.5);
			positionsRGB[indexRGB++] = (float) (detectedRGB[2] - 0.5);
			positionsRGB[indexRGB++] = (float) (detectedRGB[0] - 0.5);
			positionsRGB[indexRGB++] = (float) (referenceRGB[1] - 0.5);
			positionsRGB[indexRGB++] = (float) (referenceRGB[2] - 0.5);
			positionsRGB[indexRGB++] = (float) (referenceRGB[0] - 0.5);

			// HSB:
			const double radians1 = detectedHSB[0] * 2.0 * M_PI;
			const double radians2 = referenceHSB[0] * 2.0 * M_PI;
			const double radius1 = (detectedHSB[1] * detectedHSB[2]) / 2.0;
			const double radius2 = (referenceHSB[1] * referenceHSB[2]) / 2.0;
			positionsHSB[indexHSB++] = (float) (radius1 * std::cos(radians1));
			positionsHSB[indexHSB++] = (float) (radius1 * std::sin(radians1));
			positionsHSB[indexHSB++] = (float) (detectedHSB[2] - 0.5);
			positionsHSB[indexHSB++] = (float) (radius2 * std::cos(radians2));
			positionsHSB[indexHSB++] = (float) (radius2 * std::sin(radians2));
			positionsHSB[indexHSB++] = (float) (referenceHSB[2] - 0.5);

			// XYZ:
			positionsXYZ[indexXYZ++] = (float) (detectedXYZ[2] - 0.5);
			positionsXYZ[indexXYZ++] = (float) (detectedXYZ[0] - 0.5);
			positionsXYZ[indexXYZ++] = (float) (detectedXYZ[1] - 0.5);
			positionsXYZ[indexXYZ++] = (float) (referenceXYZ[2] - 0.5);
			positionsXYZ[indexXYZ++] = (float) (referenceXYZ[0] - 0.5);
			positionsXYZ[indexXYZ++] = (float) (referenceXYZ[1] - 0.5);

			// XYV:
			positionsXYV[indexXYV++] = (float) (detectedXYV[1] - 0.5);
			positionsXYV[indexXYV++] = (float) (detectedXYV[0] - 0.5);
			positionsXYV[indexXYV++] = (float) (detectedXYV[2] - 0.5);
			positionsXYV[indexXYV++] = (float) (referenceXYV[1] - 0.5);
			positionsXYV[indexXYV++] = (float) (referenceXYV[0] - 0.5);
			positionsXYV[indexXYV++] = (float) (referenceXYV[2] - 0.5);

			// LAB:
			positionsLAB[indexLAB++] = (float) (detectedLAB[1] - 0.5);
			positionsLAB[indexLAB++] = (float) (detectedLAB[2] - 0.5);
			positionsLAB[indexLAB++] = (float) (detectedLAB[0] - 0.5);
			positionsLAB[indexLAB++] = (float) (referenceLAB[1] - 0.5);
			positionsLAB[indexLAB++] = (float) (referenceLAB[2] - 0.5);
			positionsLAB[indexLAB++] = (float) (referenceLAB[0] - 0.5);

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


#endif // CAPTURE3_COLOR_CHART_GRAPH_UTILS_H

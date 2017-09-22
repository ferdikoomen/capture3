#ifndef CAPTURE3_COLOR_CHART_PREVIEW_UTILS_H
#define CAPTURE3_COLOR_CHART_PREVIEW_UTILS_H


#include <string>
#include <vector>
#include <omp.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <QtCore/QString>
#include <QtCore/QFile>


#include "../engine/objects/colorChart/ColorChart.h"
#include "../engine/objects/colorChart/ColorChartPatch.h"
#include "../constants/ColorChartConstants.h"
#include "../constants/ResourceConstants.h"


namespace Capture3
{

	static Image *generatePreview(const ColorChart *colorChart)
	{
		// Load preview file
		QFile file(FILE_COLOR_CHART);
		file.open(QIODevice::ReadOnly);
		std::vector<char> buffer((size_t) file.size());
		file.read(buffer.data(), file.size());
		file.close();

		// Decode background
		cv::Mat background = cv::imdecode(buffer, cv::IMREAD_COLOR);
		const unsigned char *backgroundData = background.data;

		// Create new image
		auto *image = new Image(COLOR_CHART_OUTSIDE_WIDTH, COLOR_CHART_OUTSIDE_HEIGHT);
		image->getMeta().fileName = "ColorChecker Digital SG";
		const unsigned int imageArea = image->getSize().getArea();
		double *imageDataRGB = image->getRGB().getData();
		double *imageDataHSB = image->getHSB().getData();
		double *imageDataXYZ = image->getXYZ().getData();
		double *imageDataXYV = image->getXYV().getData();
		double *imageDataLAB = image->getLAB().getData();

		// Copy background
		#pragma omp parallel for schedule(static)
		for (unsigned int i = 0; i < imageArea; i++) {
			const unsigned int index = i * 3;
			imageDataRGB[index + 0] = backgroundData[index + 2] / 255.0;
			imageDataRGB[index + 1] = backgroundData[index + 1] / 255.0;
			imageDataRGB[index + 2] = backgroundData[index + 0] / 255.0;
		}

		// Convert RGB to other channels
		image->convertRGB();

		// Clear data
		background.release();

		// Fetch patches
		const std::vector<ColorChartPatch *> &patches = colorChart->getPatches();

		// Draw preview
		#pragma omp parallel for schedule(static) collapse(2)
		for (unsigned int col = 0; col < COLOR_CHART_COLS; col++) {
			for (unsigned int row = 0; row < COLOR_CHART_ROWS; row++) {

				// Get patch
				const ColorChartPatch *patch = patches[(COLOR_CHART_ROWS * col) + row];
				const double *rgb = patch->getRGB();
				const double *hsb = patch->getHSB();
				const double *xyz = patch->getXYZ();
				const double *xyv = patch->getXYV();
				const double *lab = patch->getLAB();

				// Calculate gamma corrected RGB values
				const double r = applyGamma(rgb[0]);
				const double g = applyGamma(rgb[1]);
				const double b = applyGamma(rgb[2]);

				// Calculate start position
				const unsigned int startX = col * (COLOR_CHART_PATCH_WIDTH + COLOR_CHART_PATCH_PADDING) + COLOR_CHART_PATCH_OFFSET_X;
				const unsigned int startY = row * (COLOR_CHART_PATCH_HEIGHT + COLOR_CHART_PATCH_PADDING) + COLOR_CHART_PATCH_OFFSET_Y;

				// Draw patch
				for (unsigned int y = startY, endY = startY + COLOR_CHART_PATCH_HEIGHT; y < endY; y++) {
					for (unsigned int x = startX, endX = startX + COLOR_CHART_PATCH_WIDTH; x < endX; x++) {
						const unsigned int index = (COLOR_CHART_OUTSIDE_WIDTH * y + x) * 3;
						imageDataRGB[index + 0] = r;
						imageDataRGB[index + 1] = g;
						imageDataRGB[index + 2] = b;
						imageDataHSB[index + 0] = hsb[0];
						imageDataHSB[index + 1] = hsb[1];
						imageDataHSB[index + 2] = hsb[2];
						imageDataXYZ[index + 0] = xyz[0];
						imageDataXYZ[index + 1] = xyz[1];
						imageDataXYZ[index + 2] = xyz[2];
						imageDataXYV[index + 0] = xyv[0];
						imageDataXYV[index + 1] = xyv[1];
						imageDataXYV[index + 2] = xyv[2];
						imageDataLAB[index + 0] = lab[0];
						imageDataLAB[index + 1] = lab[1];
						imageDataLAB[index + 2] = lab[2];
					}
				}
			}
		}

		// Apply gamma correction and return
		return image;
	}

}


#endif // CAPTURE3_COLOR_CHART_PREVIEW_UTILS_H

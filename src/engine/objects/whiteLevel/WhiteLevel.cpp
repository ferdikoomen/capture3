#include "WhiteLevel.h"


namespace Capture3
{

	WhiteLevel::WhiteLevel(const Image *image) :
		width(image->getSize().getWidth()),
		height(image->getSize().getHeight()),
		area(image->getSize().getArea()),
		white(image->getRGB().getMat().clone()),
		whiteData((double *) white.data),

		// Min and max values
		whiteLevelMinR(0),
		whiteLevelMinG(0),
		whiteLevelMinB(0),
		whiteLevelMaxR(0),
		whiteLevelMaxG(0),
		whiteLevelMaxB(0)
	{
		// Blur image for better results
		cv::blur(white, white, cv::Size(50, 50));
		cv::blur(white, white, cv::Size(50, 50));
		cv::blur(white, white, cv::Size(50, 50));

		double minR = 1;
		double minG = 1;
		double minB = 1;
		double maxR = 0;
		double maxG = 0;
		double maxB = 0;

		// Find min and max values
		#pragma omp parallel for schedule(static) \
			reduction(min:minR), \
			reduction(min:minG), \
			reduction(min:minB), \
			reduction(max:maxR), \
			reduction(max:maxG), \
			reduction(max:maxB)
		for (unsigned int i = 0; i < area; i++) {

			// Fetch color
			const unsigned int index = i * 3;
			const double r = whiteData[index + 0];
			const double g = whiteData[index + 1];
			const double b = whiteData[index + 2];

			// Find min and max values
			minR = r < minR ? r : minR;
			minG = g < minG ? g : minG;
			minB = b < minB ? b : minB;
			maxR = r > maxR ? r : maxR;
			maxG = g > maxG ? g : maxG;
			maxB = b > maxB ? b : maxB;
		}

		// Store result
		whiteLevelMinR = minR;
		whiteLevelMinG = minG;
		whiteLevelMinB = minB;
		whiteLevelMaxR = maxR;
		whiteLevelMaxG = maxG;
		whiteLevelMaxB = maxB;

		// Find min and max values
		whiteLevelMin = std::min(std::min(whiteLevelMinR, whiteLevelMinG), whiteLevelMinB);
		whiteLevelMax = std::max(std::max(whiteLevelMaxR, whiteLevelMaxG), whiteLevelMinB);

		// Calculate white balance (based on lightest color)
		whiteLevelR = whiteLevelMax / whiteLevelMaxR;
		whiteLevelG = whiteLevelMax / whiteLevelMaxG;
		whiteLevelB = whiteLevelMax / whiteLevelMaxB;

		// Normalize white level, so we don't clip any channels at this point
		whiteLevel = std::max(std::max(whiteLevelR, whiteLevelG), whiteLevelB);
		whiteLevelNormR = whiteLevelR / whiteLevel;
		whiteLevelNormG = whiteLevelG / whiteLevel;
		whiteLevelNormB = whiteLevelB / whiteLevel;
	}


	WhiteLevel::~WhiteLevel()
	{
		whiteData = nullptr;
		white.release();
	}


	void WhiteLevel::apply(Image *image)
	{
		// Fetch RGB data
		double *imageData = image->getRGB().getData();

		// Per pixel white level adjustments
		#pragma omp parallel for schedule(static)
		for (unsigned int i = 0; i < area; i++) {

			// Fetch color
			const unsigned int index = i * 3;
			double r = imageData[index + 0];
			double g = imageData[index + 1];
			double b = imageData[index + 2];

			// Fetch white reference color
			const double whiteR = whiteData[index + 0];
			const double whiteG = whiteData[index + 1];
			const double whiteB = whiteData[index + 2];

			// Our goal is to create a perfectly calibrated image. In order to
			// achieve this, we need to make sure that we create a smooth image
			// in terms of color intensity (or illumination). We can do this
			// by mixing the values from this image with ones from a reference
			// white image.
			r = r * (whiteLevelMaxR / whiteR);
			g = g * (whiteLevelMaxG / whiteG);
			b = b * (whiteLevelMaxB / whiteB);
			r = r * whiteLevelNormR;
			g = g * whiteLevelNormG;
			b = b * whiteLevelNormB;

			// Cap values
			// r = r < 0 ? 0 : r > 1 ? 1 : r;
			// g = g < 0 ? 0 : g > 1 ? 1 : g;
			// b = b < 0 ? 0 : b > 1 ? 1 : b;

			// Store in output data
			imageData[index + 0] = r;
			imageData[index + 1] = g;
			imageData[index + 2] = b;
		}

		// Convert RGB to other channels
		image->convertRGB();
	}
}
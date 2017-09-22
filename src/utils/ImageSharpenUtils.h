#ifndef CAPTURE3_IMAGE_SHARPEN_UTILS_H
#define CAPTURE3_IMAGE_SHARPEN_UTILS_H


#include <cmath>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>


#include "../engine/objects/image/Image.h"


namespace Capture3
{

	static void sharpenImage(Image &image, unsigned int radius, double strength)
	{
		// get image size
		const unsigned int imageArea = image.getSize().getArea();
		const unsigned int imageWidth = image.getSize().getWidth();
		const unsigned int imageHeight = image.getSize().getHeight();

		// Temp data
		cv::Mat temp(cv::Size(imageWidth, imageHeight), CV_64FC1, cv::Scalar(0));
		cv::Mat blur(cv::Size(imageWidth, imageHeight), CV_64FC1, cv::Scalar(0));

		// Fetch pointers and size
		double *labData = image.getLAB().getData();
		auto *tempData = (double *) temp.data;
		auto *blurData = (double *) blur.data;

		// We will only apply sharpening on the lightness channel,
		// afterwards we mix this again to create a RGB output.
		// Sharpening the lightness channel creates a very natural
		// looking result and avoids heavy color changes around edges.
		#pragma omp parallel for schedule(static)
		for (unsigned int i = 0; i < imageArea; i++) {
			tempData[i] = labData[i * 3];
		}

		// Apply unsharp masking
		cv::GaussianBlur(temp, blur, cv::Size(0, 0), radius, radius);
		cv::addWeighted(temp, 1.0 + strength, blur, -strength, 0, blur);

		// Copy the result
		#pragma omp parallel for schedule(static)
		for (unsigned int i = 0; i < imageArea; i++) {
			labData[i * 3] = blurData[i];
		}

		// Release images
		blur.release();
		temp.release();

		// Convert LAB to other channels
		image.convertLAB();
	}
}


#endif // CAPTURE3_IMAGE_HISTOGRAM_UTILS_H

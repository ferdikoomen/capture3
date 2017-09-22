#ifndef CAPTURE3_COLOR_UTILS_H
#define CAPTURE3_COLOR_UTILS_H


#include <cmath>
#include <vector>
#include <omp.h>


namespace Capture3
{


	static double applyGamma(const double value)
	{
		return value > 0.0031308 ? 1.055 * std::pow(value, 1.0 / 2.4) - 0.055 : 12.92 * value;
	}


	static void applyGamma(double *data, const unsigned int bytes)
	{
		#pragma omp parallel for schedule(static)
		for (unsigned int i = 0; i < bytes; i++) {
			double color = data[i];
			color = color > 0.0031308 ? 1.055 * std::pow(color, 1.0 / 2.4) - 0.055 : 12.92 * color;
			data[i] = color;
		}
	}


	static double applyInverseGamma(const double value)
	{
		return value > 0.04045 ? std::pow((value + 0.055) / 1.055, 2.4) : value / 12.92;
	}


	static void applyInverseGamma(double *data, const unsigned int bytes)
	{
		#pragma omp parallel for schedule(static)
		for (unsigned int i = 0; i < bytes; i++) {
			double color = data[i];
			color = color > 0.04045 ? std::pow((color + 0.055) / 1.055, 2.4) : color / 12.92;
			data[i] = color;
		}
	}


	static unsigned char to8Bit(const double value)
	{
		auto result = (int) lround(value * 255.0);
		result = result < 0 ? 0 : result;
		result = result > 255 ? 255 : result;
		return (unsigned char) result;
	}


	static void toGreyscale(
		const double *input,
		double *output,
		const unsigned int size,
		const double minR = 0,
		const double minG = 0,
		const double minB = 0,
		const double maxR = 1,
		const double maxG = 1,
		const double maxB = 1
	)
	{
		// Calculate normalized greyscale image
		#pragma omp parallel for schedule(static)
		for (unsigned int i = 0; i < size; i++) {
			const unsigned int index = i * 3;
			const double colorR = (input[index + 0] - minR) / (maxR - minR);
			const double colorG = (input[index + 1] - minG) / (maxG - minG);
			const double colorB = (input[index + 2] - minB) / (maxB - minB);
			const double luma = (0.2126 * colorR) + (0.7152 * colorG) + (0.0722 * colorB);
			output[i] = luma;
		}
	}
}


#endif // CAPTURE3_COLOR_UTILS_H

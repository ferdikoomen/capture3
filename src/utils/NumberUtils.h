#ifndef CAPTURE3_NUMBER_UTILS_H
#define CAPTURE3_NUMBER_UTILS_H


#include <cmath>
#include <vector>


namespace Capture3
{

	static double map(
		const double value,
		const double inputMin,
		const double inputMax,
		const double outputMin,
		const double outputMax
	)
	{
		double result = (((value - inputMin) / (inputMax - inputMin)) * (outputMax - outputMin)) + outputMin;
		result = result < outputMin ? outputMin : result;
		result = result > outputMax ? outputMax : result;
		return result;
	}


	static double deg2rad(const double radians)
	{
		return radians * (180.0 / M_PI);
	}


	static double rad2deg(const double degrees)
	{
		return degrees * (M_PI / 180.0);
	}

}


#endif // CAPTURE3_NUMBER_UTILS_H

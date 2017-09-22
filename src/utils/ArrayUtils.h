#ifndef CAPTURE3_ARRAY_UTILS_H
#define CAPTURE3_ARRAY_UTILS_H


#include <cmath>
#include <vector>
#include <numeric>
#include <algorithm>


namespace Capture3
{

	static void filterUnique(std::vector<double> &data)
	{
		std::sort(data.begin(), data.end());
		data.erase(std::unique(data.begin(), data.end()), data.end());
	}


	static double calculateMean(std::vector<double> &data)
	{
		// Average
		const double sum = std::accumulate(data.begin(), data.end(), 0.0);
		return sum / data.size();
	}


	static double calculateMedian(std::vector<double> &data)
	{
		// Middle
		std::nth_element(data.begin(), data.begin() + data.size() / 2, data.end());
		return data[data.size() / 2];
	}

}


#endif // CAPTURE3_ARRAY_UTILS_H

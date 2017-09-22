#ifndef CAPTURE3_SPLINE_H
#define CAPTURE3_SPLINE_H


#include <cmath>
#include <vector>
#include <algorithm>


#include "SplineMatrix.h"


namespace Capture3
{

	class Spline final
	{

		public:
			Spline();

			virtual ~Spline();

			void setBoundary(
				const unsigned int left, const double valueLeft,
				const unsigned int right, const double valueRight,
				const bool forceExtrapolation
			);

			void setPoints(
				const std::vector<double> &x,
				const std::vector<double> &y,
				const bool cubicSpline = true
			);

			double at(const double x) const;

			double deriv(const unsigned int order, const double x) const;

		private:
			std::vector<double> mx;
			std::vector<double> my;
			std::vector<double> ma;
			std::vector<double> mb;
			std::vector<double> mc;
			double mb0;
			double mc0;
			unsigned int left;
			unsigned int right;
			double valueLeft;
			double valueRight;
			bool forceExtrapolation;
	};
}

#endif // CAPTURE3_SPLINE_H

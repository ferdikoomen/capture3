#ifndef CAPTURE3_CURVE_DATA_CUBIC_H
#define CAPTURE3_CURVE_DATA_CUBIC_H


#include <cmath>
#include <vector>


#include "CurvePoint.h"
#include "../spline/Spline.h"


namespace Capture3
{

	class CurveDataCubic final
	{

		public:
			CurveDataCubic();

			virtual ~CurveDataCubic();

			void calculate(
				const std::vector<double> &x,
				const std::vector<double> &y,
				const unsigned int resolution = 256
			);

			double getY(const double x) const;

			double getX(const double y) const;

			const Spline &getSpline() const;

			const std::vector<double> &getPointsX() const;

			const std::vector<double> &getPointsY() const;

			const std::vector<double> &getSplineX() const;

			const std::vector<double> &getSplineY() const;

		private:
			Spline spline;
			std::vector<double> pointsX;
			std::vector<double> pointsY;
			std::vector<double> splineX;
			std::vector<double> splineY;
			unsigned int size;
	};
}

#endif // CAPTURE3_CURVE_DATA_CUBIC_H

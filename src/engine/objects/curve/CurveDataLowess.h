#ifndef CAPTURE3_CURVE_DATA_LOWESS_H
#define CAPTURE3_CURVE_DATA_LOWESS_H


#include <cmath>
#include <vector>


#include "CurvePoint.h"


namespace Capture3
{

	class CurveDataLowess final
	{

		public:
			CurveDataLowess();

			virtual ~CurveDataLowess();

			void calculate(
				const std::vector<const CurvePoint *> &points,
				const double span = 0.75,
				const unsigned int steps = 2
			);

			const std::vector<double> &getPointsX() const;

			const std::vector<double> &getPointsY() const;

		private:
			void lowess(
				const double *x,
				const double *y,
				const unsigned int size,
				double *rw,
				double *res,
				double *ys,
				const double span,
				const unsigned int steps,
				const double delta
			);

			void lowest(
				const double *x,
				const double *y,
				const unsigned int size,
				const double &xs,
				double &ys,
				const unsigned int left,
				const unsigned int right,
				double *residuals,
				const bool useWeights,
				const double *weights,
				bool &ok
			);

			void sort(double *x, const unsigned n, const unsigned k);

			int rcmp(const double x, const double y);

			std::vector<double> pointsX;
			std::vector<double> pointsY;
	};
}

#endif // CAPTURE3_CURVE_DATA_LOWESS_H

#ifndef CAPTURE3_CURVE_DATA_LINEAR_H
#define CAPTURE3_CURVE_DATA_LINEAR_H


#include <cmath>
#include <vector>


#include "CurvePoint.h"


namespace Capture3
{

	class CurveDataLinear final
	{

		public:
			CurveDataLinear();

			virtual ~CurveDataLinear();

			void calculate(const std::vector<const CurvePoint *> &points);

			double getX1() const;

			double getY1() const;

			double getX2() const;

			double getY2() const;

		private:
			std::vector<double> extrapolateToEdge(
				const double fromX, const double fromY,
				const double toX, const double toY,
				const double boundsMinX = 0, const double boundsMaxX = 1,
				const double boundsMinY = 0, const double boundsMaxY = 1
			);

			double slope;
			double intercept;
			double x1;
			double y1;
			double x2;
			double y2;
	};
}

#endif // CAPTURE3_CURVE_DATA_LINEAR_H

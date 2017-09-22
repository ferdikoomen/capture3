#ifndef CAPTURE3_CURVE_H
#define CAPTURE3_CURVE_H


#include <cmath>
#include <vector>


#include "CurvePoint.h"
#include "CurveDataLinear.h"
#include "CurveDataLowess.h"
#include "CurveDataCubic.h"
#include "../colorChart/ColorChartPatch.h"


namespace Capture3
{

	class Curve
	{

		public:
			Curve();

			virtual ~Curve();

			void add(const double x, const double y, const ColorChartPatch *patch);

			void finalize();

			double getY(const double x) const;

			double getX(const double y) const;

			const std::vector<const CurvePoint *> &getPoints() const;

			const CurveDataLinear &getDataLinear() const;

			const CurveDataLowess &getDataLowess() const;

			const CurveDataCubic &getDataCubic() const;

		private:
			std::vector<const CurvePoint *> points;
			CurveDataLinear dataLinear;
			CurveDataLowess dataLowess;
			CurveDataCubic dataCubic;
	};
}

#endif // CAPTURE3_CURVE_H

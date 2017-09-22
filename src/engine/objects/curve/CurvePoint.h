#ifndef CAPTURE3_CURVE_POINT_H
#define CAPTURE3_CURVE_POINT_H


#include "../colorChart/ColorChartPatch.h"


namespace Capture3
{

	class CurvePoint final
	{

		public:
			CurvePoint(const double x = 0, const double y = 0, const ColorChartPatch *patch = nullptr);

			virtual ~CurvePoint();

			const double getX() const;

			const double getY() const;

			const ColorChartPatch *getPatch() const;

		private:
			const double x;
			const double y;
			const ColorChartPatch *patch;
	};
}

#endif // CAPTURE3_CURVE_POINT_H

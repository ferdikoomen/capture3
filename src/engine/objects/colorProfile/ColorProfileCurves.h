#ifndef CAPTURE3_COLOR_PROFILE_CURVES_H
#define CAPTURE3_COLOR_PROFILE_CURVES_H


#include <vector>


#include "ColorProfileCurve.h"
#include "ColorProfileChartPatchData.h"


namespace Capture3
{

	class ColorProfileCurves final
	{
		public:
			ColorProfileCurves(const std::vector<const ColorProfileChartPatchData *> &patches);

			virtual ~ColorProfileCurves();

			const ColorProfileCurve &getCurveX() const;

			const ColorProfileCurve &getCurveY() const;

			const ColorProfileCurve &getCurveZ() const;

		private:
			ColorProfileCurve curveX;
			ColorProfileCurve curveY;
			ColorProfileCurve curveZ;

	};
}

#endif // CAPTURE3_COLOR_PROFILE_CURVES_H

#ifndef CAPTURE3_COLOR_PROFILE_CURVE_H
#define CAPTURE3_COLOR_PROFILE_CURVE_H


#include <cmath>
#include <vector>


#include "ColorProfileChartPatchData.h"
#include "../curve/Curve.h"
#include "../curve/CurvePoint.h"


namespace Capture3
{

	class ColorProfileCurve final : public Curve
	{

		public:
			ColorProfileCurve(
				const std::vector<const ColorProfileChartPatchData *> &patches,
				const unsigned int channel
			);

			virtual ~ColorProfileCurve();

		private:

	};
}

#endif // CAPTURE3_COLOR_PROFILE_CURVE_H

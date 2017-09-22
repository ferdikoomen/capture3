#ifndef CAPTURE3_WHITE_BALANCE_CURVE_H
#define CAPTURE3_WHITE_BALANCE_CURVE_H


#include <cmath>
#include <vector>


#include "WhiteBalanceChartPatchData.h"
#include "../curve/Curve.h"
#include "../curve/CurvePoint.h"


namespace Capture3
{

	class WhiteBalanceCurve final : public Curve
	{

		public:
			WhiteBalanceCurve(
				const std::vector<const WhiteBalanceChartPatchData *> &patches,
				const unsigned int channel
			);

			virtual ~WhiteBalanceCurve();

		private:

	};
}

#endif // CAPTURE3_WHITE_BALANCE_CURVE_H

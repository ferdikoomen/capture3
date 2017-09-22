#ifndef CAPTURE3_WHITE_BALANCE_CURVES_H
#define CAPTURE3_WHITE_BALANCE_CURVES_H


#include <vector>


#include "WhiteBalanceCurve.h"
#include "WhiteBalanceChartPatchData.h"


namespace Capture3
{

	class WhiteBalanceCurves final
	{
		public:
			WhiteBalanceCurves(const std::vector<const WhiteBalanceChartPatchData *> &patches);

			virtual ~WhiteBalanceCurves();

			const WhiteBalanceCurve &getCurveX() const;

			const WhiteBalanceCurve &getCurveY() const;

			const WhiteBalanceCurve &getCurveZ() const;

		private:
			WhiteBalanceCurve curveX;
			WhiteBalanceCurve curveY;
			WhiteBalanceCurve curveZ;

	};
}

#endif // CAPTURE3_WHITE_BALANCE_CURVES_H

#ifndef CAPTURE3_WHITE_BALANCE_H
#define CAPTURE3_WHITE_BALANCE_H


#include <cmath>
#include <vector>
#include <omp.h>


#include "WhiteBalanceChart.h"
#include "WhiteBalanceCurves.h"
#include "WhiteBalanceGain.h"
#include "../colorChart/ColorChart.h"
#include "../colorChart/ColorChartPatch.h"


namespace Capture3
{

	class WhiteBalance final
	{

		public:
			WhiteBalance(
				const ColorChart *colorChartReference,
				const ColorChart *colorChartDetected
			);

			virtual ~WhiteBalance();

			const WhiteBalanceChart &getChart() const;

			const WhiteBalanceGain &getGain() const;

			const WhiteBalanceCurves &getCurvesRGB() const;

			const WhiteBalanceCurves &getCurvesHSB() const;

			const WhiteBalanceCurves &getCurvesXYZ() const;

			const WhiteBalanceCurves &getCurvesXYV() const;

			const WhiteBalanceCurves &getCurvesLAB() const;

		private:
			WhiteBalanceChart chart;
			WhiteBalanceGain gain;
			WhiteBalanceCurves curvesRGB;
			WhiteBalanceCurves curvesHSB;
			WhiteBalanceCurves curvesXYZ;
			WhiteBalanceCurves curvesXYV;
			WhiteBalanceCurves curvesLAB;
	};
}

#endif // CAPTURE3_WHITE_BALANCE_H

#ifndef CAPTURE3_COLOR_PROFILE_H
#define CAPTURE3_COLOR_PROFILE_H


#include <cmath>
#include <vector>
#include <omp.h>


#include "ColorProfileChart.h"
#include "ColorProfileCurves.h"
#include "../colorChart/ColorChart.h"
#include "../colorChart/ColorChartPatch.h"


namespace Capture3
{

	class ColorProfile final
	{

		public:
			ColorProfile(
				const ColorChart *colorChartReference,
				const ColorChart *colorChartDetected
			);

			virtual ~ColorProfile();

			const ColorProfileChart &getChart() const;

			const ColorProfileCurves &getCurvesRGB() const;

			const ColorProfileCurves &getCurvesHSB() const;

			const ColorProfileCurves &getCurvesXYZ() const;

			const ColorProfileCurves &getCurvesXYV() const;

			const ColorProfileCurves &getCurvesLAB() const;

		private:
			ColorProfileChart chart;
			ColorProfileCurves curvesRGB;
			ColorProfileCurves curvesHSB;
			ColorProfileCurves curvesXYZ;
			ColorProfileCurves curvesXYV;
			ColorProfileCurves curvesLAB;
	};
}

#endif // CAPTURE3_COLOR_PROFILE_H

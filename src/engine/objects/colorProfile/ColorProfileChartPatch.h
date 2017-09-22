#ifndef CAPTURE3_COLOR_PROFILE_CHART_PATCH_H
#define CAPTURE3_COLOR_PROFILE_CHART_PATCH_H


#include <vector>


#include "../colorChart/ColorChartPatch.h"
#include "../../../utils/ColorDistanceUtils.h"
#include "../../../constants/MetamorfozeConstants.h"


namespace Capture3
{

	class ColorProfileChartPatch final
	{

		public:
			ColorProfileChartPatch(
				const ColorChartPatch *patchReference,
				const ColorChartPatch *patchDetected
			);

			virtual ~ColorProfileChartPatch();

			const ColorChartPatch *getPatchReference() const;

			const ColorChartPatch *getPatchDetected() const;

			double getDeltaChroma() const;

			double getDeltaLightness() const;

			double getDeltaCIE1976() const;

			double getDeltaCIE2000() const;

			bool isCorrect() const;

		private:
			const ColorChartPatch *patchReference;
			const ColorChartPatch *patchDetected;
			double deltaChroma;
			double deltaLightness;
			double deltaCIE1976;
			double deltaCIE2000;
			bool correct;
	};
}

#endif // CAPTURE3_COLOR_PROFILE_CHART_PATCH_H

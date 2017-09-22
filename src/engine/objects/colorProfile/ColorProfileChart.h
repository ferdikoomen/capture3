#ifndef CAPTURE3_COLOR_PROFILE_CHART_H
#define CAPTURE3_COLOR_PROFILE_CHART_H


#include <vector>


#include "ColorProfileChartPatch.h"
#include "ColorProfileChartPatchData.h"
#include "../colorChart/ColorChart.h"
#include "../colorChart/ColorChartPatch.h"


namespace Capture3
{

	class ColorProfileChart final
	{

		public:
			ColorProfileChart(
				const ColorChart *colorChartReference,
				const ColorChart *colorChartDetected
			);

			virtual ~ColorProfileChart();

			const std::vector<const ColorProfileChartPatch *> &getPatches() const;

			const std::vector<const ColorProfileChartPatchData *> &getPatchesRGB() const;

			const std::vector<const ColorProfileChartPatchData *> &getPatchesHSB() const;

			const std::vector<const ColorProfileChartPatchData *> &getPatchesXYZ() const;

			const std::vector<const ColorProfileChartPatchData *> &getPatchesXYV() const;

			const std::vector<const ColorProfileChartPatchData *> &getPatchesLAB() const;

		private:
			const unsigned int count;
			std::vector<const ColorProfileChartPatch *> patches;
			std::vector<const ColorProfileChartPatchData *> patchesRGB;
			std::vector<const ColorProfileChartPatchData *> patchesHSB;
			std::vector<const ColorProfileChartPatchData *> patchesXYZ;
			std::vector<const ColorProfileChartPatchData *> patchesXYV;
			std::vector<const ColorProfileChartPatchData *> patchesLAB;
	};
}

#endif // CAPTURE3_COLOR_PROFILE_CHART_H

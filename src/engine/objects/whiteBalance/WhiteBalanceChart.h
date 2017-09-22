#ifndef CAPTURE3_WHITE_BALANCE_CHART_H
#define CAPTURE3_WHITE_BALANCE_CHART_H


#include <vector>


#include "WhiteBalanceChartPatch.h"
#include "WhiteBalanceChartPatchData.h"
#include "../colorChart/ColorChart.h"
#include "../colorChart/ColorChartPatch.h"


namespace Capture3
{

	class WhiteBalanceChart final
	{

		public:
			WhiteBalanceChart(
				const ColorChart *colorChartReference,
				const ColorChart *colorChartDetected
			);

			virtual ~WhiteBalanceChart();

			const std::vector<const WhiteBalanceChartPatch *> &getPatches() const;

			const std::vector<const WhiteBalanceChartPatchData *> &getPatchesRGB() const;

			const std::vector<const WhiteBalanceChartPatchData *> &getPatchesHSB() const;

			const std::vector<const WhiteBalanceChartPatchData *> &getPatchesXYZ() const;

			const std::vector<const WhiteBalanceChartPatchData *> &getPatchesXYV() const;

			const std::vector<const WhiteBalanceChartPatchData *> &getPatchesLAB() const;

		private:
			const unsigned int count;
			std::vector<const WhiteBalanceChartPatch *> patches;
			std::vector<const WhiteBalanceChartPatchData *> patchesRGB;
			std::vector<const WhiteBalanceChartPatchData *> patchesHSB;
			std::vector<const WhiteBalanceChartPatchData *> patchesXYZ;
			std::vector<const WhiteBalanceChartPatchData *> patchesXYV;
			std::vector<const WhiteBalanceChartPatchData *> patchesLAB;
	};
}

#endif // CAPTURE3_WHITE_BALANCE_CHART_H

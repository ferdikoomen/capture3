#ifndef CAPTURE3_WHITE_BALANCE_GAIN_PATCH_H
#define CAPTURE3_WHITE_BALANCE_GAIN_PATCH_H


#include <vector>


#include "../colorChart/ColorChartPatch.h"
#include "../../../utils/ColorDistanceUtils.h"
#include "../../../constants/MetamorfozeConstants.h"


namespace Capture3
{

	class WhiteBalanceGainPatch final
	{
		public:
			WhiteBalanceGainPatch(
				const ColorChartPatch *patchReferenceA,
				const ColorChartPatch *patchReferenceB,
				const ColorChartPatch *patchDetectedA,
				const ColorChartPatch *patchDetectedB
			);

			virtual ~WhiteBalanceGainPatch();

			const ColorChartPatch *getPatchReferenceA() const;

			const ColorChartPatch *getPatchReferenceB() const;

			const ColorChartPatch *getPatchDetectedA() const;

			const ColorChartPatch *getPatchDetectedB() const;

			double getDeltaReference() const;

			double getDeltaDetected() const;

			double getGain() const;

			bool isCorrect() const;

		private:
			const ColorChartPatch *patchReferenceA;
			const ColorChartPatch *patchReferenceB;
			const ColorChartPatch *patchDetectedA;
			const ColorChartPatch *patchDetectedB;
			double deltaReference;
			double deltaDetected;
			double gain;
			bool correct;

	};
}

#endif // CAPTURE3_WHITE_BALANCE_GAIN_PATCH_H

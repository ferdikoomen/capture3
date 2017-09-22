#ifndef CAPTURE3_WHITE_BALANCE_GAIN_H
#define CAPTURE3_WHITE_BALANCE_GAIN_H


#include <vector>


#include "WhiteBalanceGainPatch.h"
#include "../colorChart/ColorChart.h"
#include "../colorChart/ColorChartPatch.h"


namespace Capture3
{

	class WhiteBalanceGain final
	{
		public:
			WhiteBalanceGain(
				const ColorChart *colorChartReference,
				const ColorChart *colorChartDetected
			);

			virtual ~WhiteBalanceGain();

			const std::vector<const WhiteBalanceGainPatch *> &getPatches() const;

			const WhiteBalanceGainPatch &getPatchA() const;

			const WhiteBalanceGainPatch &getPatchB() const;

			const WhiteBalanceGainPatch &getPatchC() const;

			const WhiteBalanceGainPatch &getPatchD() const;

			const WhiteBalanceGainPatch &getPatchE() const;

			const WhiteBalanceGainPatch &getPatchF() const;

		private:
			const WhiteBalanceGainPatch patchA;
			const WhiteBalanceGainPatch patchB;
			const WhiteBalanceGainPatch patchC;
			const WhiteBalanceGainPatch patchD;
			const WhiteBalanceGainPatch patchE;
			const WhiteBalanceGainPatch patchF;
			const std::vector<const WhiteBalanceGainPatch *> patches;

	};
}

#endif // CAPTURE3_WHITE_BALANCE_GAIN_H

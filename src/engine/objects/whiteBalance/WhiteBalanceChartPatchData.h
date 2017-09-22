#ifndef CAPTURE3_WHITE_BALANCE_DATA_H
#define CAPTURE3_WHITE_BALANCE_DATA_H


#include <vector>


#include "WhiteBalanceChartPatch.h"


namespace Capture3
{

	class WhiteBalanceChartPatchData final
	{
		public:
			WhiteBalanceChartPatchData(
				const WhiteBalanceChartPatch *patch,
				const double *valueReference,
				const double *valueDetected
			);

			virtual ~WhiteBalanceChartPatchData();

			const WhiteBalanceChartPatch *getPatch() const;

			const double *getValueReference() const;

			const double *getValueDetected() const;

		private:
			const WhiteBalanceChartPatch *patch;
			const double *valueReference;
			const double *valueDetected;

	};
}

#endif // CAPTURE3_WHITE_BALANCE_DATA_H

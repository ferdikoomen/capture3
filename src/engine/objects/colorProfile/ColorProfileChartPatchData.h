#ifndef CAPTURE3_COLOR_PROFILE_CHART_DATA_H
#define CAPTURE3_COLOR_PROFILE_CHART_DATA_H


#include <vector>


#include "ColorProfileChartPatch.h"


namespace Capture3
{

	class ColorProfileChartPatchData final
	{
		public:
			ColorProfileChartPatchData(
				const ColorProfileChartPatch *patch,
				const double *valueReference,
				const double *valueDetected
			);

			virtual ~ColorProfileChartPatchData();

			const ColorProfileChartPatch *getPatch() const;

			const double *getValueReference() const;

			const double *getValueDetected() const;

		private:
			const ColorProfileChartPatch *patch;
			const double *valueReference;
			const double *valueDetected;

	};
}

#endif // CAPTURE3_COLOR_PROFILE_CHART_DATA_H

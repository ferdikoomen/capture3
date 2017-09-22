#include "ColorProfileCurve.h"


namespace Capture3
{

	ColorProfileCurve::ColorProfileCurve(
		const std::vector<const ColorProfileChartPatchData *> &patches,
		const unsigned int channel
	) :
		Curve()
	{
		for (const ColorProfileChartPatchData *patch : patches) {
			add(
				patch->getValueReference()[channel],
				patch->getValueDetected()[channel],
				patch->getPatch()->getPatchReference()
			);
		}

		// Finalize curve
		finalize();
	}


	ColorProfileCurve::~ColorProfileCurve()
	{
		//
	}

}
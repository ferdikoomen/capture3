#include "WhiteBalanceCurve.h"


namespace Capture3
{

	WhiteBalanceCurve::WhiteBalanceCurve(
		const std::vector<const WhiteBalanceChartPatchData *> &patches,
		const unsigned int channel
	) :
		Curve()
	{
		for (const WhiteBalanceChartPatchData *patch : patches) {
			add(
				patch->getValueReference()[channel],
				patch->getValueDetected()[channel],
				patch->getPatch()->getPatchReference()
			);
		}

		// Finalize curve
		finalize();
	}


	WhiteBalanceCurve::~WhiteBalanceCurve()
	{
		//
	}

}
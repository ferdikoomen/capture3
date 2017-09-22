#include "ColorProfileChartPatch.h"


namespace Capture3
{

	ColorProfileChartPatch::ColorProfileChartPatch(
		const ColorChartPatch *patchReference,
		const ColorChartPatch *patchDetected
	) :
		patchReference(patchReference),
		patchDetected(patchDetected),

		// Delta values
		deltaChroma(0),
		deltaLightness(0),
		deltaCIE1976(0),
		deltaCIE2000(0)
	{
		// Get values from reference and detected patches
		const double *referenceLAB = patchReference->getLAB();
		const double *detectedLAB = patchDetected->getLAB();

		// Get color distances
		deltaChroma = calculateDeltaChroma(referenceLAB, detectedLAB);
		deltaLightness = calculateDeltaLightness(referenceLAB, detectedLAB);
		deltaCIE1976 = calculateDeltaCIE1976(referenceLAB, detectedLAB);
		deltaCIE2000 = calculateDeltaCIE2000(referenceLAB, detectedLAB);

		// Check if the values are within the approved range
		correct = deltaChroma <= DELTA_C_MAX &&
				  deltaLightness <= DELTA_L_MAX &&
				  deltaCIE2000 <= DELTA_E_MAX;
	}


	ColorProfileChartPatch::~ColorProfileChartPatch()
	{
		//
	}


	const ColorChartPatch *ColorProfileChartPatch::getPatchReference() const
	{
		return patchReference;
	}


	const ColorChartPatch *ColorProfileChartPatch::getPatchDetected() const
	{
		return patchDetected;
	}


	double ColorProfileChartPatch::getDeltaChroma() const
	{
		return deltaChroma;
	}


	double ColorProfileChartPatch::getDeltaLightness() const
	{
		return deltaLightness;
	}


	double ColorProfileChartPatch::getDeltaCIE1976() const
	{
		return deltaCIE1976;
	}


	double ColorProfileChartPatch::getDeltaCIE2000() const
	{
		return deltaCIE2000;
	}


	bool ColorProfileChartPatch::isCorrect() const
	{
		return correct;
	}
}
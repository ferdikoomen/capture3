#include "WhiteBalanceGainPatch.h"


namespace Capture3
{

	WhiteBalanceGainPatch::WhiteBalanceGainPatch(
		const ColorChartPatch *patchReferenceA,
		const ColorChartPatch *patchReferenceB,
		const ColorChartPatch *patchDetectedA,
		const ColorChartPatch *patchDetectedB
	) :
		patchReferenceA(patchReferenceA),
		patchReferenceB(patchReferenceB),
		patchDetectedA(patchDetectedA),
		patchDetectedB(patchDetectedB)
	{
		// Calculate the gain modulation in lightness between reference and detected values
		deltaReference = calculateDeltaLightness(patchDetectedA->getLAB(), patchDetectedB->getLAB());
		deltaDetected = calculateDeltaLightness(patchReferenceA->getLAB(), patchReferenceB->getLAB());
		gain = (deltaDetected / deltaReference) * 100;

		// Check if the value is within the approved range
		correct = gain >= GAIN_MODULATION_MIN &&
				  gain <= GAIN_MODULATION_MAX;
	}


	WhiteBalanceGainPatch::~WhiteBalanceGainPatch()
	{
		//
	}


	const ColorChartPatch *WhiteBalanceGainPatch::getPatchReferenceA() const
	{
		return patchReferenceA;
	}


	const ColorChartPatch *WhiteBalanceGainPatch::getPatchReferenceB() const
	{
		return patchReferenceB;
	}


	const ColorChartPatch *WhiteBalanceGainPatch::getPatchDetectedA() const
	{
		return patchDetectedA;
	}


	const ColorChartPatch *WhiteBalanceGainPatch::getPatchDetectedB() const
	{
		return patchDetectedB;
	}


	double WhiteBalanceGainPatch::getDeltaReference() const
	{
		return deltaReference;
	}


	double WhiteBalanceGainPatch::getDeltaDetected() const
	{
		return deltaDetected;
	}


	double WhiteBalanceGainPatch::getGain() const
	{
		return gain;
	}


	bool WhiteBalanceGainPatch::isCorrect() const
	{
		return correct;
	}

}
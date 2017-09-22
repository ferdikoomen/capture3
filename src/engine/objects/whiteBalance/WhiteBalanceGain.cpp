#include "WhiteBalanceGain.h"


namespace Capture3
{

	WhiteBalanceGain::WhiteBalanceGain(
		const ColorChart *colorChartReference,
		const ColorChart *colorChartDetected
	) :
		patchA(
			colorChartReference->getPatchesGain()[0], colorChartReference->getPatchesGain()[1],
			colorChartDetected->getPatchesGain()[0], colorChartDetected->getPatchesGain()[1]
		),
		patchB(
			colorChartReference->getPatchesGain()[2], colorChartReference->getPatchesGain()[3],
			colorChartDetected->getPatchesGain()[2], colorChartDetected->getPatchesGain()[3]
		),
		patchC(
			colorChartReference->getPatchesGain()[4], colorChartReference->getPatchesGain()[5],
			colorChartDetected->getPatchesGain()[4], colorChartDetected->getPatchesGain()[5]
		),
		patchD(
			colorChartReference->getPatchesGain()[6], colorChartReference->getPatchesGain()[7],
			colorChartDetected->getPatchesGain()[6], colorChartDetected->getPatchesGain()[7]
		),
		patchE(
			colorChartReference->getPatchesGain()[8], colorChartReference->getPatchesGain()[9],
			colorChartDetected->getPatchesGain()[8], colorChartDetected->getPatchesGain()[9]
		),
		patchF(
			colorChartReference->getPatchesGain()[10], colorChartReference->getPatchesGain()[11],
			colorChartDetected->getPatchesGain()[10], colorChartDetected->getPatchesGain()[11]
		),

		// Store in patches list
		patches({&patchA, &patchB, &patchC, &patchD, &patchE, &patchF})
	{
		//
	}


	WhiteBalanceGain::~WhiteBalanceGain()
	{
		//
	}


	const std::vector<const WhiteBalanceGainPatch *> &WhiteBalanceGain::getPatches() const
	{
		return patches;
	}


	const WhiteBalanceGainPatch &WhiteBalanceGain::getPatchA() const
	{
		return patchA;
	}


	const WhiteBalanceGainPatch &WhiteBalanceGain::getPatchB() const
	{
		return patchB;
	}


	const WhiteBalanceGainPatch &WhiteBalanceGain::getPatchC() const
	{
		return patchC;
	}


	const WhiteBalanceGainPatch &WhiteBalanceGain::getPatchD() const
	{
		return patchD;
	}


	const WhiteBalanceGainPatch &WhiteBalanceGain::getPatchE() const
	{
		return patchE;
	}


	const WhiteBalanceGainPatch &WhiteBalanceGain::getPatchF() const
	{
		return patchF;
	}

}
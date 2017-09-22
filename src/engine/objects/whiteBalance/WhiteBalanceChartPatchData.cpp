#include "WhiteBalanceChartPatchData.h"


namespace Capture3
{

	WhiteBalanceChartPatchData::WhiteBalanceChartPatchData(
		const WhiteBalanceChartPatch *patch,
		const double *valueReference,
		const double *valueDetected
	) :
		patch(patch),
		valueReference(valueReference),
		valueDetected(valueDetected)
	{
		//
	}


	WhiteBalanceChartPatchData::~WhiteBalanceChartPatchData()
	{
		patch = nullptr;
		valueReference = nullptr;
		valueDetected = nullptr;
	}


	const WhiteBalanceChartPatch *WhiteBalanceChartPatchData::getPatch() const
	{
		return patch;
	}


	const double *WhiteBalanceChartPatchData::getValueReference() const
	{
		return valueReference;
	}


	const double *WhiteBalanceChartPatchData::getValueDetected() const
	{
		return valueDetected;
	}
}
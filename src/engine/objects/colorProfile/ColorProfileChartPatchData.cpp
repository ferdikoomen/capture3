#include "ColorProfileChartPatchData.h"


namespace Capture3
{

	ColorProfileChartPatchData::ColorProfileChartPatchData(
		const ColorProfileChartPatch *patch,
		const double *valueReference,
		const double *valueDetected
	) :
		patch(patch),
		valueReference(valueReference),
		valueDetected(valueDetected)
	{
		//
	}


	ColorProfileChartPatchData::~ColorProfileChartPatchData()
	{
		patch = nullptr;
		valueReference = nullptr;
		valueDetected = nullptr;
	}


	const ColorProfileChartPatch *ColorProfileChartPatchData::getPatch() const
	{
		return patch;
	}


	const double *ColorProfileChartPatchData::getValueReference() const
	{
		return valueReference;
	}


	const double *ColorProfileChartPatchData::getValueDetected() const
	{
		return valueDetected;
	}
}
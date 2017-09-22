#include "ColorProfileCurves.h"


namespace Capture3
{

	ColorProfileCurves::ColorProfileCurves(const std::vector<const ColorProfileChartPatchData *> &patches) :
		curveX(patches, 0),
		curveY(patches, 1),
		curveZ(patches, 2)
	{
		//
	}


	ColorProfileCurves::~ColorProfileCurves()
	{
		//
	}


	const ColorProfileCurve &ColorProfileCurves::getCurveX() const
	{
		return curveX;
	}


	const ColorProfileCurve &ColorProfileCurves::getCurveY() const
	{
		return curveY;
	}


	const ColorProfileCurve &ColorProfileCurves::getCurveZ() const
	{
		return curveZ;
	}
}
#include "WhiteBalanceCurves.h"


namespace Capture3
{

	WhiteBalanceCurves::WhiteBalanceCurves(const std::vector<const WhiteBalanceChartPatchData *> &patches) :
		curveX(patches, 0),
		curveY(patches, 1),
		curveZ(patches, 2)
	{
		//
	}


	WhiteBalanceCurves::~WhiteBalanceCurves()
	{
		//
	}


	const WhiteBalanceCurve &WhiteBalanceCurves::getCurveX() const
	{
		return curveX;
	}


	const WhiteBalanceCurve &WhiteBalanceCurves::getCurveY() const
	{
		return curveY;
	}


	const WhiteBalanceCurve &WhiteBalanceCurves::getCurveZ() const
	{
		return curveZ;
	}
}
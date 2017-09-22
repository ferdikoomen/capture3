#include "CurvePoint.h"


namespace Capture3
{

	CurvePoint::CurvePoint(const double x, const double y, const ColorChartPatch *patch) :
		x(x),
		y(y),
		patch(patch)
	{
		//
	}


	CurvePoint::~CurvePoint()
	{
		//
	}


	const double CurvePoint::getX() const
	{
		return x;
	}


	const double CurvePoint::getY() const
	{
		return y;
	}


	const ColorChartPatch *CurvePoint::getPatch() const
	{
		return patch;
	}

}
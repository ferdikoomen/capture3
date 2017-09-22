#include "ColorProfile.h"


namespace Capture3
{

	ColorProfile::ColorProfile(
		const ColorChart *colorChartReference,
		const ColorChart *colorChartDetected
	) :
		chart(colorChartReference, colorChartDetected),

		// Curves for different color spaces
		curvesRGB(chart.getPatchesRGB()),
		curvesHSB(chart.getPatchesHSB()),
		curvesXYZ(chart.getPatchesXYZ()),
		curvesXYV(chart.getPatchesXYV()),
		curvesLAB(chart.getPatchesLAB())
	{
		//
	}


	ColorProfile::~ColorProfile()
	{
		//
	}


	const ColorProfileChart &ColorProfile::getChart() const
	{
		return chart;
	}


	const ColorProfileCurves &ColorProfile::getCurvesRGB() const
	{
		return curvesRGB;
	}


	const ColorProfileCurves &ColorProfile::getCurvesHSB() const
	{
		return curvesHSB;
	}


	const ColorProfileCurves &ColorProfile::getCurvesXYZ() const
	{
		return curvesXYZ;
	}


	const ColorProfileCurves &ColorProfile::getCurvesXYV() const
	{
		return curvesXYV;
	}


	const ColorProfileCurves &ColorProfile::getCurvesLAB() const
	{
		return curvesLAB;
	}
}
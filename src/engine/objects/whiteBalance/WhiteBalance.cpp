#include "WhiteBalance.h"


namespace Capture3
{

	WhiteBalance::WhiteBalance(
		const ColorChart *colorChartReference,
		const ColorChart *colorChartDetected
	) :
		chart(colorChartReference, colorChartDetected),
		gain(colorChartReference, colorChartDetected),

		// Curves for different color spaces
		curvesRGB(chart.getPatchesRGB()),
		curvesHSB(chart.getPatchesHSB()),
		curvesXYZ(chart.getPatchesXYZ()),
		curvesXYV(chart.getPatchesXYV()),
		curvesLAB(chart.getPatchesLAB())
	{
		//
	}


	WhiteBalance::~WhiteBalance()
	{
		//
	}


	const WhiteBalanceChart &WhiteBalance::getChart() const
	{
		return chart;
	}


	const WhiteBalanceGain &WhiteBalance::getGain() const
	{
		return gain;
	}


	const WhiteBalanceCurves &WhiteBalance::getCurvesRGB() const
	{
		return curvesRGB;
	}


	const WhiteBalanceCurves &WhiteBalance::getCurvesHSB() const
	{
		return curvesHSB;
	}


	const WhiteBalanceCurves &WhiteBalance::getCurvesXYZ() const
	{
		return curvesXYZ;
	}


	const WhiteBalanceCurves &WhiteBalance::getCurvesXYV() const
	{
		return curvesXYV;
	}


	const WhiteBalanceCurves &WhiteBalance::getCurvesLAB() const
	{
		return curvesLAB;
	}

}
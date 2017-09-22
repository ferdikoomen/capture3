#include "Curve.h"


namespace Capture3
{

	Curve::Curve() :
		points(),
		dataLinear(),
		dataLowess(),
		dataCubic()
	{
		//
	}


	Curve::~Curve()
	{
		points.clear();
	}


	void Curve::add(const double x, const double y, const ColorChartPatch *patch)
	{
		points.push_back(new CurvePoint(x, y, patch));
	}


	void Curve::finalize()
	{
		// Sort list on X-axis
		std::sort(points.begin(), points.end(), [](const CurvePoint *a, const CurvePoint *b) {
			return a->getX() < b->getX();
		});

		dataLinear.calculate(points);
		dataLowess.calculate(points, 0.75, 2);
		dataCubic.calculate(
			dataLowess.getPointsX(),
			dataLowess.getPointsY(),
			256
		);
	}


	double Curve::getY(const double x) const
	{
		return dataCubic.getY(x);
	}


	double Curve::getX(const double y) const
	{
		return dataCubic.getX(y);
	}


	const std::vector<const CurvePoint *> &Curve::getPoints() const
	{
		return points;
	}


	const CurveDataLinear &Curve::getDataLinear() const
	{
		return dataLinear;
	}


	const CurveDataLowess &Curve::getDataLowess() const
	{
		return dataLowess;
	}


	const CurveDataCubic &Curve::getDataCubic() const
	{
		return dataCubic;
	}


}
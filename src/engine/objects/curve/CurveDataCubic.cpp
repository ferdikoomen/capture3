#include "CurveDataCubic.h"


namespace Capture3
{

	CurveDataCubic::CurveDataCubic() :
		spline(),
		pointsX(),
		pointsY(),
		splineX(),
		splineY(),
		size(0)
	{
		//
	}


	CurveDataCubic::~CurveDataCubic()
	{
		pointsX.clear();
		pointsY.clear();
		splineX.clear();
		splineY.clear();
	}


	void CurveDataCubic::calculate(
		const std::vector<double> &x,
		const std::vector<double> &y,
		const unsigned int resolution
	)
	{
		// Get total number of points
		size = (unsigned int) x.size();

		// Vars needed for reduce loop
		double position = 0;
		double positionX = 0;
		double positionY = 0;
		unsigned int count = 0;

		for (unsigned int i = 0; i < size; i++) {

			// Get data from point
			const double px = x[i];
			const double py = y[i];

			// Get distance from first point in the possible group
			const double distance = px - position;

			// If this is the last point in the list, then we
			// force this point to be added
			const bool force = (i == size - 1);

			// Set forced data (if needed)
			if (force) {
				positionX = px;
				positionY = py;
				count = 1;
			}

			// Add the point is the distance between this and the previous
			// point is larger then the (very) small threshold. We need to do
			// this because the cubic curve is a lot more stable when there
			// is a small distance between the data points.
			if (distance >= 0.0001 || force) {
				if (count > 0) {
					positionX /= count;
					positionY /= count;
					pointsX.push_back(positionX);
					pointsY.push_back(positionY);
				}

				// Reset data
				position = px;
				positionX = 0;
				positionY = 0;
				count = 0;
			}

			// Append current point
			positionX += px;
			positionY += py;
			count++;
		}

		// Use linear line (no curve) if there is not enough data
		if (pointsX.size() < 3) {
			pointsX = {0.0, 0.5, 1.0};
			pointsY = {0.0, 0.5, 1.0};
		}

		// Set points
		spline.setBoundary(2, 0.0, 2, 1.0, false);
		spline.setPoints(pointsX, pointsY);

		// Calculate fixed positions
		size = resolution;
		splineX.resize(size);
		splineY.resize(size);

		for (int i = 0; i < size; i++) {
			const double t = i / (double) (size - 1);
			splineX[i] = t;
			splineY[i] = spline.at(t);
		}
	}


	double CurveDataCubic::getY(const double x) const
	{
		double y = 0;
		if (size == 0) {
			y = x;
		} else if (x <= splineX.front()) {
			y = splineY.front();
		} else if (x >= splineX.back()) {
			y = splineY.back();
		} else {
			for (int i = 0; i < size - 1; i++) {
				const double x1 = splineX[i];
				const double x2 = splineX[i + 1];
				if (x >= x1 && x <= x2) {
					const double y1 = splineY[i];
					const double y2 = splineY[i + 1];
					const double mu = (x - x1) / (x2 - x1);
					y = (y1 * (1.0 - mu) + y2 * mu);
					break;
				}
			}
		}
		return y; // y < 0 ? 0 : y > 1 ? 1 : y;
	}


	double CurveDataCubic::getX(const double y) const
	{
		double x = 0;
		if (size == 0) {
			x = y;
		} else if (y <= splineY.front()) {
			x = splineX.front();
		} else if (y >= splineY.back()) {
			x = splineX.back();
		} else {
			for (int i = 0; i < size - 1; i++) {
				const double y1 = splineY[i];
				const double y2 = splineY[i + 1];
				if (y >= y1 && y <= y2) {
					const double x1 = splineX[i];
					const double x2 = splineX[i + 1];
					const double mu = (y - y1) / (y2 - y1);
					x = (x1 * (1.0 - mu) + x2 * mu);
					break;
				}
			}
		}
		return x; // x < 0 ? 0 : x > 1 ? 1 : x;
	}


	const Spline &CurveDataCubic::getSpline() const
	{
		return spline;
	}


	const std::vector<double> &CurveDataCubic::getPointsX() const
	{
		return pointsX;
	}


	const std::vector<double> &CurveDataCubic::getPointsY() const
	{
		return pointsY;
	}


	const std::vector<double> &CurveDataCubic::getSplineX() const
	{
		return splineX;
	}


	const std::vector<double> &CurveDataCubic::getSplineY() const
	{
		return splineY;
	}
}
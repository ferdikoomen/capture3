#include "CurveDataLinear.h"


namespace Capture3
{

	CurveDataLinear::CurveDataLinear() :
		slope(1),
		intercept(0),
		x1(0),
		y1(0),
		x2(1),
		y2(1)
	{
		//
	}


	CurveDataLinear::~CurveDataLinear()
	{
		//
	}


	void CurveDataLinear::calculate(const std::vector<const CurvePoint *> &points)
	{
		// Get total number of points
		const auto size = (unsigned int) points.size();

		// Calculate mean values (to calculate slope)
		double meanX = 0;
		double meanXY = 0;
		double meanX2 = 0;
		double meanY = 0;

		for (unsigned int i = 0; i < size; i++) {
			const double x = points[i]->getX();
			const double y = points[i]->getY();
			meanX += x;
			meanY += y;
			meanXY += (x * y);
			meanX2 += (x * x);
		}

		// Calculate means
		meanX /= size;
		meanY /= size;
		meanXY /= size;
		meanX2 /= size;

		// Calculate slope and intercept
		slope = ((meanX * meanY) - meanXY) / ((meanX * meanX) - meanX2);
		intercept = meanY - slope * meanX;

		// Calculate begin and end points for curve
		const std::vector<double> point1 = extrapolateToEdge(
			0.0, intercept,
			1.0, intercept + slope
		);
		const std::vector<double> point2 = extrapolateToEdge(
			1.0, intercept + slope,
			0.0, intercept
		);

		// Store points
		x1 = point1[0];
		y1 = point1[1];
		x2 = point2[0];
		y2 = point2[1];
	}


	std::vector<double> CurveDataLinear::extrapolateToEdge(
		const double fromX, const double fromY,
		const double toX, const double toY,
		const double boundsMinX, const double boundsMaxX,
		const double boundsMinY, const double boundsMaxY
	)
	{
		// Calculate distance and angles
		const double distanceX = toX - fromX;
		const double distanceY = toY - fromY;
		const double radians = std::atan2(distanceY, distanceX);

		// Distance to sides
		const double distanceLeft = boundsMinX - fromX;
		const double distanceRight = boundsMaxX - fromX;
		const double distanceTop = boundsMinY - fromY;
		const double distanceBottom = boundsMaxY - fromY;

		// Angles to corners
		const double angle0 = 0;
		const double angle90 = M_PI / 2.0;
		const double angle180 = M_PI;
		const double angleA = std::atan2(distanceTop, distanceLeft);
		const double angleB = std::atan2(distanceTop, distanceRight);
		const double angleC = std::atan2(distanceBottom, distanceRight);
		const double angleD = std::atan2(distanceBottom, distanceLeft);

		// Check if this is a horizontal or vertical line
		const bool isHorizontal = (radians == angle0 || radians == angle180 || radians == -angle180);
		const bool isVertical = (radians == angle90 || radians == -angle90);

		// Calculate end points if one of the distances is zero
		double endX = (isVertical) ? fromX : (radians > -angle90 && radians < angle90) ? boundsMaxX : boundsMinX;
		double endY = (isHorizontal) ? fromY : (radians > angle0 && radians < angle180) ? boundsMaxY : boundsMinY;

		// Only calculate when we don't have a direct match with
		// any horizontal, directional or corner line
		if (!isHorizontal &&
			!isVertical &&
			radians != angleA &&
			radians != angleB &&
			radians != angleC &&
			radians != angleD
			) {

			// Get tangents
			const double tan = std::tan(radians);
			const double tanInv = std::tan((M_PI / 2.0) - radians);

			// Calculate offset
			if (radians > angleA && radians < angleB) {
				endX = distanceTop * tanInv;
				endY = distanceTop;
			} else if (radians > angleB && radians < angleC) {
				endX = distanceRight;
				endY = distanceRight * tan;
			} else if (radians > angleC && radians < angleD) {
				endX = distanceBottom * tanInv;
				endY = distanceBottom;
			} else {
				endX = distanceLeft;
				endY = distanceLeft * tan;
			}

			// Append start point
			endX += fromX;
			endY += fromY;
		}

		// Save in point
		return {endX, endY};
	}


	double CurveDataLinear::getX1() const
	{
		return x1;
	}


	double CurveDataLinear::getY1() const
	{
		return y1;
	}


	double CurveDataLinear::getX2() const
	{
		return x2;
	}


	double CurveDataLinear::getY2() const
	{
		return y2;
	}

}
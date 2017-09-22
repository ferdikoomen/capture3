#ifndef CAPTURE3_COLOR_DISTANCE_UTILS_H
#define CAPTURE3_COLOR_DISTANCE_UTILS_H


#include <cmath>
#include <vector>


namespace Capture3
{

	static double calculateDeltaChroma(
		const double *LAB1,
		const double *LAB2
	)
	{
		// Convert to regular LAB range
		const double A1 = LAB1[1] * 256.0 - 128.0;
		const double B1 = LAB1[2] * 256.0 - 128.0;
		const double A2 = LAB2[1] * 256.0 - 128.0;
		const double B2 = LAB2[2] * 256.0 - 128.0;

		// Calculate chroma
		const double chroma1 = std::sqrt(A1 * A1 + B1 * B1);
		const double chroma2 = std::sqrt(A2 * A2 + B2 * B2);

		// Return difference
		return std::abs(chroma1 - chroma2);
	}


	static double calculateDeltaLightness(
		const double *LAB1,
		const double *LAB2
	)
	{
		// Convert to regular LAB range
		const double L1 = LAB1[0] * 100.0;
		const double L2 = LAB2[0] * 100.0;

		// Return difference
		return L1 - L2;
	}


	static double calculateDeltaCIE1976(
		const double *LAB1,
		const double *LAB2
	)
	{
		// Convert to regular LAB range
		const double L1 = LAB1[0] * 100.0;
		const double A1 = LAB1[1] * 256.0 - 128.0;
		const double B1 = LAB1[2] * 256.0 - 128.0;
		const double L2 = LAB2[0] * 100.0;
		const double A2 = LAB2[1] * 256.0 - 128.0;
		const double B2 = LAB2[2] * 256.0 - 128.0;

		// Get distance between LAB values
		const double deltaL = L1 - L2;
		const double deltaA = A1 - A2;
		const double deltaB = B1 - B2;

		// Standard Euclidean Distance formula
		return std::sqrt(deltaL * deltaL + deltaA * deltaA + deltaB * deltaB);
	}


	static double calculateDeltaCIE2000(
		const double *LAB1,
		const double *LAB2
	)
	{
		// Adapted from Sharma et al's MATLAB implementation at
		// http://www.ece.rochester.edu/~gsharma/ciede2000/
		// http://www.ece.rochester.edu/~gsharma/ciede2000/dataNprograms/deltaE2000.m

		// Convert to regular LAB range
		const double L1 = LAB1[0] * 100.0;
		const double A1 = LAB1[1] * 256.0 - 128.0;
		const double B1 = LAB1[2] * 256.0 - 128.0;
		const double L2 = LAB2[0] * 100.0;
		const double A2 = LAB2[1] * 256.0 - 128.0;
		const double B2 = LAB2[2] * 256.0 - 128.0;

		// Parametric factors, use defaults
		const double kl = 1;
		const double kc = 1;
		const double kh = 1;
		const double pi = M_PI;

		// Compute terms
		const double chroma1 = std::sqrt(A1 * A1 + B1 * B1);
		const double chroma2 = std::sqrt(A2 * A2 + B2 * B2);
		const double chroma = (chroma1 + chroma2) * 0.5;
		const double chroma7 = std::pow(chroma, 7);
		const double g = (1.0 - std::sqrt(chroma7 / (chroma7 + std::pow(25.0, 7)))) * 0.5;
		const double ap1 = (g + 1.0) * A1;
		const double ap2 = (g + 1.0) * A2;
		const double cp1 = std::sqrt(ap1 * ap1 + B1 * B1);
		const double cp2 = std::sqrt(ap2 * ap2 + B2 * B2);
		const double cpp = cp1 * cp2;

		// Ensure hue is between 0 and 2pi
		double hp1 = std::atan2(B1, ap1);
		if (hp1 < 0) {
			hp1 += pi * 2.0;
		}
		double hp2 = std::atan2(B2, ap2);
		if (hp2 < 0) {
			hp2 += pi * 2.0;
		}

		double dl = L2 - L1;
		double dc = cp2 - cp1;
		double dhp = hp2 - hp1;
		if (dhp > +pi) {
			dhp -= pi * 2.0;
		}
		if (dhp < -pi) {
			dhp += pi * 2.0;
		}
		if (cpp == 0) {
			dhp = 0;
		}

		// Note that the defining equations actually need
		// signed Hue and chroma differences which is different
		// from prior color difference formulae
		double dh = std::sqrt(cpp) * std::sin(dhp / 2.0) * 2.0;

		// Weighting functions
		const double lp = (L1 + L2) * 0.5;
		const double cp = (cp1 + cp2) * 0.5;
		const double cp7 = std::pow(cp, 7);

		// Average hue is computed in radians and converted to degrees where needed
		double hp = (hp1 + hp2) * 0.5;

		// Identify positions for which abs hue diff exceeds 180 degrees
		if (std::abs(hp1 - hp2) > pi) {
			hp -= pi;
		}
		if (hp < 0) {
			hp += pi * 2.0;
		}

		// Check if one of the chroma values is zero, in which case set
		// mean hue to the sum which is equivalent to other value
		if (cpp == 0) {
			hp = hp1 + hp2;
		}

		const double lpm502 = (lp - 50.0) * (lp - 50.0);
		const double sl = 1.0 + 0.015 * lpm502 / std::sqrt(20.0 + lpm502);
		const double sc = 1.0 + 0.045 * cp;
		const double t = 1
						 - 0.17 * std::cos(hp - pi / 6.0)
						 + 0.24 * std::cos(2.0 * hp)
						 + 0.32 * std::cos(3.0 * hp + pi / 30.0)
						 - 0.20 * std::cos(4.0 * hp - 63.0 * pi / 180.0);
		const double sh = 1.0 + 0.015 * cp * t;
		const double ex = (180.0 / pi * hp - 275.0) / 25.0;
		const double d = (30.0 * pi / 180.0) * std::exp(-1 * (ex * ex));
		const double rc = 2.0 * std::sqrt(cp7 / (cp7 + std::pow(25.0, 7)));
		const double rt = -1.0 * std::sin(2.0 * d) * rc;

		dl = dl / (kl * sl);
		dc = dc / (kc * sc);
		dh = dh / (kh * sh);

		// The CIE 2000 color difference
		return std::sqrt(dl * dl + dc * dc + dh * dh + rt * dc * dh);
	}

}


#endif // CAPTURE3_COLOR_DISTANCE_UTILS_H

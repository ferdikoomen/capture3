#include "CurveDataLowess.h"


namespace Capture3
{

	CurveDataLowess::CurveDataLowess() :
		pointsX(),
		pointsY()
	{
		//
	}


	CurveDataLowess::~CurveDataLowess()
	{
		pointsX.clear();
		pointsY.clear();
	}


	void CurveDataLowess::calculate(
		const std::vector<const CurvePoint *> &points,
		const double span,
		const unsigned int steps
	)
	{
		// Get total number of points
		const auto size = (unsigned int) points.size();

		// Return if there are not enough points
		if (size < 3) {
			pointsX = {0.0, 0.5, 1.0};
			pointsY = {0.0, 0.5, 1.0};
			return;
		}

		// Create data
		std::vector<double> x(size);
		std::vector<double> y(size);
		std::vector<double> weights(size, 0);
		std::vector<double> residuals(size, 0);
		std::vector<double> result(size, 0);

		// Copy positions
		for (unsigned int i = 0; i < size; i++) {
			x[i] = points[i]->getX();
			y[i] = points[i]->getY();
		}

		// Estimate delta values
		const double xmin = x.front();
		const double xmax = x.back();
		const double delta = 0.01 * std::abs(xmax - xmin);

		// Apply smoothing
		lowess(
			x.data(),
			y.data(),
			size,
			weights.data(),
			residuals.data(),
			result.data(),
			span,
			steps,
			delta
		);

		// Copy result
		pointsX.resize(size);
		pointsY.resize(size);
		for (unsigned int i = 0; i < size; i++) {
			pointsX[i] = x[i];
			pointsY[i] = result[i];
		}
	}


	void CurveDataLowess::lowess(
		const double *x,
		const double *y,
		const unsigned int size,
		double *weights,
		double *residuals,
		double *result,
		const double span,
		const unsigned int steps,
		const double delta
	)
	{
		unsigned int i, iteration, j, last, m1, m2, left, right, ns;
		double alpha, c1, c9, cmad, cut, d1, d2, denom, r;
		bool ok;

		if (size < 2) {
			result[0] = y[0];
			return;
		}

		x--;
		y--;
		result--;

		ns = (unsigned int) std::max(2, std::min(int(size), (int) (span * size + 1e-7)));

		iteration = 1;
		while (iteration <= steps + 1) {
			left = 1;
			right = ns;
			last = 0;
			i = 1;

			while (true) {
				if (right < size) {
					d1 = x[i] - x[left];
					d2 = x[right + 1] - x[i];
					if (d1 > d2) {
						left++;
						right++;
						continue;
					}
				}

				lowest(&x[1], &y[1], size, x[i], result[i], left, right, residuals, iteration > 1, weights, ok);

				if (!ok) {
					result[i] = y[i];
				}

				if (last < i - 1) {
					denom = x[i] - x[last];
					for (j = last + 1; j < i; j++) {
						alpha = (x[j] - x[last]) / denom;
						result[j] = alpha * result[i] + (1.0 - alpha) * result[last];
					}
				}

				last = i;

				cut = x[last] + delta;
				for (i = last + 1; i <= size; i++) {
					if (x[i] > cut) {
						break;
					}
					if (x[i] == x[last]) {
						result[i] = result[last];
						last = i;
					}
				}
				i = std::max(last + 1, i - 1);
				if (last >= size) {
					break;
				}
			}

			for (i = 0; i < size; i++) {
				residuals[i] = y[i + 1] - result[i + 1];
			}

			if (iteration > steps) {
				break;
			}
			for (i = 0; i < size; i++) {
				weights[i] = std::abs(residuals[i]);
			}

			m1 = size / 2;

			sort(weights, size, m1);
			if (size % 2 == 0) {
				m2 = size - m1 - 1;
				sort(weights, size, m2);
				cmad = 3.0 * (weights[m1] + weights[m2]);
			} else {
				cmad = 6.0 * weights[m1];
			}

			c9 = 0.999 * cmad;
			c1 = 0.001 * cmad;
			for (i = 0; i < size; i++) {
				r = std::abs(residuals[i]);
				if (r <= c1) {
					weights[i] = 1.0;
				} else if (r <= c9) {
					weights[i] = (1.0 - (r / cmad) * (r / cmad)) * (1.0 - (r / cmad) * (r / cmad));
				} else {
					weights[i] = 0.0;
				}
			}
			iteration++;
		}
	}


	void CurveDataLowess::lowest(
		const double *x,
		const double *y,
		const unsigned int size,
		const double &xs,
		double &ys,
		const unsigned int left,
		const unsigned int right,
		double *residuals,
		const bool useWeights,
		const double *weights,
		bool &ok
	)
	{
		unsigned int nrt, j;
		double a, b, c, d, h, h1, h9, r, range;

		x--;
		y--;
		residuals--;
		weights--;

		range = x[size] - x[1];
		h = std::max(xs - x[left], x[right] - xs);
		h9 = 0.999 * h;
		h1 = 0.001 * h;

		a = 0.0;
		j = left;
		while (j <= size) {
			residuals[j] = 0.0;
			r = std::abs(x[j] - xs);
			if (r <= h9) {
				if (r <= h1) {
					residuals[j] = 1.0;
				} else {
					d = (r / h) * (r / h) * (r / h);
					residuals[j] = (1.0 - d) * (1.0 - d) * (1.0 - d);
				}
				if (useWeights) {
					residuals[j] *= weights[j];
				}
				a += residuals[j];
			} else if (x[j] > xs) {
				break;
			}
			j = j + 1;
		}

		nrt = j - 1;
		if (a <= 0.0) {
			ok = false;
		} else {
			ok = true;
			for (j = left; j <= nrt; j++) {
				residuals[j] /= a;
			}
			if (h > 0.0) {
				a = 0.0;
				for (j = left; j <= nrt; j++) {
					a += residuals[j] * x[j];
				}
				b = xs - a;
				c = 0.0;
				for (j = left; j <= nrt; j++) {
					c += residuals[j] * (x[j] - a) * (x[j] - a);
				}
				if (std::sqrt(c) > 0.001 * range) {
					b /= c;
					for (j = left; j <= nrt; j++) {
						residuals[j] *= (b * (x[j] - a) + 1.0);
					}
				}
			}
			ys = 0.0;
			for (j = left; j <= nrt; j++) {
				ys += residuals[j] * y[j];
			}
		}
	}


	void CurveDataLowess::sort(double *x, const unsigned int n, const unsigned int k)
	{
		double v, w;
		unsigned int pl, pr, i, j;

		for (pl = 0, pr = n - 1; pl < pr;) {
			v = x[k];
			for (i = pl, j = pr; i <= j;) {
				while (rcmp(x[i], v) < 0) {
					i++;
				}
				while (rcmp(v, x[j]) < 0) {
					j--;
				}
				if (i <= j) {
					w = x[i];
					x[i++] = x[j];
					x[j--] = w;
				}
			}
			if (j < k) {
				pl = i;
			}
			if (k < i) {
				pr = j;
			}
		}
	}


	int CurveDataLowess::rcmp(const double x, const double y)
	{
		if (x < y) {
			return -1;
		}
		if (x > y) {
			return 1;
		}
		return 0;
	}


	const std::vector<double> &CurveDataLowess::getPointsX() const
	{
		return pointsX;
	}


	const std::vector<double> &CurveDataLowess::getPointsY() const
	{
		return pointsY;
	}

}
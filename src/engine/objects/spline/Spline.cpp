#include "Spline.h"


namespace Capture3
{

	Spline::Spline() :
		mx(),
		my(),
		ma(),
		mb(),
		mc(),
		mb0(0),
		mc0(0),
		left(2),
		right(2),
		valueLeft(0.0),
		valueRight(0.0),
		forceExtrapolation(false)
	{
		// Adapted from http://kluge.in-chemnitz.de/opensource/spline/
	}


	Spline::~Spline()
	{
		mx.clear();
		my.clear();
		ma.clear();
		mb.clear();
		mc.clear();
	}


	void Spline::setBoundary(
		const unsigned int left, const double valueLeft,
		const unsigned int right, const double valueRight,
		const bool forceExtrapolation
	)
	{
		this->left = left;
		this->right = right;
		this->valueLeft = valueLeft;
		this->valueRight = valueRight;
		this->forceExtrapolation = forceExtrapolation;
	}


	void Spline::setPoints(
		const std::vector<double> &x,
		const std::vector<double> &y,
		const bool cubicSpline
	)
	{
		const auto n = (unsigned int) x.size();

		mx.resize(n);
		my.resize(n);
		for (unsigned int i = 0; i < n; i++) {
			mx[i] = x[i];
			my[i] = y[i];
		}

		if (cubicSpline) {

			SplineMatrix matrix(n, 1, 1);
			std::vector<double> rhs(n);

			for (unsigned int i = 1; i < n - 1; i++) {
				matrix.at(i, i - 1) = 1.0 / 3.0 * (x[i] - x[i - 1]);
				matrix.at(i, i) = 2.0 / 3.0 * (x[i + 1] - x[i - 1]);
				matrix.at(i, i + 1) = 1.0 / 3.0 * (x[i + 1] - x[i]);
				rhs[i] = (y[i + 1] - y[i]) / (x[i + 1] - x[i]) - (y[i] - y[i - 1]) / (x[i] - x[i - 1]);
			}

			if (left == 2) {
				matrix.at(0, 0) = 2.0;
				matrix.at(0, 1) = 0.0;
				rhs[0] = valueLeft;
			} else if (left == 1) {
				matrix.at(0, 0) = 2.0 * (x[1] - x[0]);
				matrix.at(0, 1) = 1.0 * (x[1] - x[0]);
				rhs[0] = 3.0 * ((y[1] - y[0]) / (x[1] - x[0]) - valueLeft);
			}

			if (right == 2) {
				matrix.at(n - 1, n - 1) = 2.0;
				matrix.at(n - 1, n - 2) = 0.0;
				rhs[n - 1] = valueRight;
			} else if (right == 1) {
				matrix.at(n - 1, n - 1) = 2.0 * (x[n - 1] - x[n - 2]);
				matrix.at(n - 1, n - 2) = 1.0 * (x[n - 1] - x[n - 2]);
				rhs[n - 1] = 3.0 * (valueRight - (y[n - 1] - y[n - 2]) / (x[n - 1] - x[n - 2]));
			}

			mb = matrix.solveLU(rhs);

			ma.resize(n);
			mc.resize(n);
			for (unsigned int i = 0; i < n - 1; i++) {
				ma[i] = 1.0 / 3.0 * (mb[i + 1] - mb[i]) / (x[i + 1] - x[i]);
				mc[i] = (y[i + 1] - y[i]) / (x[i + 1] - x[i]) - 1.0 / 3.0 * (2.0 * mb[i] + mb[i + 1]) * (x[i + 1] - x[i]);
			}
		} else {
			ma.resize(n);
			mb.resize(n);
			mc.resize(n);
			for (unsigned int i = 0; i < n - 1; i++) {
				ma[i] = 0.0;
				mb[i] = 0.0;
				mc[i] = (my[i + 1] - my[i]) / (mx[i + 1] - mx[i]);
			}
		}

		mb0 = (!forceExtrapolation) ? mb[0] : 0.0;
		mc0 = mc[0];

		const double h = x[n - 1] - x[n - 2];
		ma[n - 1] = 0.0;
		mc[n - 1] = 3.0 * ma[n - 2] * h * h + 2.0 * mb[n - 2] * h + mc[n - 2];

		if (forceExtrapolation) {
			mb[n - 1] = 0.0;
		}
	}


	double Spline::at(const double x) const
	{
		const auto n = (unsigned int) mx.size();

		std::vector<double>::const_iterator it;
		it = std::lower_bound(mx.begin(), mx.end(), x);
		const int idx = std::max(int(it - mx.begin()) - 1, 0);

		const double h = x - mx[idx];
		double interpol;
		if (x < mx[0]) {
			interpol = (mb0 * h + mc0) * h + my[0];
		} else if (x > mx[n - 1]) {
			interpol = (mb[n - 1] * h + mc[n - 1]) * h + my[n - 1];
		} else {
			interpol = ((ma[idx] * h + mb[idx]) * h + mc[idx]) * h + my[idx];
		}
		return interpol;
	}


	double Spline::deriv(const unsigned int order, const double x) const
	{
		const auto n = (unsigned int) mx.size();

		std::vector<double>::const_iterator it;
		it = std::lower_bound(mx.begin(), mx.end(), x);
		const int idx = std::max(int(it - mx.begin()) - 1, 0);

		const double h = x - mx[idx];
		double interpol;

		if (x < mx[0]) {
			switch (order) {
				case 1:
					interpol = 2.0 * mb0 * h + mc0;
					break;
				case 2:
					interpol = 2.0 * mb0 * h;
					break;
				default:
					interpol = 0.0;
					break;
			}
		} else if (x > mx[n - 1]) {
			switch (order) {
				case 1:
					interpol = 2.0 * mb[n - 1] * h + mc[n - 1];
					break;
				case 2:
					interpol = 2.0 * mb[n - 1];
					break;
				default:
					interpol = 0.0;
					break;
			}
		} else {
			switch (order) {
				case 1:
					interpol = (3.0 * ma[idx] * h + 2.0 * mb[idx]) * h + mc[idx];
					break;
				case 2:
					interpol = 6.0 * ma[idx] * h + 2.0 * mb[idx];
					break;
				case 3:
					interpol = 6.0 * ma[idx];
					break;
				default:
					interpol = 0.0;
					break;
			}
		}
		return interpol;
	}

}
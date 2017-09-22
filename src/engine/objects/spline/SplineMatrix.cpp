#include "SplineMatrix.h"


namespace Capture3
{

	SplineMatrix::SplineMatrix() :
		upper(),
		lower()
	{
		// Adapted from http://kluge.in-chemnitz.de/opensource/spline/
	}


	SplineMatrix::SplineMatrix(const unsigned int dim, const unsigned int nu, const unsigned int nl) :
		upper(),
		lower()
	{
		resize(dim, nu, nl);
	}


	SplineMatrix::~SplineMatrix()
	{
		upper.clear();
		lower.clear();
	}


	void SplineMatrix::resize(const unsigned int dim, const unsigned int nu, const unsigned int nl)
	{
		upper.resize(nu + 1);
		lower.resize(nl + 1);

		for (auto &i : upper) {
			i.resize(dim);
		}
		for (auto &i : lower) {
			i.resize(dim);
		}
	}


	unsigned int SplineMatrix::dim() const
	{
		if (!upper.empty()) {
			return (unsigned int) upper.front().size();
		} else {
			return 0;
		}
	}


	unsigned int SplineMatrix::numUpper() const
	{
		return (unsigned int) upper.size() - 1;
	}


	unsigned int SplineMatrix::numLower() const
	{
		return (unsigned int) lower.size() - 1;
	}


	double &SplineMatrix::at(const int i, const int j)
	{
		const int k = j - i;
		if (k >= 0) {
			return upper[k][i];
		} else {
			return lower[-k][i];
		}
	}


	double SplineMatrix::at(const int i, const int j) const
	{
		const int k = j - i;
		if (k >= 0) {
			return upper[k][i];
		} else {
			return lower[-k][i];
		}
	}


	double &SplineMatrix::savedDiag(const int i)
	{
		return lower.front()[i];
	}


	double SplineMatrix::savedDiag(const int i) const
	{
		return lower.front()[i];
	}


	void SplineMatrix::decompose()
	{
		for (int i = 0; i < dim(); i++) {
			savedDiag(i) = 1.0 / at(i, i);
			const int min = (int) std::max(0, i - (int) numLower());
			const int max = std::min(dim() - 1, i + numUpper());
			for (int j = min; j <= max; j++) {
				at(i, j) *= savedDiag(i);
			}
			at(i, i) = 1.0;
		}

		for (int k = 0; k < dim(); k++) {
			const int max = std::min(dim() - 1, k + numLower());
			for (int i = k + 1; i <= max; i++) {
				const double x = -at(i, k) / at(k, k);
				at(i, k) = -x;
				const int max2 = std::min(dim() - 1, k + numUpper());
				for (int j = k + 1; j <= max2; j++) {
					at(i, j) = at(i, j) + x * at(k, j);
				}
			}
		}
	}


	std::vector<double> SplineMatrix::solveR(const std::vector<double> &b) const
	{
		std::vector<double> x(dim());
		for (int i = dim() - 1; i >= 0; i--) {
			double sum = 0;
			const int stop = std::min(dim() - 1, i + numUpper());
			for (int j = i + 1; j <= stop; j++) {
				sum += at(i, j) * x[j];
			}
			x[i] = (b[i] - sum) / at(i, i);
		}
		return x;
	}


	std::vector<double> SplineMatrix::solveL(const std::vector<double> &b) const
	{
		std::vector<double> x(dim());
		for (int i = 0; i < dim(); i++) {
			double sum = 0;
			const int start = std::max(0, i - (int) numLower());
			for (int j = start; j < i; j++) {
				sum += at(i, j) * x[j];
			}
			x[i] = (b[i] * savedDiag(i)) - sum;
		}
		return x;
	}


	std::vector<double> SplineMatrix::solveLU(const std::vector<double> &b, bool decomposed)
	{
		if (!decomposed) {
			decompose();
		}
		const std::vector<double> y = solveL(b);
		const std::vector<double> x = solveR(y);
		return x;
	}

}
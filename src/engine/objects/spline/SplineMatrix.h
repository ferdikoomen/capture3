#ifndef CAPTURE3_SPLINE_MATRIX_H
#define CAPTURE3_SPLINE_MATRIX_H


#include <cmath>
#include <vector>
#include <algorithm>


namespace Capture3
{

	class SplineMatrix final
	{

		public:
			SplineMatrix();

			SplineMatrix(const unsigned int dim, const unsigned int nu, const unsigned int nl);

			virtual ~SplineMatrix();

			void resize(const unsigned int dim, const unsigned int nu, const unsigned int nl);

			unsigned int dim() const;

			unsigned int numUpper() const;

			unsigned int numLower() const;

			double &at(const int i, const int j);

			double at(const int i, const int j) const;

			double &savedDiag(const int i);

			double savedDiag(const int i) const;

			void decompose();

			std::vector<double> solveR(const std::vector<double> &b) const;

			std::vector<double> solveL(const std::vector<double> &b) const;

			std::vector<double> solveLU(const std::vector<double> &b, bool decomposed = false);

		private:
			std::vector<std::vector<double> > upper;
			std::vector<std::vector<double> > lower;

	};
}

#endif // CAPTURE3_SPLINE_MATRIX_H
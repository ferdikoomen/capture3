#ifndef CAPTURE3_COLOR_MATRIX_H
#define CAPTURE3_COLOR_MATRIX_H


#include <vector>
#include <cmath>
#include <omp.h>


namespace Capture3
{
	class ColorMatrix final
	{
		public:
			ColorMatrix();

			virtual ~ColorMatrix();

			void reset();

			void setData(
				const double m11, const double m12, const double m13, const double m14,
				const double m21, const double m22, const double m23, const double m24,
				const double m31, const double m32, const double m33, const double m34
			);

			const double *getData();

			double getX(const double x, const double y, const double z);

			double getY(const double x, const double y, const double z);

			double getZ(const double x, const double y, const double z);

		private:
			static const unsigned int M11 = 0;
			static const unsigned int M12 = 1;
			static const unsigned int M13 = 2;
			static const unsigned int M14 = 3;
			static const unsigned int M21 = 4;
			static const unsigned int M22 = 5;
			static const unsigned int M23 = 6;
			static const unsigned int M24 = 7;
			static const unsigned int M31 = 8;
			static const unsigned int M32 = 9;
			static const unsigned int M33 = 10;
			static const unsigned int M34 = 11;

			double data[12];

	};
}

#endif // CAPTURE3_COLOR_MATRIX_H

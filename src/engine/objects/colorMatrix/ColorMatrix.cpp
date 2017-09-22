#include "ColorMatrix.h"


namespace Capture3
{

	ColorMatrix::ColorMatrix() :
		data{
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0
		}
	{
		//
	}


	ColorMatrix::~ColorMatrix()
	{
		//
	}

	void ColorMatrix::reset()
	{
		setData(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0
		);
	}

	void ColorMatrix::setData(
		const double m11, const double m12, const double m13, const double m14,
		const double m21, const double m22, const double m23, const double m24,
		const double m31, const double m32, const double m33, const double m34
	)
	{
		data[M11] = m11;
		data[M12] = m12;
		data[M13] = m13;
		data[M14] = m14;
		data[M21] = m21;
		data[M22] = m22;
		data[M23] = m23;
		data[M24] = m24;
		data[M31] = m31;
		data[M32] = m32;
		data[M33] = m33;
		data[M34] = m34;
	}


	const double *ColorMatrix::getData()
	{
		return data;
	}


	double ColorMatrix::getX(const double x, const double y, const double z)
	{
		return x * data[M11] + y * data[M12] + z * data[M13] + data[M14];
	}


	double ColorMatrix::getY(const double x, const double y, const double z)
	{
		return x * data[M21] + y * data[M22] + z * data[M23] + data[M24];
	}


	double ColorMatrix::getZ(const double x, const double y, const double z)
	{
		return x * data[M31] + y * data[M32] + z * data[M33] + data[M34];
	}
}
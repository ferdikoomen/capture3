#include "ColorChartPatch.h"


namespace Capture3
{

	ColorChartPatch::ColorChartPatch(
		const QString &label,
		const double l,
		const double a,
		const double b
	) :
		label(label),

		// Colors
		rgb8{0, 0, 0},
		rgb{0, 0, 0},
		hsb{0, 0, 0},
		xyz{0, 0, 0},
		xyv{0, 0, 0},
		lab{0, 0, 0}
	{
		// Convert LAB input values to 0-1 range
		setLAB(
			(l / 100.0),
			(a + 128.0) / 256.0,
			(b + 128.0) / 256.0
		);
	}


	ColorChartPatch::~ColorChartPatch()
	{
		//
	}


	void ColorChartPatch::update()
	{
		// Convert to gamma corrected 8 bit RGB values
		rgb8[0] = to8Bit(applyGamma(rgb[0]));
		rgb8[1] = to8Bit(applyGamma(rgb[1]));
		rgb8[2] = to8Bit(applyGamma(rgb[2]));
	}


	void ColorChartPatch::setRGB(const double r, const double g, const double b, const bool convert)
	{
		rgb[0] = r;
		rgb[1] = g;
		rgb[2] = b;

		if (convert) {
			RGBtoHSB(rgb, hsb, 1);
			RGBtoXYZ(rgb, xyz, 1);
			XYZtoLAB(xyz, lab, 1);
			XYZtoXYV(xyz, xyv, 1);
			update();
		}
	}


	void ColorChartPatch::setHSB(const double h, const double s, const double b, const bool convert)
	{
		hsb[0] = h;
		hsb[1] = s;
		hsb[2] = b;

		if (convert) {
			HSBtoRGB(hsb, rgb, 1);
			RGBtoXYZ(rgb, xyz, 1);
			XYZtoLAB(xyz, lab, 1);
			XYZtoXYV(xyz, xyv, 1);
			update();
		}
	}


	void ColorChartPatch::setXYZ(const double x, const double y, const double z, const bool convert)
	{
		xyz[0] = x;
		xyz[1] = y;
		xyz[2] = z;

		if (convert) {
			XYZtoXYV(xyz, xyv, 1);
			XYZtoLAB(xyz, lab, 1);
			XYZtoRGB(xyz, rgb, 1);
			RGBtoHSB(rgb, hsb, 1);
			update();
		}
	}


	void ColorChartPatch::setXYV(const double x, const double y, const double v, const bool convert)
	{
		xyv[0] = x;
		xyv[1] = y;
		xyv[2] = v;

		if (convert) {
			XYVtoXYZ(xyv, xyz, 1);
			XYZtoLAB(xyz, lab, 1);
			XYZtoRGB(xyz, rgb, 1);
			RGBtoHSB(rgb, hsb, 1);
			update();
		}
	}


	void ColorChartPatch::setLAB(const double l, const double a, const double b, const bool convert)
	{
		lab[0] = l;
		lab[1] = a;
		lab[2] = b;

		if (convert) {
			LABtoXYZ(lab, xyz, 1);
			XYZtoXYV(xyz, xyv, 1);
			XYZtoRGB(xyz, rgb, 1);
			RGBtoHSB(rgb, hsb, 1);
			update();
		}
	}


	const unsigned int *ColorChartPatch::getRGB8() const
	{
		return rgb8;
	}


	const double *ColorChartPatch::getRGB() const
	{
		return rgb;
	}


	const double *ColorChartPatch::getHSB() const
	{
		return hsb;
	}


	const double *ColorChartPatch::getXYZ() const
	{
		return xyz;
	}


	const double *ColorChartPatch::getXYV() const
	{
		return xyv;
	}


	const double *ColorChartPatch::getLAB() const
	{
		return lab;
	}


	QString ColorChartPatch::getLabel() const
	{
		return label;
	}


	QPixmap ColorChartPatch::getPreview() const
	{
		QPixmap preview(15, 15);
		preview.fill(QColor(
			rgb8[0],
			rgb8[1],
			rgb8[2]
		));
		return preview;
	}
}
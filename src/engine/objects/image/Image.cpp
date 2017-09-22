#include "Image.h"


namespace Capture3
{

	Image::Image(const unsigned int width, const unsigned int height) :
		size(width, height),

		// Image color spaces
		rgb(size),
		hsb(size),
		xyz(size),
		xyv(size),
		lab(size),

		// Meta information
		meta()
	{
		//
	}


	Image::~Image()
	{
		//
	}


	void Image::read(const QString &path)
	{
		readBytes(rgb.getData(), size.getBytes(), path + "_RGB.RAW");
		readBytes(hsb.getData(), size.getBytes(), path + "_HSB.RAW");
		readBytes(xyz.getData(), size.getBytes(), path + "_XYZ.RAW");
		readBytes(xyv.getData(), size.getBytes(), path + "_XYV.RAW");
		readBytes(lab.getData(), size.getBytes(), path + "_LAB.RAW");
	}


	void Image::write(const QString &path)
	{
		writeBytes(rgb.getData(), size.getBytes(), path + "_RGB.RAW");
		writeBytes(hsb.getData(), size.getBytes(), path + "_HSB.RAW");
		writeBytes(xyz.getData(), size.getBytes(), path + "_XYZ.RAW");
		writeBytes(xyv.getData(), size.getBytes(), path + "_XYV.RAW");
		writeBytes(lab.getData(), size.getBytes(), path + "_LAB.RAW");
	}


	void Image::gammaCorrection()
	{
		applyGamma(rgb.getData(), size.getBytes());
	}


	void Image::inverseGammaCorrection()
	{
		applyInverseGamma(rgb.getData(), size.getBytes());
	}


	void Image::convertRGB(const bool gammaCorrected)
	{
		RGBtoHSB(rgb.getData(), hsb.getData(), size.getArea(), gammaCorrected);
		RGBtoXYZ(rgb.getData(), xyz.getData(), size.getArea(), gammaCorrected);
		XYZtoLAB(xyz.getData(), lab.getData(), size.getArea());
		XYZtoXYV(xyz.getData(), xyv.getData(), size.getArea());
	}


	void Image::convertHSB(const bool gammaCorrected)
	{
		HSBtoRGB(hsb.getData(), rgb.getData(), size.getArea(), gammaCorrected);
		RGBtoXYZ(rgb.getData(), xyz.getData(), size.getArea(), gammaCorrected);
		XYZtoLAB(xyz.getData(), lab.getData(), size.getArea());
		XYZtoXYV(xyz.getData(), xyv.getData(), size.getArea());
	}


	void Image::convertXYZ(const bool gammaCorrected)
	{
		XYZtoXYV(xyz.getData(), xyv.getData(), size.getArea());
		XYZtoLAB(xyz.getData(), lab.getData(), size.getArea());
		XYZtoRGB(xyz.getData(), rgb.getData(), size.getArea(), gammaCorrected);
		RGBtoHSB(rgb.getData(), hsb.getData(), size.getArea(), gammaCorrected);
	}


	void Image::convertXYV(const bool gammaCorrected)
	{
		XYVtoXYZ(xyv.getData(), xyz.getData(), size.getArea());
		XYZtoLAB(xyz.getData(), lab.getData(), size.getArea());
		XYZtoRGB(xyz.getData(), rgb.getData(), size.getArea(), gammaCorrected);
		RGBtoHSB(rgb.getData(), hsb.getData(), size.getArea(), gammaCorrected);
	}


	void Image::convertLAB(const bool gammaCorrected)
	{
		LABtoXYZ(lab.getData(), xyz.getData(), size.getArea());
		XYZtoXYV(xyz.getData(), xyv.getData(), size.getArea());
		XYZtoRGB(xyz.getData(), rgb.getData(), size.getArea(), gammaCorrected);
		RGBtoHSB(rgb.getData(), hsb.getData(), size.getArea(), gammaCorrected);
	}


	ImageChannel &Image::getRGB()
	{
		return rgb;
	}


	ImageChannel &Image::getHSB()
	{
		return hsb;
	}


	ImageChannel &Image::getXYZ()
	{
		return xyz;
	}


	ImageChannel &Image::getXYV()
	{
		return xyv;
	}


	ImageChannel &Image::getLAB()
	{
		return lab;
	}


	ImageMeta &Image::getMeta()
	{
		return meta;
	}


	const ImageSize &Image::getSize() const
	{
		return size;
	}


	const ImageChannel &Image::getRGB() const
	{
		return rgb;
	}


	const ImageChannel &Image::getHSB() const
	{
		return hsb;
	}


	const ImageChannel &Image::getXYZ() const
	{
		return xyz;
	}


	const ImageChannel &Image::getXYV() const
	{
		return xyv;
	}


	const ImageChannel &Image::getLAB() const
	{
		return lab;
	}


	const ImageMeta &Image::getMeta() const
	{
		return meta;
	}

}
#include "ImageHistogramComponent.h"


namespace Capture3
{

	ImageHistogramComponent::ImageHistogramComponent() :
		PanelTabComponent("Histogram"),
		groupRGB("Histogram - RGB"),
		groupHSB("Histogram - HSB"),
		groupXYZ("Histogram - XYZ"),
		groupXYV("Histogram - xyY"),
		groupLAB("Histogram - LAB"),
		itemRGB_R(),
		itemRGB_G(),
		itemRGB_B(),
		itemHSB_H(),
		itemHSB_S(),
		itemHSB_B(),
		itemXYZ_X(),
		itemXYZ_Y(),
		itemXYZ_Z(),
		itemXYV_X(),
		itemXYV_Y(),
		itemXYV_V(),
		itemLAB_L(),
		itemLAB_A(),
		itemLAB_B()
	{
		// Add items
		groupRGB.addWidget(&itemRGB_R);
		groupRGB.addWidget(&itemRGB_G);
		groupRGB.addWidget(&itemRGB_B);
		groupHSB.addWidget(&itemHSB_H);
		groupHSB.addWidget(&itemHSB_S);
		groupHSB.addWidget(&itemHSB_B);
		groupXYZ.addWidget(&itemXYZ_X);
		groupXYZ.addWidget(&itemXYZ_Y);
		groupXYZ.addWidget(&itemXYZ_Z);
		groupXYV.addWidget(&itemXYV_X);
		groupXYV.addWidget(&itemXYV_Y);
		groupXYV.addWidget(&itemXYV_V);
		groupLAB.addWidget(&itemLAB_L);
		groupLAB.addWidget(&itemLAB_A);
		groupLAB.addWidget(&itemLAB_B);
		addWidget(&groupRGB);
		addWidget(&groupHSB);
		addWidget(&groupXYZ);
		addWidget(&groupXYV);
		addWidget(&groupLAB);
	}


	ImageHistogramComponent::~ImageHistogramComponent()
	{
		itemRGB_R.deleteLater();
		itemRGB_G.deleteLater();
		itemRGB_B.deleteLater();
		itemHSB_H.deleteLater();
		itemHSB_S.deleteLater();
		itemHSB_B.deleteLater();
		itemXYZ_X.deleteLater();
		itemXYZ_Y.deleteLater();
		itemXYZ_Z.deleteLater();
		itemXYV_X.deleteLater();
		itemXYV_Y.deleteLater();
		itemXYV_V.deleteLater();
		itemLAB_L.deleteLater();
		itemLAB_A.deleteLater();
		itemLAB_B.deleteLater();
		groupRGB.deleteLater();
		groupHSB.deleteLater();
		groupXYZ.deleteLater();
		groupXYV.deleteLater();
		groupLAB.deleteLater();
	}


	void ImageHistogramComponent::show(const Image *image)
	{
		// Generate images
		generateHistogram(
			image->getSize(),
			image->getRGB(),
			itemRGB_R.getImage(),
			itemRGB_G.getImage(),
			itemRGB_B.getImage()
		);
		generateHistogram(
			image->getSize(),
			image->getHSB(),
			itemHSB_H.getImage(),
			itemHSB_S.getImage(),
			itemHSB_B.getImage()
		);
		generateHistogram(
			image->getSize(),
			image->getXYZ(),
			itemXYZ_X.getImage(),
			itemXYZ_Y.getImage(),
			itemXYZ_Z.getImage()
		);
		generateHistogram(
			image->getSize(),
			image->getXYV(),
			itemXYV_X.getImage(),
			itemXYV_Y.getImage(),
			itemXYV_V.getImage()
		);
		generateHistogram(
			image->getSize(),
			image->getLAB(),
			itemLAB_L.getImage(),
			itemLAB_A.getImage(),
			itemLAB_B.getImage()
		);

		// Redraw
		itemRGB_R.redraw();
		itemRGB_G.redraw();
		itemRGB_B.redraw();
		itemHSB_H.redraw();
		itemHSB_S.redraw();
		itemHSB_B.redraw();
		itemXYZ_X.redraw();
		itemXYZ_Y.redraw();
		itemXYZ_Z.redraw();
		itemXYV_X.redraw();
		itemXYV_Y.redraw();
		itemXYV_V.redraw();
		itemLAB_L.redraw();
		itemLAB_A.redraw();
		itemLAB_B.redraw();
	}


	void ImageHistogramComponent::reset()
	{
		itemRGB_R.reset();
		itemRGB_G.reset();
		itemRGB_B.reset();
		itemHSB_H.reset();
		itemHSB_S.reset();
		itemHSB_B.reset();
		itemXYZ_X.reset();
		itemXYZ_Y.reset();
		itemXYZ_Z.reset();
		itemXYV_X.reset();
		itemXYV_Y.reset();
		itemXYV_V.reset();
		itemLAB_L.reset();
		itemLAB_A.reset();
		itemLAB_B.reset();
	}

}
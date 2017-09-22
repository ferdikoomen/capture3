#include "ImageGraphComponent.h"


namespace Capture3
{

	ImageGraphComponent::ImageGraphComponent() :
		PanelTabComponent("Graph"),
		groupRGB("Graph - RGB"),
		groupHSB("Graph - HSB"),
		groupXYZ("Graph - XYZ"),
		groupXYV("Graph - xyY"),
		groupLAB("Graph - LAB"),
		itemRGB(),
		itemHSB(),
		itemXYZ(),
		itemXYV(),
		itemLAB(),
		positionsRGB(),
		positionsHSB(),
		positionsXYZ(),
		positionsXYV(),
		positionsLAB(),
		colors(),
		countPoints(0),
		countLines(0)
	{
		// Add items
		groupRGB.addWidget(&itemRGB);
		groupHSB.addWidget(&itemHSB);
		groupXYZ.addWidget(&itemXYZ);
		groupXYV.addWidget(&itemXYV);
		groupLAB.addWidget(&itemLAB);
		addWidget(&groupRGB);
		addWidget(&groupHSB);
		addWidget(&groupXYZ);
		addWidget(&groupXYV);
		addWidget(&groupLAB);
	}


	ImageGraphComponent::~ImageGraphComponent()
	{
		reset();
		itemRGB.deleteLater();
		itemHSB.deleteLater();
		itemXYZ.deleteLater();
		itemXYV.deleteLater();
		itemLAB.deleteLater();
		groupRGB.deleteLater();
		groupHSB.deleteLater();
		groupXYZ.deleteLater();
		groupXYV.deleteLater();
		groupLAB.deleteLater();
	}


	void ImageGraphComponent::show(const Image *image)
	{
		// Generate data
		generateGraph(
			image->getSize(),
			image->getRGB(),
			image->getHSB(),
			image->getXYZ(),
			image->getXYV(),
			image->getLAB(),
			positionsRGB,
			positionsHSB,
			positionsXYZ,
			positionsXYV,
			positionsLAB,
			colors,
			countPoints,
			countLines
		);

		// Draw
		itemRGB.draw(positionsRGB, colors, countPoints, countLines);
		itemHSB.draw(positionsHSB, colors, countPoints, countLines);
		itemXYZ.draw(positionsXYZ, colors, countPoints, countLines);
		itemXYV.draw(positionsXYV, colors, countPoints, countLines);
		itemLAB.draw(positionsLAB, colors, countPoints, countLines);
	}


	void ImageGraphComponent::reset()
	{
		itemRGB.reset();
		itemHSB.reset();
		itemXYZ.reset();
		itemXYV.reset();
		itemLAB.reset();
		positionsRGB.clear();
		positionsHSB.clear();
		positionsXYZ.clear();
		positionsXYV.clear();
		positionsLAB.clear();
		colors.clear();
		countPoints = 0;
		countLines = 0;
	}
}
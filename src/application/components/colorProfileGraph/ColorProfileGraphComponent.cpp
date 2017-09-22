#include "ColorProfileGraphComponent.h"


namespace Capture3
{

	ColorProfileGraphComponent::ColorProfileGraphComponent() :
		PanelTabComponent("Color Profile Graph"),
		groupRGB("Color Profile Graph - RGB"),
		groupHSB("Color Profile Graph - HSB"),
		groupXYZ("Color Profile Graph - XYZ"),
		groupXYV("Color Profile Graph - xyY"),
		groupLAB("Color Profile Graph - LAB"),
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


	ColorProfileGraphComponent::~ColorProfileGraphComponent()
	{
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

	void ColorProfileGraphComponent::show(
		const ColorChart *colorChartReference,
		const ColorChart *colorChartDetected
	)
	{
		// Generate data
		generateGraph(
			colorChartReference,
			colorChartDetected,
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


	void ColorProfileGraphComponent::reset()
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
#include "DynamicRangeComponent.h"


namespace Capture3
{

	DynamicRangeComponent::DynamicRangeComponent() :
		PanelTabComponent("Dynamic Range"),

		// Groups
		groupPreview("Preview"),
		groupRow1("Row (X)"),
		groupRow2("Row (Y)"),
		groupRow3("Row (Z)"),

		// Dynamic range preview
		preview(400, 300)
	{
		// Set point size
		preview.setPointSize(2.0f);
		preview.setLineSize(2.0f);

		// Add items
		groupPreview.addWidget(&preview);
		addWidget(&groupPreview);
		// addWidget(&groupRow1);
		// addWidget(&groupRow2);
		// addWidget(&groupRow3);
	}


	DynamicRangeComponent::~DynamicRangeComponent()
	{
		// Cleanup data
		preview.reset();
		preview.deleteLater();
		groupPreview.deleteLater();
		groupRow1.deleteLater();
		groupRow2.deleteLater();
		groupRow3.deleteLater();
	}


	void DynamicRangeComponent::show(const Image *image)
	{
		// TODO:
		// Show HDR image in 3D coordinates, where each pixel is a line with
		// x & y coordinates as planar, z coordinate as vector between dark and light
		// line has start and end color.

		// TODO:
		// Elke pixel heeft een min en max value
		// Je kunt dan de uiteindelijke mix tussen die twee aanpassen
		// - Toon meest lichte pixels (voorkant 3D render)
		// - Toon meest donkere pixels (achterkant 3D render)

		// TODO:
		// - Toon meest gesatureerde pixels -> maak een HDR map en pas een kleine blur toe!
		// - Sample daarna de kleuren uit deze map (RGB zijn losse maps)
	}


	void DynamicRangeComponent::reset()
	{

	}

}
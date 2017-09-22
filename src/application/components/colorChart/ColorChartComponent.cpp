#include "ColorChartComponent.h"


namespace Capture3
{

	ColorChartComponent::ColorChartComponent() :
		PanelTabComponent("Color Chart Patches"),
		group("X-Rite ColorChecker Digital SG (140 patches)"),
		container(),
		table()
	{
		// Set table options
		table.verticalHeader()->hide();
		table.verticalHeader()->setDefaultSectionSize(18);
		table.horizontalHeader()->setDefaultSectionSize(50);
		table.setColumnCount(21);
		table.setRowCount(COLOR_CHART_COUNT);

		// Add headers
		table.setHorizontalHeader(0, "#");
		table.setHorizontalHeader(1, "R");
		table.setHorizontalHeader(2, "G");
		table.setHorizontalHeader(3, "B");
		table.setHorizontalHeader(4, "H");
		table.setHorizontalHeader(5, "S");
		table.setHorizontalHeader(6, "B");
		table.setHorizontalHeader(7, "X");
		table.setHorizontalHeader(8, "Y");
		table.setHorizontalHeader(9, "Z");
		table.setHorizontalHeader(10, "x");
		table.setHorizontalHeader(11, "y");
		table.setHorizontalHeader(12, "Y");
		table.setHorizontalHeader(13, "L");
		table.setHorizontalHeader(14, "A");
		table.setHorizontalHeader(15, "B");
		table.setHorizontalHeader(16, "ΔC");
		table.setHorizontalHeader(17, "ΔL");
		table.setHorizontalHeader(18, "ΔE1976");
		table.setHorizontalHeader(19, "ΔE2000");
		table.setHorizontalHeader(20, "OK");

		// Set width
		table.setColumnWidth(0, 70);
		table.setColumnWidth(1, 45); // RGB_R
		table.setColumnWidth(2, 45); // RGB_G
		table.setColumnWidth(3, 45); // RGB_B
		table.setColumnWidth(4, 45); // HSB_H
		table.setColumnWidth(5, 45); // HSB_S
		table.setColumnWidth(6, 45); // HSB_B
		table.setColumnWidth(7, 50); // XYZ_X
		table.setColumnWidth(8, 50); // XYZ_Y
		table.setColumnWidth(9, 50); // XYZ_Z
		table.setColumnWidth(10, 50); // XYZ_X
		table.setColumnWidth(11, 50); // XYZ_Y
		table.setColumnWidth(12, 50); // XYZ_Z
		table.setColumnWidth(13, 50); // LAB_L
		table.setColumnWidth(14, 50); // LAB_A
		table.setColumnWidth(15, 50); // LAB_B
		table.setColumnWidth(16, 50); // Delta chroma
		table.setColumnWidth(17, 50); // Delta lightness
		table.setColumnWidth(18, 50); // Delta CIE1976
		table.setColumnWidth(19, 60); // Delta CIE2000
		table.setColumnWidth(20, 40); // Result

		// Add items
		group.addWidget(&container);
		addWidget(&group);
		addWidget(&table);

		// Reset image
		reset();
	}


	ColorChartComponent::~ColorChartComponent()
	{
		container.deleteLater();
		group.deleteLater();
		table.deleteLater();
	}


	void ColorChartComponent::show(const ColorProfile *profile)
	{
		// Generate visual
		container.setPixmap(getPixmap(
			generate(
				profile->getChart(),
				window()->devicePixelRatio()
			), window()->devicePixelRatio())
		);

		// Fetch list of patches
		const std::vector<const ColorProfileChartPatch *> &patches = profile->getChart().getPatches();

		// Add list
		for (unsigned int i = 0; i < patches.size(); i++) {

			// Get patch
			const ColorProfileChartPatch *patch = patches[i];
			const ColorChartPatch *patchReference = patch->getPatchReference();
			const ColorChartPatch *patchDetected = patch->getPatchDetected();

			// Get color
			const double *rgb = patchReference->getRGB();
			const double *hsb = patchReference->getHSB();
			const double *xyz = patchReference->getXYZ();
			const double *xyv = patchReference->getXYV();
			const double *lab = patchReference->getLAB();

			// Create items
			table.addItem(i, 0, patchReference->getPreview(), patchReference->getLabel());
			table.addItem(i, 1, (int) std::round(rgb[0] * 255));
			table.addItem(i, 2, (int) std::round(rgb[1] * 255));
			table.addItem(i, 3, (int) std::round(rgb[2] * 255));
			table.addItem(i, 4, (int) std::round(hsb[0] * 360));
			table.addItem(i, 5, (int) std::round(hsb[1] * 100));
			table.addItem(i, 6, (int) std::round(hsb[2] * 100));
			table.addItem(i, 7, xyz[0]);
			table.addItem(i, 8, xyz[1]);
			table.addItem(i, 9, xyz[2]);
			table.addItem(i, 10, xyv[0]);
			table.addItem(i, 11, xyv[1]);
			table.addItem(i, 12, xyv[2]);
			table.addItem(i, 13, (lab[0] * 100));
			table.addItem(i, 14, (lab[1] * 256.0) - 128.0);
			table.addItem(i, 15, (lab[2] * 256.0) - 128.0);
			table.addItem(i, 16, patch->getDeltaChroma());
			table.addItem(i, 17, patch->getDeltaLightness());
			table.addItem(i, 18, patch->getDeltaCIE1976());
			table.addItem(i, 19, patch->getDeltaCIE2000());
			table.addItem(i, 20, patch->isCorrect());
		}
	}


	void ColorChartComponent::reset()
	{
		container.setPixmap(QPixmap());
	}
}
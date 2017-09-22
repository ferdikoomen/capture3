#include "ColorProfileChart.h"


namespace Capture3
{

	ColorProfileChart::ColorProfileChart(
		const ColorChart *colorChartReference,
		const ColorChart *colorChartDetected
	) :
		count((unsigned int) colorChartReference->getPatches().size()),
		patches(count),
		patchesRGB(count),
		patchesHSB(count),
		patchesXYZ(count),
		patchesXYV(count),
		patchesLAB(count)
	{
		const std::vector<ColorChartPatch *> &patchesReference = colorChartReference->getPatches();
		const std::vector<ColorChartPatch *> &patchesDetected = colorChartDetected->getPatches();

		// Copy references to data
		for (unsigned int i = 0; i < count; i++) {

			// Create patch with links to reference and detected data
			const ColorChartPatch *reference = patchesReference[i];
			const ColorChartPatch *detected = patchesDetected[i];
			auto *patch = new ColorProfileChartPatch(reference, detected);

			// We create reference objects with the following data:
			// - Pointer to the color profile patch above
			// - Pointer to the difference value
			// - Pointer to the reference value

			// Afterwards we sort these vectors based on the reference value, this makes
			// calculating the curve easier, since the x-axis is already sorted, but
			// we still have access to all other values we need for the curve.
			// See the ColorProfileCurve class for more info

			patches[i] = patch;
			patchesRGB[i] = new ColorProfileChartPatchData(patch, reference->getRGB(), detected->getRGB());
			patchesHSB[i] = new ColorProfileChartPatchData(patch, reference->getHSB(), detected->getHSB());
			patchesXYZ[i] = new ColorProfileChartPatchData(patch, reference->getXYZ(), detected->getXYZ());
			patchesXYV[i] = new ColorProfileChartPatchData(patch, reference->getXYV(), detected->getXYV());
			patchesLAB[i] = new ColorProfileChartPatchData(patch, reference->getLAB(), detected->getLAB());
		}
	}


	ColorProfileChart::~ColorProfileChart()
	{
		patches.clear();
		patchesRGB.clear();
		patchesHSB.clear();
		patchesXYZ.clear();
		patchesXYV.clear();
		patchesLAB.clear();
	}


	const std::vector<const ColorProfileChartPatch *> &ColorProfileChart::getPatches() const
	{
		return patches;
	}


	const std::vector<const ColorProfileChartPatchData *> &ColorProfileChart::getPatchesRGB() const
	{
		return patchesRGB;
	}


	const std::vector<const ColorProfileChartPatchData *> &ColorProfileChart::getPatchesHSB() const
	{
		return patchesHSB;
	}


	const std::vector<const ColorProfileChartPatchData *> &ColorProfileChart::getPatchesXYZ() const
	{
		return patchesXYZ;
	}


	const std::vector<const ColorProfileChartPatchData *> &ColorProfileChart::getPatchesXYV() const
	{
		return patchesXYV;
	}


	const std::vector<const ColorProfileChartPatchData *> &ColorProfileChart::getPatchesLAB() const
	{
		return patchesLAB;
	}
}
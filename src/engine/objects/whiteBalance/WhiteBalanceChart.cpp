#include "WhiteBalanceChart.h"


namespace Capture3
{

	WhiteBalanceChart::WhiteBalanceChart(
		const ColorChart *colorChartReference,
		const ColorChart *colorChartDetected
	) :
		count((unsigned int) colorChartReference->getPatchesNeutral().size()),
		patches(count),
		patchesRGB(count),
		patchesHSB(count),
		patchesXYZ(count),
		patchesXYV(count),
		patchesLAB(count)
	{
		const std::vector<ColorChartPatch *> &patchesReference = colorChartReference->getPatchesNeutral();
		const std::vector<ColorChartPatch *> &patchesDetected = colorChartDetected->getPatchesNeutral();

		// Copy references to data
		for (unsigned int i = 0; i < count; i++) {

			// Create patch with links to reference and detected data
			const ColorChartPatch *reference = patchesReference[i];
			const ColorChartPatch *detected = patchesDetected[i];
			auto *patch = new WhiteBalanceChartPatch(reference, detected);

			// We create reference objects with the following data:
			// - Pointer to the color profile patch above
			// - Pointer to the difference value
			// - Pointer to the reference value

			// Afterwards we sort these vectors based on the reference value, this makes
			// calculating the curve easier, since the x-axis is already sorted, but
			// we still have access to all other values we need for the curve.
			// See the WhiteBalanceCurve class for more info

			patches[i] = patch;
			patchesRGB[i] = new WhiteBalanceChartPatchData(patch, reference->getRGB(), detected->getRGB());
			patchesHSB[i] = new WhiteBalanceChartPatchData(patch, reference->getHSB(), detected->getHSB());
			patchesXYZ[i] = new WhiteBalanceChartPatchData(patch, reference->getXYZ(), detected->getXYZ());
			patchesXYV[i] = new WhiteBalanceChartPatchData(patch, reference->getXYV(), detected->getXYV());
			patchesLAB[i] = new WhiteBalanceChartPatchData(patch, reference->getLAB(), detected->getLAB());
		}

		// Sort vector on reference lightness value
		std::sort(patches.begin(), patches.end(), [](const WhiteBalanceChartPatch *a, const WhiteBalanceChartPatch *b) {
			return a->getPatchReference()->getLAB()[0] > b->getPatchReference()->getLAB()[0];
		});
	}


	WhiteBalanceChart::~WhiteBalanceChart()
	{
		patches.clear();
		patchesRGB.clear();
		patchesHSB.clear();
		patchesXYZ.clear();
		patchesXYV.clear();
		patchesLAB.clear();
	}


	const std::vector<const WhiteBalanceChartPatch *> &WhiteBalanceChart::getPatches() const
	{
		return patches;
	}


	const std::vector<const WhiteBalanceChartPatchData *> &WhiteBalanceChart::getPatchesRGB() const
	{
		return patchesRGB;
	}


	const std::vector<const WhiteBalanceChartPatchData *> &WhiteBalanceChart::getPatchesHSB() const
	{
		return patchesHSB;
	}


	const std::vector<const WhiteBalanceChartPatchData *> &WhiteBalanceChart::getPatchesXYZ() const
	{
		return patchesXYZ;
	}


	const std::vector<const WhiteBalanceChartPatchData *> &WhiteBalanceChart::getPatchesXYV() const
	{
		return patchesXYV;
	}


	const std::vector<const WhiteBalanceChartPatchData *> &WhiteBalanceChart::getPatchesLAB() const
	{
		return patchesLAB;
	}
}
#include "ColorChart.h"


namespace Capture3
{

	ColorChart::ColorChart() :
		count(COLOR_CHART_COUNT),
		cols(COLOR_CHART_COLS),
		rows(COLOR_CHART_ROWS),

		// CIE Lab data for illuminant D50 and 2 degree observer (CIE 1931)
		// http://www.xrite.com/documents/apps/public/digital_colorchecker_sg_l_a_b.txt
		A01("A1", 96.55, -0.91, 0.57),
		A02("A2", 6.43, -0.06, -0.41),
		A03("A3", 49.7, -0.18, 0.03),
		A04("A4", 96.5, -0.89, 0.59),
		A05("A5", 6.5, -0.06, -0.44),
		A06("A6", 49.66, -0.2, 0.01),
		A07("A7", 96.52, -0.91, 0.58),
		A08("A8", 6.49, -0.02, -0.28),
		A09("A9", 49.72, -0.2, 0.04),
		A10("A10", 96.43, -0.91, 0.67),

		B01("B1", 49.72, -0.19, 0.02),
		B02("B2", 32.6, 51.58, -10.85),
		B03("B3", 60.75, 26.22, -18.69),
		B04("B4", 28.69, 48.28, -39),
		B05("B5", 49.38, -15.43, -48.48),
		B06("B6", 60.63, -30.77, -26.23),
		B07("B7", 19.29, -26.37, -6.15),
		B08("B8", 60.15, -41.77, -12.6),
		B09("B9", 21.42, 1.67, 8.79),
		B10("B10", 49.69, -0.2, 0.01),

		C01("C1", 6.5, -0.03, -0.67),
		C02("C2", 21.82, 17.33, -18.35),
		C03("C3", 41.53, 18.48, -37.26),
		C04("C4", 19.99, -0.16, -36.29),
		C05("C5", 60.16, -18.45, -31.42),
		C06("C6", 19.94, -17.92, -20.96),
		C07("C7", 60.68, -6.05, -32.81),
		C08("C8", 50.81, -49.8, -9.63),
		C09("C9", 60.65, -39.77, 20.76),
		C10("C10", 6.53, -0.03, -0.43),

		D01("D1", 96.56, -0.91, 0.59),
		D02("D2", 84.19, -1.95, -8.23),
		D03("D3", 84.75, 14.55, 0.23),
		D04("D4", 84.87, -19.07, -0.82),
		D05("D5", 85.15, 13.48, 6.82),
		D06("D6", 84.17, -10.45, 26.78),
		D07("D7", 61.74, 31.06, 36.42),
		D08("D8", 64.37, 20.82, 18.92),
		D09("D9", 50.4, -53.22, 14.62),
		D10("D10", 96.51, -0.89, 0.65),

		E01("E1", 49.74, -0.19, 0.03),
		E02("E2", 31.91, 18.62, 21.99),
		E03("E3", 60.74, 38.66, 70.97),
		E04("E4", 19.35, 22.23, -58.86),
		E05("E5", 96.52, -0.91, 0.62),
		E06("E6", 6.66, 0, -0.3),
		E07("E7", 76.51, 20.81, 22.72),
		E08("E8", 72.79, 29.15, 24.18),
		E09("E9", 22.33, -20.7, 5.75),
		E10("E10", 49.7, -0.19, 0.01),

		F01("F1", 6.53, -0.05, -0.61),
		F02("F2", 63.42, 20.19, 19.22),
		F03("F3", 34.94, 11.64, -50.7),
		F04("F4", 52.03, -44.15, 39.04),
		F05("F5", 79.43, 0.29, -0.17),
		F06("F6", 30.67, -0.14, -0.53),
		F07("F7", 63.6, 14.44, 26.07),
		F08("F8", 64.37, 14.5, 17.05),
		F09("F9", 60.01, -44.33, 8.49),
		F10("F10", 6.63, -0.01, -0.47),

		G01("G1", 96.56, -0.93, 0.59),
		G02("G2", 46.37, -5.09, -24.46),
		G03("G3", 47.08, 52.97, 20.49),
		G04("G4", 36.04, 64.92, 38.51),
		G05("G5", 65.05, 0, -0.32),
		G06("G6", 40.14, -0.19, -0.38),
		G07("G7", 43.77, 16.46, 27.12),
		G08("G8", 64.39, 17, 16.59),
		G09("G9", 60.79, -29.74, 41.5),
		G10("G10", 96.48, -0.89, 0.64),

		H01("H1", 49.75, -0.21, 0.01),
		H02("H2", 38.18, -16.99, 30.87),
		H03("H3", 21.31, 29.14, -27.51),
		H04("H4", 80.57, 3.85, 89.61),
		H05("H5", 49.71, -0.2, 0.03),
		H06("H6", 60.27, 0.08, -0.41),
		H07("H7", 67.34, 14.45, 16.9),
		H08("H8", 64.69, 16.95, 18.57),
		H09("H9", 51.12, -49.31, 44.41),
		H10("H10", 49.7, -0.2, 0.02),

		I01("I1", 6.67, -0.05, -0.64),
		I02("I2", 51.56, 9.16, -26.88),
		I03("I3", 70.83, -24.26, 64.77),
		I04("I4", 48.06, 55.33, -15.61),
		I05("I5", 35.26, -0.09, -0.24),
		I06("I6", 75.16, 0.25, -0.2),
		I07("I7", 44.54, 26.27, 38.93),
		I08("I8", 35.91, 16.59, 26.46),
		I09("I9", 61.49, -52.73, 47.3),
		I10("I10", 6.59, -0.05, -0.5),

		J01("J1", 96.58, -0.9, 0.61),
		J02("J2", 68.93, -34.58, -0.34),
		J03("J3", 69.65, 20.09, 78.57),
		J04("J4", 47.79, -33.18, -30.21),
		J05("J5", 15.94, -0.42, -1.2),
		J06("J6", 89.02, -0.36, -0.48),
		J07("J7", 63.43, 25.44, 26.25),
		J08("J8", 65.75, 22.06, 27.82),
		J09("J9", 61.47, 17.1, 50.72),
		J10("J10", 96.53, -0.89, 0.66),

		K01("K1", 49.79, -0.2, 0.03),
		K02("K2", 85.17, 10.89, 17.26),
		K03("K3", 89.74, -16.52, 6.19),
		K04("K4", 84.55, 5.07, -6.12),
		K05("K5", 84.02, -13.87, -8.72),
		K06("K6", 70.76, 0.07, -0.35),
		K07("K7", 45.59, -0.05, 0.23),
		K08("K8", 20.3, 0.07, -0.32),
		K09("K9", 61.79, -13.41, 55.42),
		K10("K10", 49.72, -0.19, 0.02),

		L01("L1", 6.77, -0.05, -0.44),
		L02("L2", 21.85, 34.37, 7.83),
		L03("L3", 42.66, 67.43, 48.42),
		L04("L4", 60.33, 36.56, 3.56),
		L05("L5", 61.22, 36.61, 17.32),
		L06("L6", 62.07, 52.8, 77.14),
		L07("L7", 72.42, -9.82, 89.66),
		L08("L8", 62.03, 3.53, 57.01),
		L09("L9", 71.95, -27.34, 73.69),
		L10("L10", 6.59, -0.04, -0.45),

		M01("M1", 49.77, -0.19, 0.04),
		M02("M2", 41.84, 62.05, 10.01),
		M03("M3", 19.78, 29.16, -7.85),
		M04("M4", 39.56, 65.98, 33.71),
		M05("M5", 52.39, 68.33, 47.84),
		M06("M6", 81.23, 24.12, 87.51),
		M07("M7", 81.8, 6.78, 95.75),
		M08("M8", 71.72, -16.23, 76.28),
		M09("M9", 20.31, 14.45, 16.74),
		M10("M10", 49.68, -0.19, 0.05),

		N01("N1", 96.48, -0.88, 0.68),
		N02("N2", 49.69, -0.18, 0.03),
		N03("N3", 6.39, -0.04, -0.33),
		N04("N4", 96.54, -0.9, 0.67),
		N05("N5", 49.72, -0.18, 0.05),
		N06("N6", 6.49, -0.03, -0.41),
		N07("N7", 96.51, -0.9, 0.69),
		N08("N8", 49.7, -0.19, 0.07),
		N09("N9", 6.47, 0, -0.38),
		N10("N10", 96.46, -0.89, 0.71),

		// Add patches
		patches(
			{
				&A01, &A02, &A03, &A04, &A05, &A06, &A07, &A08, &A09, &A10,
				&B01, &B02, &B03, &B04, &B05, &B06, &B07, &B08, &B09, &B10,
				&C01, &C02, &C03, &C04, &C05, &C06, &C07, &C08, &C09, &C10,
				&D01, &D02, &D03, &D04, &D05, &D06, &D07, &D08, &D09, &D10,
				&E01, &E02, &E03, &E04, &E05, &E06, &E07, &E08, &E09, &E10,
				&F01, &F02, &F03, &F04, &F05, &F06, &F07, &F08, &F09, &F10,
				&G01, &G02, &G03, &G04, &G05, &G06, &G07, &G08, &G09, &G10,
				&H01, &H02, &H03, &H04, &H05, &H06, &H07, &H08, &H09, &H10,
				&I01, &I02, &I03, &I04, &I05, &I06, &I07, &I08, &I09, &I10,
				&J01, &J02, &J03, &J04, &J05, &J06, &J07, &J08, &J09, &J10,
				&K01, &K02, &K03, &K04, &K05, &K06, &K07, &K08, &K09, &K10,
				&L01, &L02, &L03, &L04, &L05, &L06, &L07, &L08, &L09, &L10,
				&M01, &M02, &M03, &M04, &M05, &M06, &M07, &M08, &M09, &M10,
				&N01, &N02, &N03, &N04, &N05, &N06, &N07, &N08, &N09, &N10
			}
		),

		// Add color patches
		patchesColor(
			{
				&B02, &B03, &B04, &B05, &B06, &B07, &B08, &B09,
				&C02, &C03, &C04, &C05, &C06, &C07, &C08, &C09,
				&D02, &D03, &D04, &D05, &D06, &D07, &D08, &D09,
				&E02, &E03, &E04, &E07, &E08, &E09,
				&F02, &F03, &F04, &F07, &F08, &F09,
				&G02, &G03, &G04, &G07, &G08, &G09,
				&H02, &H03, &H04, &H07, &H08, &H09,
				&I02, &I03, &I04, &I07, &I08, &I09,
				&J02, &J03, &J04, &J07, &J08, &J09,
				&K02, &K03, &K04, &K05, &K08, &K09,
				&L02, &L03, &L04, &L05, &L06, &L07, &L08, &L09,
				&M02, &M03, &M04, &M05, &M06, &M07, &M08, &M09
			}
		),

		// Add neutral patches
		patchesNeutral(
			{
				&A01, &A02, &A03, &A04, &A05, &A06, &A07, &A08, &A09, &A10, // Left
				&N01, &N02, &N03, &N04, &N05, &N06, &N07, &N08, &N09, &N10, // Right
				&B01, &C01, &D01, &E01, &F01, &G01, &H01, &I01, &J01, &K01, &L01, &M01, // Top
				&B10, &C10, &D10, &E10, &F10, &G10, &H10, &I10, &J10, &K10, &L10, &M10, // Bottom
				&E05, &F05, &G05, &H05, &I05, &J05, // Gain top
				&E06, &F06, &G06, &H06, &I06, &J06, // Gain bottom
				&K06, &K07 // Extended
			}
		),

		// Add gain patches
		patchesGain(
			{
				&E05, &J06,
				&F05, &I06,
				&G05, &H06,
				&H05, &G06,
				&I05, &F06,
				&J05, &E06,
			}
		)
	{
		//
	}


	ColorChart::~ColorChart()
	{
		patches.clear();
		patchesColor.clear();
		patchesNeutral.clear();
		patchesGain.clear();
	}


	void ColorChart::read(const QString &path)
	{
		// Create data object
		std::vector<double> data(count * 3 * 3);

		// Read data
		readBytes(data.data(), (unsigned int) data.size(), path);

		// Iterate over data and fill patches
		for (unsigned int i = 0; i < count; i++) {
			const unsigned int index = count * 3 * 3;
			patches[i]->setRGB(data[index + 0], data[index + 1], data[index + 2], false);
			patches[i]->setHSB(data[index + 3], data[index + 4], data[index + 5], false);
			patches[i]->setXYZ(data[index + 6], data[index + 7], data[index + 8], false);
			patches[i]->setXYV(data[index + 9], data[index + 10], data[index + 11], false);
			patches[i]->setLAB(data[index + 12], data[index + 13], data[index + 14], false);
			patches[i]->update();
		}
	}


	void ColorChart::write(const QString &path)
	{
		// Create data object
		std::vector<double> data(count * 3 * 3);

		// Iterate over patches
		for (unsigned int i = 0; i < count; i++) {

			// Fetch color values
			const double *rgb = patches[i]->getRGB();
			const double *hsb = patches[i]->getHSB();
			const double *xyz = patches[i]->getXYZ();
			const double *xyv = patches[i]->getXYV();
			const double *lab = patches[i]->getLAB();

			// Add to vector
			data.push_back(rgb[0]);
			data.push_back(rgb[1]);
			data.push_back(rgb[2]);
			data.push_back(hsb[0]);
			data.push_back(hsb[1]);
			data.push_back(hsb[2]);
			data.push_back(xyz[0]);
			data.push_back(xyz[1]);
			data.push_back(xyz[2]);
			data.push_back(xyv[0]);
			data.push_back(xyv[1]);
			data.push_back(xyv[2]);
			data.push_back(lab[0]);
			data.push_back(lab[1]);
			data.push_back(lab[2]);
		}

		// Write data
		writeBytes(data.data(), (unsigned int) data.size(), path);
	}


	ColorChartPatch *ColorChart::at(const unsigned int col, const unsigned int row)
	{
		return at(rows * col + row);
	}


	ColorChartPatch *ColorChart::at(const unsigned int index)
	{
		return patches[index];
	}


	const std::vector<ColorChartPatch *> &ColorChart::getPatches() const
	{
		return patches;
	}


	const std::vector<ColorChartPatch *> &ColorChart::getPatchesColor() const
	{
		return patchesColor;
	}


	const std::vector<ColorChartPatch *> &ColorChart::getPatchesNeutral() const
	{
		return patchesNeutral;
	}


	const std::vector<ColorChartPatch *> &ColorChart::getPatchesGain() const
	{
		return patchesGain;
	}


	const unsigned int ColorChart::getCols() const
	{
		return cols;
	}


	const unsigned int ColorChart::getRows() const
	{
		return rows;
	}
}
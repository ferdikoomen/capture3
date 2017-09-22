#ifndef CAPTURE3_COLOR_CHART_H
#define CAPTURE3_COLOR_CHART_H


#include <string>
#include <vector>
#include <omp.h>


#include "ColorChartPatch.h"
#include "../../../constants/ColorChartConstants.h"
#include "../../../constants/ResourceConstants.h"
#include "../../../engine/objects/image/Image.h"
#include "../../../engine/objects/image/ImageChannel.h"
#include "../../../utils/FileUtils.h"
#include "../../../utils/ColorUtils.h"


namespace Capture3
{
	class ColorChart final
	{
		public:
			ColorChart();

			virtual ~ColorChart();

			void read(const QString &path);

			void write(const QString &path);

			ColorChartPatch *at(const unsigned int col, const unsigned int row);

			ColorChartPatch *at(const unsigned int index);

			const std::vector<ColorChartPatch *> &getPatches() const;

			const std::vector<ColorChartPatch *> &getPatchesColor() const;

			const std::vector<ColorChartPatch *> &getPatchesNeutral() const;

			const std::vector<ColorChartPatch *> &getPatchesGain() const;

			const unsigned int getCols() const;

			const unsigned int getRows() const;

			ColorChartPatch A01;
			ColorChartPatch A02;
			ColorChartPatch A03;
			ColorChartPatch A04;
			ColorChartPatch A05;
			ColorChartPatch A06;
			ColorChartPatch A07;
			ColorChartPatch A08;
			ColorChartPatch A09;
			ColorChartPatch A10;

			ColorChartPatch B01;
			ColorChartPatch B02;
			ColorChartPatch B03;
			ColorChartPatch B04;
			ColorChartPatch B05;
			ColorChartPatch B06;
			ColorChartPatch B07;
			ColorChartPatch B08;
			ColorChartPatch B09;
			ColorChartPatch B10;

			ColorChartPatch C01;
			ColorChartPatch C02;
			ColorChartPatch C03;
			ColorChartPatch C04;
			ColorChartPatch C05;
			ColorChartPatch C06;
			ColorChartPatch C07;
			ColorChartPatch C08;
			ColorChartPatch C09;
			ColorChartPatch C10;

			ColorChartPatch D01;
			ColorChartPatch D02;
			ColorChartPatch D03;
			ColorChartPatch D04;
			ColorChartPatch D05;
			ColorChartPatch D06;
			ColorChartPatch D07;
			ColorChartPatch D08;
			ColorChartPatch D09;
			ColorChartPatch D10;

			ColorChartPatch E01;
			ColorChartPatch E02;
			ColorChartPatch E03;
			ColorChartPatch E04;
			ColorChartPatch E05;
			ColorChartPatch E06;
			ColorChartPatch E07;
			ColorChartPatch E08;
			ColorChartPatch E09;
			ColorChartPatch E10;

			ColorChartPatch F01;
			ColorChartPatch F02;
			ColorChartPatch F03;
			ColorChartPatch F04;
			ColorChartPatch F05;
			ColorChartPatch F06;
			ColorChartPatch F07;
			ColorChartPatch F08;
			ColorChartPatch F09;
			ColorChartPatch F10;

			ColorChartPatch G01;
			ColorChartPatch G02;
			ColorChartPatch G03;
			ColorChartPatch G04;
			ColorChartPatch G05;
			ColorChartPatch G06;
			ColorChartPatch G07;
			ColorChartPatch G08;
			ColorChartPatch G09;
			ColorChartPatch G10;

			ColorChartPatch H01;
			ColorChartPatch H02;
			ColorChartPatch H03;
			ColorChartPatch H04;
			ColorChartPatch H05;
			ColorChartPatch H06;
			ColorChartPatch H07;
			ColorChartPatch H08;
			ColorChartPatch H09;
			ColorChartPatch H10;

			ColorChartPatch I01;
			ColorChartPatch I02;
			ColorChartPatch I03;
			ColorChartPatch I04;
			ColorChartPatch I05;
			ColorChartPatch I06;
			ColorChartPatch I07;
			ColorChartPatch I08;
			ColorChartPatch I09;
			ColorChartPatch I10;

			ColorChartPatch J01;
			ColorChartPatch J02;
			ColorChartPatch J03;
			ColorChartPatch J04;
			ColorChartPatch J05;
			ColorChartPatch J06;
			ColorChartPatch J07;
			ColorChartPatch J08;
			ColorChartPatch J09;
			ColorChartPatch J10;

			ColorChartPatch K01;
			ColorChartPatch K02;
			ColorChartPatch K03;
			ColorChartPatch K04;
			ColorChartPatch K05;
			ColorChartPatch K06;
			ColorChartPatch K07;
			ColorChartPatch K08;
			ColorChartPatch K09;
			ColorChartPatch K10;

			ColorChartPatch L01;
			ColorChartPatch L02;
			ColorChartPatch L03;
			ColorChartPatch L04;
			ColorChartPatch L05;
			ColorChartPatch L06;
			ColorChartPatch L07;
			ColorChartPatch L08;
			ColorChartPatch L09;
			ColorChartPatch L10;

			ColorChartPatch M01;
			ColorChartPatch M02;
			ColorChartPatch M03;
			ColorChartPatch M04;
			ColorChartPatch M05;
			ColorChartPatch M06;
			ColorChartPatch M07;
			ColorChartPatch M08;
			ColorChartPatch M09;
			ColorChartPatch M10;

			ColorChartPatch N01;
			ColorChartPatch N02;
			ColorChartPatch N03;
			ColorChartPatch N04;
			ColorChartPatch N05;
			ColorChartPatch N06;
			ColorChartPatch N07;
			ColorChartPatch N08;
			ColorChartPatch N09;
			ColorChartPatch N10;

		private:
			const unsigned int count;
			const unsigned int cols;
			const unsigned int rows;
			std::vector<ColorChartPatch *> patches;
			std::vector<ColorChartPatch *> patchesColor;
			std::vector<ColorChartPatch *> patchesNeutral;
			std::vector<ColorChartPatch *> patchesGain;
	};
}

#endif // CAPTURE3_COLOR_CHART_H

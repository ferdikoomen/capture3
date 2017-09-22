#ifndef CAPTURE3_COLOR_CHART_COMPONENT_H
#define CAPTURE3_COLOR_CHART_COMPONENT_H


#include <cmath>
#include <QtGui/QImage>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>


#include "../panelTab/PanelTabComponent.h"
#include "../panelGroup/PanelGroupComponent.h"
#include "../table/TableComponent.h"
#include "../../../engine/objects/colorChart/ColorChart.h"
#include "../../../engine/objects/colorChart/ColorChartPatch.h"
#include "../../../engine/objects/colorProfile/ColorProfile.h"
#include "../../../engine/objects/colorProfile/ColorProfileChart.h"
#include "../../../engine/objects/colorProfile/ColorProfileChartPatch.h"
#include "../../../engine/objects/colorProfile/ColorProfileChartPatchData.h"
#include "../../../constants/ColorChartConstants.h"
#include "../../../utils/ColorChartVisualUtils.h"
#include "../../../utils/PixmapUtils.h"


namespace Capture3
{
	class ColorChartComponent final : public PanelTabComponent
	{
		Q_OBJECT

		public:
			ColorChartComponent();

			virtual ~ColorChartComponent();

			void show(const ColorProfile *profile);

			void reset();

		private:
			PanelGroupComponent group;
			QLabel container;
			TableComponent table;
	};
}


#endif // CAPTURE3_COLOR_CHART_PATCHES_COMPONENT_H

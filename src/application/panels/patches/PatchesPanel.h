#ifndef CAPTURE3_PATCHES_PANEL_H
#define CAPTURE3_PATCHES_PANEL_H


#include "../../components/panel/PanelComponent.h"
#include "../../components/panelTabs/PanelTabsComponent.h"
#include "../../components/colorChart/ColorChartComponent.h"


namespace Capture3
{
	class PatchesPanel final : public PanelComponent
	{
		Q_OBJECT

		public:
			PatchesPanel();

			virtual ~PatchesPanel();

			ColorChartComponent &getColorChart();

		private:
			PanelTabsComponent tabs;
			ColorChartComponent colorChart;

	};
}


#endif // CAPTURE3_PATCHES_PANEL_H

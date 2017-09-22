#include "PatchesPanel.h"


namespace Capture3
{

	PatchesPanel::PatchesPanel() :
		PanelComponent(),
		tabs(),
		colorChart()
	{
		// Add items
		tabs.addTab(&colorChart);
		addTabs(&tabs);
	}


	PatchesPanel::~PatchesPanel()
	{
		colorChart.deleteLater();
		tabs.deleteLater();
	}


	ColorChartComponent &PatchesPanel::getColorChart()
	{
		return colorChart;
	}

}
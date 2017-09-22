#include "WhiteBalancePatchesComponentChart.h"


namespace Capture3
{

	WhiteBalancePatchesComponentChart::WhiteBalancePatchesComponentChart() :
		PanelGroupComponent("White Balance - Patches"),
		graphic(1, 1),
		table()
	{
		// Set table options
		table.setColumnCount(20);
		table.setRowCount(20);

		addWidget(&graphic);
		addWidget(&table);
	}


	WhiteBalancePatchesComponentChart::~WhiteBalancePatchesComponentChart()
	{
		graphic.deleteLater();
		table.deleteLater();
	}

}
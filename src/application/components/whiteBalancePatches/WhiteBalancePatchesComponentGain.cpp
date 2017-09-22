#include "WhiteBalancePatchesComponentGain.h"


namespace Capture3
{

	WhiteBalancePatchesComponentGain::WhiteBalancePatchesComponentGain() :
		PanelGroupComponent("White Balance - Gain"),
		graphic(1, 1),
		table()
	{
		// Set table options
		table.setColumnCount(20);
		table.setRowCount(20);

		addWidget(&graphic);
		addWidget(&table);
	}


	WhiteBalancePatchesComponentGain::~WhiteBalancePatchesComponentGain()
	{
		graphic.deleteLater();
		table.deleteLater();
	}

}
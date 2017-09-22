#include "WhiteBalancePatchesComponent.h"


namespace Capture3
{

	WhiteBalancePatchesComponent::WhiteBalancePatchesComponent() :
		PanelTabComponent("White Balance Patches"),
		itemGain(),
		itemChart()
	{
		// Add items
		addWidget(&itemGain);
		addWidget(&itemChart);
	}


	WhiteBalancePatchesComponent::~WhiteBalancePatchesComponent()
	{
		itemGain.deleteLater();
		itemChart.deleteLater();
	}

}
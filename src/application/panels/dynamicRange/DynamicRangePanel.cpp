#include "DynamicRangePanel.h"


namespace Capture3
{

	DynamicRangePanel::DynamicRangePanel() :
		PanelComponent(),
		tabs(),
		view()
	{
		// Add items
		tabs.addTab(&view);
		addTabs(&tabs);
	}


	DynamicRangePanel::~DynamicRangePanel()
	{
		view.deleteLater();
		tabs.deleteLater();
	}


	DynamicRangeComponent &DynamicRangePanel::getView()
	{
		return view;
	}

}
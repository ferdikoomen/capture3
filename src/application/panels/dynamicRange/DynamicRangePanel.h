#ifndef CAPTURE3_DYNAMIC_RANGE_PANEL_H
#define CAPTURE3_DYNAMIC_RANGE_PANEL_H


#include "../../components/panel/PanelComponent.h"
#include "../../components/panelTabs/PanelTabsComponent.h"
#include "../../components/dynamicRange/DynamicRangeComponent.h"

namespace Capture3
{
	class DynamicRangePanel final : public PanelComponent
	{
		Q_OBJECT

		public:
			DynamicRangePanel();

			virtual ~DynamicRangePanel();

			DynamicRangeComponent &getView();

		private:
			PanelTabsComponent tabs;
			DynamicRangeComponent view;
	};
}


#endif // CAPTURE3_DYNAMIC_RANGE_PANEL_H

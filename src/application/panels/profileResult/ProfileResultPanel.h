#ifndef CAPTURE3_PROFILE_RESULT_PANEL_H
#define CAPTURE3_PROFILE_RESULT_PANEL_H


#include "../../components/panel/PanelComponent.h"
#include "../../components/panelTabs/PanelTabsComponent.h"
#include "../../components/colorProfileGraph/ColorProfileGraphComponent.h"
#include "../../components/colorProfileMatrix/ColorProfileMatrixComponent.h"


namespace Capture3
{
	class ProfileResultPanel final : public PanelComponent
	{
		Q_OBJECT

		public:
			ProfileResultPanel();

			virtual ~ProfileResultPanel();

			ColorProfileGraphComponent &getColorProfileGraph();

			ColorProfileMatrixComponent &getColorProfileMatrix();

		private:
			PanelTabsComponent tabs;
			ColorProfileGraphComponent colorProfileGraph;
			ColorProfileMatrixComponent colorProfileMatrix;

	};
}


#endif // CAPTURE3_PROFILE_RESULT_PANEL_H

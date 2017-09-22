#ifndef CAPTURE3_PROFILE_CURVES_PANEL_H
#define CAPTURE3_PROFILE_CURVES_PANEL_H


#include "../../components/panel/PanelComponent.h"
#include "../../components/panelTabs/PanelTabsComponent.h"
#include "../../components/whiteBalanceCurves/WhiteBalanceCurvesComponent.h"
#include "../../components/colorProfileCurves/ColorProfileCurvesComponent.h"


namespace Capture3
{
	class ProfileCurvesPanel final : public PanelComponent
	{
		Q_OBJECT

		public:
			ProfileCurvesPanel();

			virtual ~ProfileCurvesPanel();

			ColorProfileCurvesComponent &getColorProfileCurves();

			WhiteBalanceCurvesComponent &getWhiteBalanceCurves();

		private:
			PanelTabsComponent tabs;
			ColorProfileCurvesComponent colorProfileCurves;
			WhiteBalanceCurvesComponent whiteBalanceCurves;
	};
}


#endif // CAPTURE3_PROFILE_CURVES_PANEL_H

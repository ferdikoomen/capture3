#ifndef CAPTURE3_WHITE_BALANCE_CURVES_COMPONENT_H
#define CAPTURE3_WHITE_BALANCE_CURVES_COMPONENT_H


#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>


#include "../panelTab/PanelTabComponent.h"
#include "../panelGroup/PanelGroupComponent.h"
#include "WhiteBalanceCurvesComponentItem.h"
#include "../../../engine/objects/whiteBalance/WhiteBalance.h"


namespace Capture3
{
	class WhiteBalanceCurvesComponent final : public PanelTabComponent
	{
		Q_OBJECT

		public:
			WhiteBalanceCurvesComponent();

			virtual ~WhiteBalanceCurvesComponent();

			void show(const WhiteBalance *whiteBalance);

			void clear();

		private:
			PanelGroupComponent groupRGB;
			PanelGroupComponent groupHSB;
			PanelGroupComponent groupXYZ;
			PanelGroupComponent groupXYV;
			PanelGroupComponent groupLAB;
			WhiteBalanceCurvesComponentItem itemRGB_R;
			WhiteBalanceCurvesComponentItem itemRGB_G;
			WhiteBalanceCurvesComponentItem itemRGB_B;
			WhiteBalanceCurvesComponentItem itemHSB_H;
			WhiteBalanceCurvesComponentItem itemHSB_S;
			WhiteBalanceCurvesComponentItem itemHSB_B;
			WhiteBalanceCurvesComponentItem itemXYZ_X;
			WhiteBalanceCurvesComponentItem itemXYZ_Y;
			WhiteBalanceCurvesComponentItem itemXYZ_Z;
			WhiteBalanceCurvesComponentItem itemXYV_X;
			WhiteBalanceCurvesComponentItem itemXYV_Y;
			WhiteBalanceCurvesComponentItem itemXYV_V;
			WhiteBalanceCurvesComponentItem itemLAB_L;
			WhiteBalanceCurvesComponentItem itemLAB_A;
			WhiteBalanceCurvesComponentItem itemLAB_B;
	};
}


#endif // CAPTURE3_WHITE_BALANCE_CURVES_COMPONENT_H

#ifndef CAPTURE3_COLOR_PROFILE_CURVES_COMPONENT_H
#define CAPTURE3_COLOR_PROFILE_CURVES_COMPONENT_H


#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>


#include "ColorProfileCurvesComponentItem.h"
#include "../panelTab/PanelTabComponent.h"
#include "../panelGroup/PanelGroupComponent.h"
#include "../../../engine/objects/colorProfile/ColorProfile.h"


namespace Capture3
{
	class ColorProfileCurvesComponent final : public PanelTabComponent
	{
		Q_OBJECT

		public:
			ColorProfileCurvesComponent();

			virtual ~ColorProfileCurvesComponent();

			void show(const ColorProfile *colorProfile);

			void clear();

		private:
			PanelGroupComponent groupRGB;
			PanelGroupComponent groupHSB;
			PanelGroupComponent groupXYZ;
			PanelGroupComponent groupXYV;
			PanelGroupComponent groupLAB;
			ColorProfileCurvesComponentItem itemRGB_R;
			ColorProfileCurvesComponentItem itemRGB_G;
			ColorProfileCurvesComponentItem itemRGB_B;
			ColorProfileCurvesComponentItem itemHSB_H;
			ColorProfileCurvesComponentItem itemHSB_S;
			ColorProfileCurvesComponentItem itemHSB_B;
			ColorProfileCurvesComponentItem itemXYZ_X;
			ColorProfileCurvesComponentItem itemXYZ_Y;
			ColorProfileCurvesComponentItem itemXYZ_Z;
			ColorProfileCurvesComponentItem itemXYV_X;
			ColorProfileCurvesComponentItem itemXYV_Y;
			ColorProfileCurvesComponentItem itemXYV_V;
			ColorProfileCurvesComponentItem itemLAB_L;
			ColorProfileCurvesComponentItem itemLAB_A;
			ColorProfileCurvesComponentItem itemLAB_B;
	};
}


#endif // CAPTURE3_COLOR_PROFILE_CURVES_COMPONENT_H

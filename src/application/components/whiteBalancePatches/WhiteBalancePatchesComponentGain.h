#ifndef CAPTURE3_WHITE_BALANCE_PATCHES_COMPONENT_GAIN_H
#define CAPTURE3_WHITE_BALANCE_PATCHES_COMPONENT_GAIN_H


#include <QtWidgets/QWidget>


#include "../panelGroup/PanelGroupComponent.h"
#include "../graphic/GraphicComponent.h"
#include "../table/TableComponent.h"


namespace Capture3
{
	class WhiteBalancePatchesComponentGain final : public PanelGroupComponent
	{
		Q_OBJECT

		public:
			WhiteBalancePatchesComponentGain();

			virtual ~WhiteBalancePatchesComponentGain();

		private:
			GraphicComponent graphic;
			TableComponent table;
	};
}


#endif // CAPTURE3_WHITE_BALANCE_PATCHES_COMPONENT_GAIN_H

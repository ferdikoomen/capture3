#ifndef CAPTURE3_WHITE_BALANCE_PATCHES_COMPONENT_CHART_H
#define CAPTURE3_WHITE_BALANCE_PATCHES_COMPONENT_CHART_H


#include <QtWidgets/QWidget>


#include "../panelGroup/PanelGroupComponent.h"
#include "../graphic/GraphicComponent.h"
#include "../table/TableComponent.h"


namespace Capture3
{
	class WhiteBalancePatchesComponentChart final : public PanelGroupComponent
	{
		Q_OBJECT

		public:
			WhiteBalancePatchesComponentChart();

			virtual ~WhiteBalancePatchesComponentChart();

		private:
			GraphicComponent graphic;
			TableComponent table;
	};
}


#endif // CAPTURE3_WHITE_BALANCE_PATCHES_COMPONENT_CHART_H

#ifndef CAPTURE3_WHITE_BALANCE_PATCHES_COMPONENT_H
#define CAPTURE3_WHITE_BALANCE_PATCHES_COMPONENT_H


#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>


#include "../panelTab/PanelTabComponent.h"
#include "WhiteBalancePatchesComponentGain.h"
#include "WhiteBalancePatchesComponentChart.h"


namespace Capture3
{
	class WhiteBalancePatchesComponent final : public PanelTabComponent
	{
		Q_OBJECT

		public:
			WhiteBalancePatchesComponent();

			virtual ~WhiteBalancePatchesComponent();

		private:
			WhiteBalancePatchesComponentGain itemGain;
			WhiteBalancePatchesComponentChart itemChart;
	};
}


#endif // CAPTURE3_WHITE_BALANCE_PATCHES_COMPONENT_H

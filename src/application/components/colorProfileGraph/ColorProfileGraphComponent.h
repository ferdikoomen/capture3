#ifndef CAPTURE3_COLOR_PROFILE_GRAPH_COMPONENT_H
#define CAPTURE3_COLOR_PROFILE_GRAPH_COMPONENT_H


#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>


#include "ColorProfileGraphComponentItem.h"
#include "../panelTab/PanelTabComponent.h"
#include "../panelGroup/PanelGroupComponent.h"
#include "../../../engine/objects/colorChart/ColorChart.h"
#include "../../../engine/objects/colorMatrix/ColorMatrix.h"
#include "../../../utils/ColorChartGraphUtils.h"


namespace Capture3
{
	class ColorProfileGraphComponent final : public PanelTabComponent
	{
		Q_OBJECT

		public:
			ColorProfileGraphComponent();

			virtual ~ColorProfileGraphComponent();

			void show(
				const ColorChart *colorChartReference,
				const ColorChart *colorChartDetected
			);

			void reset();

		private:
			PanelGroupComponent groupRGB;
			PanelGroupComponent groupHSB;
			PanelGroupComponent groupXYZ;
			PanelGroupComponent groupXYV;
			PanelGroupComponent groupLAB;
			ColorProfileGraphComponentItem itemRGB;
			ColorProfileGraphComponentItem itemHSB;
			ColorProfileGraphComponentItem itemXYZ;
			ColorProfileGraphComponentItem itemXYV;
			ColorProfileGraphComponentItem itemLAB;
			std::vector<float> positionsRGB;
			std::vector<float> positionsHSB;
			std::vector<float> positionsXYZ;
			std::vector<float> positionsXYV;
			std::vector<float> positionsLAB;
			std::vector<float> colors;
			unsigned int countPoints;
			unsigned int countLines;
	};
}


#endif // CAPTURE3_COLOR_PROFILE_GRAPH_COMPONENT_H

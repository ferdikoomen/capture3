#ifndef CAPTURE3_IMAGE_GRAPH_COMPONENT_H
#define CAPTURE3_IMAGE_GRAPH_COMPONENT_H


#include <vector>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>


#include "ImageGraphComponentItem.h"
#include "../panelTab/PanelTabComponent.h"
#include "../panelGroup/PanelGroupComponent.h"
#include "../../../engine/objects/image/Image.h"
#include "../../../utils/ImageGraphUtils.h"


namespace Capture3
{
	class ImageGraphComponent final : public PanelTabComponent
	{
		Q_OBJECT

		public:
			ImageGraphComponent();

			virtual ~ImageGraphComponent();

			void show(const Image *image);

			void reset();

		private:
			PanelGroupComponent groupRGB;
			PanelGroupComponent groupHSB;
			PanelGroupComponent groupXYZ;
			PanelGroupComponent groupXYV;
			PanelGroupComponent groupLAB;
			ImageGraphComponentItem itemRGB;
			ImageGraphComponentItem itemHSB;
			ImageGraphComponentItem itemXYZ;
			ImageGraphComponentItem itemXYV;
			ImageGraphComponentItem itemLAB;
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


#endif // CAPTURE3_IMAGE_GRAPH_COMPONENT_H

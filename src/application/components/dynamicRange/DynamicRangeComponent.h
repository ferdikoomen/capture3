#ifndef CAPTURE3_DYNAMIC_RANGE_COMPONENT_H
#define CAPTURE3_DYNAMIC_RANGE_COMPONENT_H


#include <QtWidgets/QWidget>


#include "../panelTab/PanelTabComponent.h"
#include "../panelGroup/PanelGroupComponent.h"
#include "../render/RenderComponent.h"
#include "../../../engine/objects/image/Image.h"
#include "../../../constants/CameraConstants.h"


namespace Capture3
{
	class DynamicRangeComponent final : public PanelTabComponent
	{
		Q_OBJECT

		public:
			DynamicRangeComponent();

			virtual ~DynamicRangeComponent();

			void show(const Image *image);

			void reset();

		private:
			PanelGroupComponent groupPreview;
			PanelGroupComponent groupRow1;
			PanelGroupComponent groupRow2;
			PanelGroupComponent groupRow3;
			RenderComponent preview;
	};
}


#endif // CAPTURE3_DYNAMIC_RANGE_COMPONENT_H

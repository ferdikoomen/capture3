#ifndef CAPTURE3_IMAGE_HISTOGRAM_COMPONENT_H
#define CAPTURE3_IMAGE_HISTOGRAM_COMPONENT_H


#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>


#include "ImageHistogramComponentItem.h"
#include "../panelGroup/PanelGroupComponent.h"
#include "../panelTab/PanelTabComponent.h"
#include "../../../engine/objects/image/Image.h"
#include "../../../utils/ImageHistogramUtils.h"


namespace Capture3
{
	class ImageHistogramComponent final : public PanelTabComponent
	{
		Q_OBJECT

		public:
			ImageHistogramComponent();

			virtual ~ImageHistogramComponent();

			void show(const Image *image);

			void reset();

		private:
			PanelGroupComponent groupRGB;
			PanelGroupComponent groupHSB;
			PanelGroupComponent groupXYZ;
			PanelGroupComponent groupXYV;
			PanelGroupComponent groupLAB;
			ImageHistogramComponentItem itemRGB_R;
			ImageHistogramComponentItem itemRGB_G;
			ImageHistogramComponentItem itemRGB_B;
			ImageHistogramComponentItem itemHSB_H;
			ImageHistogramComponentItem itemHSB_S;
			ImageHistogramComponentItem itemHSB_B;
			ImageHistogramComponentItem itemXYZ_X;
			ImageHistogramComponentItem itemXYZ_Y;
			ImageHistogramComponentItem itemXYZ_Z;
			ImageHistogramComponentItem itemXYV_X;
			ImageHistogramComponentItem itemXYV_Y;
			ImageHistogramComponentItem itemXYV_V;
			ImageHistogramComponentItem itemLAB_L;
			ImageHistogramComponentItem itemLAB_A;
			ImageHistogramComponentItem itemLAB_B;
	};
}


#endif // CAPTURE3_IMAGE_HISTOGRAM_COMPONENT_H

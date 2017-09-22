#ifndef CAPTURE3_IMAGE_WAVEFORM_COMPONENT_H
#define CAPTURE3_IMAGE_WAVEFORM_COMPONENT_H


#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>


#include "ImageWaveformComponentItem.h"
#include "../panelGroup/PanelGroupComponent.h"
#include "../panelTab/PanelTabComponent.h"
#include "../../../engine/objects/image/Image.h"
#include "../../../utils/ImageWaveformUtils.h"


namespace Capture3
{
	class ImageWaveformComponent final : public PanelTabComponent
	{
		Q_OBJECT

		public:
			ImageWaveformComponent();

			virtual ~ImageWaveformComponent();

			void show(const Image *image);

			void reset();

		private:
			PanelGroupComponent groupRGB;
			PanelGroupComponent groupHSB;
			PanelGroupComponent groupXYZ;
			PanelGroupComponent groupXYV;
			PanelGroupComponent groupLAB;
			ImageWaveformComponentItem itemRGB_R;
			ImageWaveformComponentItem itemRGB_G;
			ImageWaveformComponentItem itemRGB_B;
			ImageWaveformComponentItem itemHSB_H;
			ImageWaveformComponentItem itemHSB_S;
			ImageWaveformComponentItem itemHSB_B;
			ImageWaveformComponentItem itemXYZ_X;
			ImageWaveformComponentItem itemXYZ_Y;
			ImageWaveformComponentItem itemXYZ_Z;
			ImageWaveformComponentItem itemXYV_X;
			ImageWaveformComponentItem itemXYV_Y;
			ImageWaveformComponentItem itemXYV_V;
			ImageWaveformComponentItem itemLAB_L;
			ImageWaveformComponentItem itemLAB_A;
			ImageWaveformComponentItem itemLAB_B;
	};
}


#endif // CAPTURE3_IMAGE_WAVEFORM_COMPONENT_H

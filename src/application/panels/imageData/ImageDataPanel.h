#ifndef CAPTURE3_IMAGE_DATA_PANEL_H
#define CAPTURE3_IMAGE_DATA_PANEL_H


#include "../../components/panel/PanelComponent.h"
#include "../../components/panelTabs/PanelTabsComponent.h"
#include "../../components/imageHistogram/ImageHistogramComponent.h"
#include "../../components/imageGraph/ImageGraphComponent.h"
#include "../../components/imageWaveform/ImageWaveformComponent.h"


namespace Capture3
{
	class ImageDataPanel final : public PanelComponent
	{
		Q_OBJECT

		public:
			ImageDataPanel();

			virtual ~ImageDataPanel();

			ImageHistogramComponent &getImageHistogram();

			ImageGraphComponent &getImageGraph();

			ImageWaveformComponent &getImageWaveform();

		private:
			PanelTabsComponent tabs;
			ImageHistogramComponent imageHistogram;
			ImageGraphComponent imageGraph;
			ImageWaveformComponent imageWaveform;

	};
}


#endif // CAPTURE3_IMAGE_DATA_PANEL_H

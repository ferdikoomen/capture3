#ifndef CAPTURE3_IMAGE_PANEL_H
#define CAPTURE3_IMAGE_PANEL_H


#include "../../components/panel/PanelComponent.h"
#include "../../components/panelTabs/PanelTabsComponent.h"
#include "../../components/imageViewer/ImageViewerComponent.h"


namespace Capture3
{
	class ImagePanel final : public PanelComponent
	{
		Q_OBJECT

		public:
			ImagePanel();

			virtual ~ImagePanel();

			ImageViewerComponent &getImageViewer();

		private:
			PanelTabsComponent tabs;
			ImageViewerComponent imageViewer;
	};
}


#endif // CAPTURE3_IMAGE_PANEL_H

#ifndef CAPTURE3_THUMBNAILS_PANEL_H
#define CAPTURE3_THUMBNAILS_PANEL_H


#include "../../components/panel/PanelComponent.h"
#include "../../components/panelTabs/PanelTabsComponent.h"
#include "../../components/thumbnails/ThumbnailsComponent.h"

namespace Capture3
{
	class ThumbnailsPanel final : public PanelComponent
	{
		Q_OBJECT

		public:
			ThumbnailsPanel();

			virtual ~ThumbnailsPanel();

			ThumbnailsComponent &getThumbnails();

		private:
			PanelTabsComponent tabs;
			ThumbnailsComponent thumbnails;

	};
}


#endif // CAPTURE3_THUMBNAILS_PANEL_H

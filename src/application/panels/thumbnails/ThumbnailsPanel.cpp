#include "ThumbnailsPanel.h"


namespace Capture3
{

	ThumbnailsPanel::ThumbnailsPanel() :
		PanelComponent(),
		tabs(),
		thumbnails()
	{
		// Add items
		tabs.addTab(&thumbnails);
		addTabs(&tabs);
	}


	ThumbnailsPanel::~ThumbnailsPanel()
	{
		thumbnails.deleteLater();
		tabs.deleteLater();
	}


	ThumbnailsComponent &ThumbnailsPanel::getThumbnails()
	{
		return thumbnails;
	}
}
#include "ImagePanel.h"


namespace Capture3
{

	ImagePanel::ImagePanel() :
		PanelComponent(),
		tabs(),
		imageViewer()
	{
		// Add items
		tabs.addTab(&imageViewer);
		addTabs(&tabs);
	}


	ImagePanel::~ImagePanel()
	{
		imageViewer.deleteLater();
		tabs.deleteLater();
	}


	ImageViewerComponent &ImagePanel::getImageViewer()
	{
		return imageViewer;
	}
}
#include "ImageDataPanel.h"


namespace Capture3
{

	ImageDataPanel::ImageDataPanel() :
		PanelComponent(),
		tabs(),
		imageHistogram(),
		imageGraph(),
		imageWaveform()
	{
		// Add items
		tabs.addTab(&imageHistogram);
		tabs.addTab(&imageGraph);
		tabs.addTab(&imageWaveform);
		addTabs(&tabs);
	}


	ImageDataPanel::~ImageDataPanel()
	{
		imageHistogram.deleteLater();
		imageGraph.deleteLater();
		imageWaveform.deleteLater();
		tabs.deleteLater();
	}


	ImageHistogramComponent &ImageDataPanel::getImageHistogram()
	{
		return imageHistogram;
	}


	ImageGraphComponent &ImageDataPanel::getImageGraph()
	{
		return imageGraph;
	}


	ImageWaveformComponent &ImageDataPanel::getImageWaveform()
	{
		return imageWaveform;
	}
}
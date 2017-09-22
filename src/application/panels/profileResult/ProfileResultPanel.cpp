#include "ProfileResultPanel.h"


namespace Capture3
{

	ProfileResultPanel::ProfileResultPanel() :
		PanelComponent(),
		tabs(),
		colorProfileGraph(),
		colorProfileMatrix()
	{
		// Add items
		tabs.addTab(&colorProfileMatrix);
		tabs.addTab(&colorProfileGraph);
		addTabs(&tabs);
	}


	ProfileResultPanel::~ProfileResultPanel()
	{
		colorProfileGraph.deleteLater();
		colorProfileMatrix.deleteLater();
		tabs.deleteLater();
	}


	ColorProfileGraphComponent &ProfileResultPanel::getColorProfileGraph()
	{
		return colorProfileGraph;
	}


	ColorProfileMatrixComponent &ProfileResultPanel::getColorProfileMatrix()
	{
		return colorProfileMatrix;
	}
}
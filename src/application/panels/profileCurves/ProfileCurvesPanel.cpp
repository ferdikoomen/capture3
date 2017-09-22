#include "ProfileCurvesPanel.h"


namespace Capture3
{

	ProfileCurvesPanel::ProfileCurvesPanel() :
		PanelComponent(),
		tabs(),
		colorProfileCurves(),
		whiteBalanceCurves()
	{
		// Add items
		tabs.addTab(&colorProfileCurves);
		tabs.addTab(&whiteBalanceCurves);
		addTabs(&tabs);
	}


	ProfileCurvesPanel::~ProfileCurvesPanel()
	{
		colorProfileCurves.deleteLater();
		whiteBalanceCurves.deleteLater();
		tabs.deleteLater();
	}


	ColorProfileCurvesComponent &ProfileCurvesPanel::getColorProfileCurves()
	{
		return colorProfileCurves;
	}


	WhiteBalanceCurvesComponent &ProfileCurvesPanel::getWhiteBalanceCurves()
	{
		return whiteBalanceCurves;
	}
}
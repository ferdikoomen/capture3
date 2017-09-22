#include "ColorProfileCurvesComponentItem.h"


namespace Capture3
{

	ColorProfileCurvesComponentItem::ColorProfileCurvesComponentItem() :
		CurveComponent(256, 246)
	{
		//
	}


	ColorProfileCurvesComponentItem::~ColorProfileCurvesComponentItem()
	{
		//
	}


	void ColorProfileCurvesComponentItem::draw(QPainter &painter)
	{
		CurveComponent::draw(painter);
	}

}
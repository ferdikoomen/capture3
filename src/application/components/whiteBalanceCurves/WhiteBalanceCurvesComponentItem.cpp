#include "WhiteBalanceCurvesComponentItem.h"


namespace Capture3
{

	WhiteBalanceCurvesComponentItem::WhiteBalanceCurvesComponentItem() :
		CurveComponent(256, 246)
	{
		//
	}


	WhiteBalanceCurvesComponentItem::~WhiteBalanceCurvesComponentItem()
	{
		//
	}


	void WhiteBalanceCurvesComponentItem::draw(QPainter &painter)
	{
		CurveComponent::draw(painter);
	}
}
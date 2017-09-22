#include "ColorProfileGraphComponentItem.h"


namespace Capture3
{

	ColorProfileGraphComponentItem::ColorProfileGraphComponentItem() :
		RenderComponent(256, 246)
	{
		setPointSize(2.0f);
		setLineSize(2.0f);
	}


	ColorProfileGraphComponentItem::~ColorProfileGraphComponentItem()
	{
		//
	}


	void ColorProfileGraphComponentItem::draw(
		const std::vector<float> &positions,
		const std::vector<float> &colors,
		const unsigned int countPoints,
		const unsigned int countLines
	)
	{
		setData(
			positions,
			colors,
			countPoints,
			countPoints + countLines
		);
	}

}
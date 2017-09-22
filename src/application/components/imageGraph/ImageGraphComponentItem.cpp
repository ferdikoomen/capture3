#include "ImageGraphComponentItem.h"


namespace Capture3
{

	ImageGraphComponentItem::ImageGraphComponentItem() :
		RenderComponent(256, 246)
	{
		setPointSize(2.0f);
		setLineSize(2.0f);
	}


	ImageGraphComponentItem::~ImageGraphComponentItem()
	{
		//
	}


	void ImageGraphComponentItem::draw(
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
			countLines,
			0, 0,
			countPoints
		);
	}
}
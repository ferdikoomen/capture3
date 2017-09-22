#include "ImageHistogramComponentItem.h"


namespace Capture3
{

	ImageHistogramComponentItem::ImageHistogramComponentItem() :
		GraphicComponent(256, 80),
		colorBackground(COLOR_BACKGROUND),
		colorForeground(COLOR_FOREGROUND),
		gradient(),
		image(
			256 * window()->devicePixelRatio(),
			72 * window()->devicePixelRatio(),
			QImage::Format_ARGB32_Premultiplied
		)
	{
		// Set gradient
		gradient.setColorAt(0, Qt::black);
		gradient.setColorAt(1, Qt::white);
		image.setDevicePixelRatio(window()->devicePixelRatio());
		reset();
	}


	ImageHistogramComponentItem::~ImageHistogramComponentItem()
	{
		//
	}


	void ImageHistogramComponentItem::reset()
	{
		image.fill(COLOR_FOREGROUND);
	}


	void ImageHistogramComponentItem::draw(QPainter &painter)
	{
		GraphicComponent::draw(painter);

		// Get size
		const int w = width();
		const int h = height();
		const int w2 = w - 0;
		const int h2 = h - 8;

		// Set gradient
		gradient.setStart(0, 0);
		gradient.setFinalStop(w, 0);

		// Draw background
		painter.fillRect(0, 0, w, h, colorBackground);
		painter.fillRect(0, 0, w2, h2, colorForeground);
		painter.fillRect(0, h - 5, w, 5, gradient);

		// Draw image
		painter.drawImage(0, 0, image);
	}


	QImage &ImageHistogramComponentItem::getImage()
	{
		return image;
	}
}
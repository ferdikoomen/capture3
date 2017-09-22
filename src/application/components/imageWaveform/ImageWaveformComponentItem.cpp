#include "ImageWaveformComponentItem.h"


namespace Capture3
{

	ImageWaveformComponentItem::ImageWaveformComponentItem() :
		GraphicComponent(256, 80),
		colorBackground(COLOR_BACKGROUND),
		colorForeground(COLOR_FOREGROUND),
		gradient(),
		image(
			248 * window()->devicePixelRatio(),
			80 * window()->devicePixelRatio(),
			QImage::Format_ARGB32_Premultiplied
		)
	{
		// Set gradient
		gradient.setColorAt(0, Qt::white);
		gradient.setColorAt(1, Qt::black);
		image.setDevicePixelRatio(window()->devicePixelRatio());
		reset();
	}


	ImageWaveformComponentItem::~ImageWaveformComponentItem()
	{
		//
	}


	void ImageWaveformComponentItem::reset()
	{
		image.fill(COLOR_FOREGROUND);
	}


	void ImageWaveformComponentItem::draw(QPainter &painter)
	{
		GraphicComponent::draw(painter);

		// Get size
		const int w = width();
		const int h = height();
		const int w2 = w - 8;
		const int h2 = h - 0;

		// Set gradient
		gradient.setStart(0, 0);
		gradient.setFinalStop(0, h);

		// Draw background
		painter.fillRect(0, 0, w, h, colorBackground);
		painter.fillRect(8, 0, w2, h2, colorForeground);
		painter.fillRect(0, 0, 5, h, gradient);

		// Draw image
		painter.drawImage(8, 0, image);
	}


	QImage &ImageWaveformComponentItem::getImage()
	{
		return image;
	}
}
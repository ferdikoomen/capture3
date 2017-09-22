#ifndef CAPTURE3_PIXMAP_UTILS_H
#define CAPTURE3_PIXMAP_UTILS_H


#include <QImage>
#include <QWidget>
#include <QPixmap>


namespace Capture3
{

	static QPixmap getPixmap(const QImage &image, const int pixelRatio)
	{
		QPixmap pixmap = QPixmap::fromImage(image);
		pixmap.setDevicePixelRatio(pixelRatio);
		return pixmap;
	}

}


#endif // CAPTURE3_PIXMAP_UTILS_H

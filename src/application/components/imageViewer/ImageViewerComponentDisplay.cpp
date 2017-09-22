#include "ImageViewerComponentDisplay.h"


namespace Capture3
{

	ImageViewerComponentDisplay::ImageViewerComponentDisplay() :
		GraphicViewComponent()
	{
		// Create image
		pixmap = addPixmap(QPixmap());
		pixmap->setTransformationMode(Qt::FastTransformation);

		// Create cursor
		cursor = addPixmap(QPixmap(FILE_CURSOR_PICKER));
		cursor->setTransformationMode(Qt::FastTransformation);
		cursor->setOffset(-8, -8);
		cursor->setPos(0, 0);
		cursor->hide();
	}


	ImageViewerComponentDisplay::~ImageViewerComponentDisplay()
	{
		//
	}


	void ImageViewerComponentDisplay::show(const QImage &image)
	{
		if (image.isNull()) {
			pixmap->setPixmap(QPixmap());
			cursor->hide();
		} else {
			pixmap->setPixmap(getPixmap(image, window()->devicePixelRatio()));
			cursor->show();
		}
	}


	void ImageViewerComponentDisplay::setCursorPosition(const int posX, const int posY)
	{
		cursor->setPos(posX, posY);
	}


	void ImageViewerComponentDisplay::mousePressEvent(QMouseEvent *event)
	{
		// Find position on image and emit signal
		if (event->button() == Qt::RightButton) {
			QPointF position = mapToScene(event->pos().x(), event->pos().y());
			auto posX = (int) std::floor(position.x());
			auto posY = (int) std::floor(position.y());
			emit showColor(posX, posY);
		}

		GraphicViewComponent::mousePressEvent(event);
	}


	void ImageViewerComponentDisplay::mouseReleaseEvent(QMouseEvent *event)
	{
		GraphicViewComponent::mouseReleaseEvent(event);
	}


	void ImageViewerComponentDisplay::keyPressEvent(QKeyEvent *event)
	{
		event->accept();
	}


	void ImageViewerComponentDisplay::keyReleaseEvent(QKeyEvent *event)
	{
		// Zoom in
		if (event->key() == Qt::Key_Plus ||
			event->key() == Qt::Key_Equal) {
			event->accept();
			scale(2, 2);
		}

		// Zoom out
		if (event->key() == Qt::Key_Minus ||
			event->key() == Qt::Key_Underscore) {
			event->accept();
			scale(0.5, 0.5);
		}

		event->ignore();
	}
}
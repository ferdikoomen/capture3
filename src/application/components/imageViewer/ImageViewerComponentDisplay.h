#ifndef CAPTURE3_IMAGE_VIEWER_COMPONENT_DISPLAY_H
#define CAPTURE3_IMAGE_VIEWER_COMPONENT_DISPLAY_H


#include <cmath>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGraphicsPixmapItem>
#include <QtGui/QPixmap>
#include <QtGui/QImage>
#include <QtGui/QMouseEvent>
#include <QtGui/QKeyEvent>


#include "../graphicView/GraphicViewComponent.h"
#include "../../../constants/ResourceConstants.h"
#include "../../../utils/PixmapUtils.h"


namespace Capture3
{
	class ImageViewerComponentDisplay final : public GraphicViewComponent
	{
		Q_OBJECT

		public:
			ImageViewerComponentDisplay();

			virtual ~ImageViewerComponentDisplay();

			void show(const QImage &image);

			void setCursorPosition(const int posX, const int posY);

		signals:

			void showColor(const int x, const int y);

		protected:
			virtual void mousePressEvent(QMouseEvent *event);

			virtual void mouseReleaseEvent(QMouseEvent *event);

			virtual void keyPressEvent(QKeyEvent *event);

			virtual void keyReleaseEvent(QKeyEvent *event);

		private:
			QGraphicsPixmapItem *pixmap;
			QGraphicsPixmapItem *cursor;
	};
}


#endif // CAPTURE3_IMAGE_VIEWER_COMPONENT_DISPLAY_H

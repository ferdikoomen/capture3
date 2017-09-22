#ifndef CAPTURE3_GRAPHIC_VIEW_COMPONENT_H
#define CAPTURE3_GRAPHIC_VIEW_COMPONENT_H


#include <QtWidgets/QWidget>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsPixmapItem>
#include <QtGui/QKeyEvent>
#include <QtGui/QMouseEvent>
#include <QtGui/QWheelEvent>
#include <QtGui/QFocusEvent>
#include <QtGui/QImage>
#include <QtGui/QPixmap>
#include <QtGui/QCursor>


namespace Capture3
{
	class GraphicViewComponent : public QGraphicsView
	{
		Q_OBJECT

		public:
			GraphicViewComponent();

			virtual ~GraphicViewComponent();

			QGraphicsPixmapItem *addPixmap(const QPixmap &pixmap);

		protected:
			virtual void mousePressEvent(QMouseEvent *event);

			virtual void mouseReleaseEvent(QMouseEvent *event);

			virtual void wheelEvent(QWheelEvent *event);

		private:
			QGraphicsScene scene;
	};
}


#endif // CAPTURE3_GRAPHIC_VIEW_COMPONENT_H

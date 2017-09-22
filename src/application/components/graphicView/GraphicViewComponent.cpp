#include "GraphicViewComponent.h"


namespace Capture3
{

	GraphicViewComponent::GraphicViewComponent() :
		QGraphicsView(),
		scene()
	{
		// Set view options
		setFocusPolicy(Qt::ClickFocus);
		setMouseTracking(false);
		setScene(&scene);
		setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
		setResizeAnchor(QGraphicsView::AnchorUnderMouse);
		setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

		// Hide scroll bars
		setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

		// Set zoom to 1 (default)
		scale(1.0, 1.0);
	}


	GraphicViewComponent::~GraphicViewComponent()
	{
		scene.deleteLater();
	}


	QGraphicsPixmapItem *GraphicViewComponent::addPixmap(const QPixmap &pixmap)
	{
		return scene.addPixmap(pixmap);
	}


	void GraphicViewComponent::mousePressEvent(QMouseEvent *event)
	{
		if (event->button() == Qt::LeftButton) {
			setDragMode(QGraphicsView::ScrollHandDrag);
		}
		QGraphicsView::mousePressEvent(event);
	}


	void GraphicViewComponent::mouseReleaseEvent(QMouseEvent *event)
	{
		if (event->button() == Qt::LeftButton) {
			setDragMode(QGraphicsView::NoDrag);
		}
		QGraphicsView::mouseReleaseEvent(event);
	}


	void GraphicViewComponent::wheelEvent(QWheelEvent *event)
	{
		event->ignore();
	}
}
#ifndef CAPTURE3_CAMERA_PREVIEW_COMPONENT_PREVIEW_H
#define CAPTURE3_CAMERA_PREVIEW_COMPONENT_PREVIEW_H


#include <QtWidgets/QWidget>
#include <QtGui/QPainter>
#include <QtGui/QImage>
#include <QtGui/QPixmap>
#include <QtGui/QColor>
#include <QtGui/QMouseEvent>


#include "../graphic/GraphicComponent.h"
#include "../../../constants/CameraConstants.h"
#include "../../../engine/objects/camera/Camera.h"


namespace Capture3
{
	class CameraPreviewComponentImage final : public GraphicComponent
	{
		Q_OBJECT

		public:
			CameraPreviewComponentImage(Camera &camera);

			virtual ~CameraPreviewComponentImage();

		protected:
			virtual void mousePressEvent(QMouseEvent *event);

			virtual void draw(QPainter &painter);

		private:
			Camera &camera;
			const QColor colorBackground;
			const QColor colorForeground;
			const QColor colorLines;
			QPen focusLine;
			double focusX;
			double focusY;

	};
}


#endif // CAPTURE3_CAMERA_PREVIEW_COMPONENT_PREVIEW_H

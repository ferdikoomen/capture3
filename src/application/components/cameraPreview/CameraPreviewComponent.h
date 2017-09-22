#ifndef CAPTURE3_CAMERA_PREVIEW_COMPONENT_H
#define CAPTURE3_CAMERA_PREVIEW_COMPONENT_H


#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtGui/QPainter>
#include <QtGui/QColor>
#include <QtCore/QTimer>


#include "CameraPreviewComponentImage.h"
#include "../panelTab/PanelTabComponent.h"
#include "../../../engine/objects/camera/Camera.h"


namespace Capture3
{
	class CameraPreviewComponent final : public PanelTabComponent
	{
		Q_OBJECT

		public:
			CameraPreviewComponent(Camera &camera);

			virtual ~CameraPreviewComponent();

		private:
			Camera &camera;
			CameraPreviewComponentImage image;
			QLabel labelBattery;

	};
}


#endif // CAPTURE3_CAMERA_PREVIEW_COMPONENT_H

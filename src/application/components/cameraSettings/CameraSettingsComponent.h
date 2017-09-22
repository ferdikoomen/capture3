#ifndef CAPTURE3_CAMERA_SETTINGS_COMPONENT_H
#define CAPTURE3_CAMERA_SETTINGS_COMPONENT_H


#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QPushButton>


#include "../panelTab/PanelTabComponent.h"
#include "../../../engine/objects/camera/Camera.h"
#include "../../../constants/CameraConstants.h"


namespace Capture3
{
	class CameraSettingsComponent final : public PanelTabComponent
	{
		Q_OBJECT

		public:
			CameraSettingsComponent(Camera &camera);

			virtual ~CameraSettingsComponent();

		private:
			Camera &camera;
			QLabel labelCameraName;
			QLabel labelCameraPort;
			QLabel labelWhiteBalance;
			QLabel labelColorSpace;
			QLabel labelExposureCompensation;
			QLabel labelImageSize;
			QLabel labelImageQuality;
			QLabel labelDynamicLighting;
			QLabel labelLongExposure;
			QLabel labelAssistLight;
			QLabel labelFlashMode;
			QLabel labelFocusMeterMode;
			QLabel labelExposureMeterMode;
			QLabel labelFocusModeLiveView;
			QLabel labelExposureProgram;
			QLabel labelCaptureMode;
			QLabel labelRecordingMedia;
			QLabel labelCaptureTarget;
			QLineEdit fieldCameraName;
			QLineEdit fieldCameraPort;
			QLineEdit fieldWhiteBalance;
			QLineEdit fieldColorSpace;
			QLineEdit fieldExposureCompensation;
			QLineEdit fieldImageSize;
			QLineEdit fieldImageQuality;
			QLineEdit fieldDynamicLighting;
			QLineEdit fieldLongExposure;
			QLineEdit fieldAssistLight;
			QLineEdit fieldFlashMode;
			QLineEdit fieldFocusMeterMode;
			QLineEdit fieldExposureMeterMode;
			QLineEdit fieldFocusModeLiveView;
			QLineEdit fieldExposureProgram;
			QLineEdit fieldCaptureMode;
			QLineEdit fieldRecordingMedia;
			QLineEdit fieldCaptureTarget;
			QPushButton button;

	};
}


#endif // CAPTURE3_CAMERA_SETTINGS_COMPONENT_H

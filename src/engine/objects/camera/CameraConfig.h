#ifndef CAPTURE3_CAMERA_CONFIG_H
#define CAPTURE3_CAMERA_CONFIG_H


#include <QtCore/QString>


#include "CameraConnection.h"
#include "CameraConfigItem.h"
#include "../../../constants/CameraConstants.h"


namespace Capture3
{
	class CameraConfig final
	{
		public:
			CameraConfig(CameraConnection &connection);

			virtual ~CameraConfig();

			void write();

			CameraConfigItem &getShutterSpeed();

			CameraConfigItem &getShutterSpeed2();

			CameraConfigItem &getAperture();

			CameraConfigItem &getIso();

			CameraConfigItem &getIsoAuto();

			CameraConfigItem &getWhiteBalance();

			CameraConfigItem &getColorSpace();

			CameraConfigItem &getExposureCompensation();

			CameraConfigItem &getImageSize();

			CameraConfigItem &getImageQuality();

			CameraConfigItem &getDynamicLighting();

			CameraConfigItem &getLongExposure();

			CameraConfigItem &getAssistLight();

			CameraConfigItem &getFlashMode();

			CameraConfigItem &getFocusMeterMode();

			CameraConfigItem &getExposureMeterMode();

			CameraConfigItem &getFocusMode();

			CameraConfigItem &getFocusModeLiveView();

			CameraConfigItem &getFocusArea();

			CameraConfigItem &getAutoFocusDrive();

			CameraConfigItem &getManualFocusDrive();

			CameraConfigItem &getFocalLengthMin();

			CameraConfigItem &getFocalLengthMax();

			CameraConfigItem &getExposureProgram();

			CameraConfigItem &getCaputureMode();

			CameraConfigItem &getRecordingMedia();

			CameraConfigItem &getCaptureTarget();

			CameraConfigItem &getBatteryLevel();

		private:
			CameraConfigItem shutterSpeed;
			CameraConfigItem shutterSpeed2;
			CameraConfigItem aperture;
			CameraConfigItem iso;
			CameraConfigItem isoAuto;
			CameraConfigItem whiteBalance;
			CameraConfigItem colorSpace;
			CameraConfigItem exposureCompensation;
			CameraConfigItem imageSize;
			CameraConfigItem imageQuality;
			CameraConfigItem dynamicLighting;
			CameraConfigItem longExposure;
			CameraConfigItem assistLight;
			CameraConfigItem flashMode;
			CameraConfigItem focusMeterMode;
			CameraConfigItem exposureMeterMode;
			CameraConfigItem focusMode;
			CameraConfigItem focusModeLiveView;
			CameraConfigItem focusArea;
			CameraConfigItem autoFocusDrive;
			CameraConfigItem manualFocusDrive;
			CameraConfigItem focalLengthMin;
			CameraConfigItem focalLengthMax;
			CameraConfigItem exposureProgram;
			CameraConfigItem caputureMode;
			CameraConfigItem recordingMedia;
			CameraConfigItem captureTarget;
			CameraConfigItem batteryLevel;

	};
}

#endif // CAPTURE3_CAMERA_CONFIG_H

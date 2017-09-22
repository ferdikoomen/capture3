#include "CameraSettingsComponent.h"


namespace Capture3
{

	CameraSettingsComponent::CameraSettingsComponent(Camera &camera) :
		PanelTabComponent("Camera Settings"),
		camera(camera),

		// Labels
		labelCameraName("Camera Name"),
		labelCameraPort("Camera Port"),
		labelWhiteBalance("White Balance"),
		labelColorSpace("Color Space"),
		labelExposureCompensation("Exposure Compensation"),
		labelImageSize("Image Size"),
		labelImageQuality("Image Quality"),
		labelDynamicLighting("Dynamic Lighting"),
		labelLongExposure("Long Exposure"),
		labelAssistLight("Assist Light"),
		labelFlashMode("Flash Mode"),
		labelFocusMeterMode("Focus Meter Mode"),
		labelExposureMeterMode("Exposure Meter Mode"),
		labelFocusModeLiveView("FocusMode Live View"),
		labelExposureProgram("Exposure Program"),
		labelCaptureMode("Capture Mode"),
		labelRecordingMedia("Recording Media"),
		labelCaptureTarget("Capture Target"),

		// Fields
		fieldCameraName(CAMERA_CONNECTION_MODEL),
		fieldCameraPort(CAMERA_CONNECTION_PORT),
		fieldWhiteBalance(CAMERA_DEFAULT_WHITE_BALANCE),
		fieldColorSpace(CAMERA_DEFAULT_COLOR_SPACE),
		fieldExposureCompensation(CAMERA_DEFAULT_EXPOSURE_COMPENSATION),
		fieldImageSize(CAMERA_DEFAULT_IMAGE_SIZE),
		fieldImageQuality(CAMERA_DEFAULT_IMAGE_QUALITY),
		fieldDynamicLighting(CAMERA_DEFAULT_DYNAMIC_LIGHTING),
		fieldLongExposure(CAMERA_DEFAULT_LONG_EXPOSURE),
		fieldAssistLight(CAMERA_DEFAULT_ASSIST_LIGHT),
		fieldFlashMode(CAMERA_DEFAULT_FLASH_MODE),
		fieldFocusMeterMode(CAMERA_DEFAULT_FOCUS_METER_MODE),
		fieldExposureMeterMode(CAMERA_DEFAULT_EXPOSURE_METER_MODE),
		fieldFocusModeLiveView(CAMERA_DEFAULT_FOCUS_MODE_LIVE_VIEW),
		fieldExposureProgram(CAMERA_DEFAULT_EXPOSURE_PROGRAM),
		fieldCaptureMode(CAMERA_DEFAULT_CAPUTURE_MODE),
		fieldRecordingMedia(CAMERA_DEFAULT_RECORDING_MEDIA),
		fieldCaptureTarget(CAMERA_DEFAULT_CAPTURE_TARGET),

		// Reconnect camera button
		button("Reconnect")
	{
		// Set fields read only
		fieldCameraName.setReadOnly(true);
		fieldCameraPort.setReadOnly(true);
		fieldWhiteBalance.setReadOnly(true);
		fieldColorSpace.setReadOnly(true);
		fieldExposureCompensation.setReadOnly(true);
		fieldImageSize.setReadOnly(true);
		fieldImageQuality.setReadOnly(true);
		fieldDynamicLighting.setReadOnly(true);
		fieldLongExposure.setReadOnly(true);
		fieldAssistLight.setReadOnly(true);
		fieldFlashMode.setReadOnly(true);
		fieldFocusMeterMode.setReadOnly(true);
		fieldExposureMeterMode.setReadOnly(true);
		fieldFocusModeLiveView.setReadOnly(true);
		fieldExposureProgram.setReadOnly(true);
		fieldCaptureMode.setReadOnly(true);
		fieldRecordingMedia.setReadOnly(true);
		fieldCaptureTarget.setReadOnly(true);

		// Add items
		addWidget(&labelCameraName);
		addWidget(&fieldCameraName);
		addWidget(&labelCameraPort);
		addWidget(&fieldCameraPort);
		addWidget(&labelWhiteBalance);
		addWidget(&fieldWhiteBalance);
		addWidget(&labelColorSpace);
		addWidget(&fieldColorSpace);
		addWidget(&labelExposureCompensation);
		addWidget(&fieldExposureCompensation);
		addWidget(&labelImageSize);
		addWidget(&fieldImageSize);
		addWidget(&labelImageQuality);
		addWidget(&fieldImageQuality);
		addWidget(&labelDynamicLighting);
		addWidget(&fieldDynamicLighting);
		addWidget(&labelLongExposure);
		addWidget(&fieldLongExposure);
		addWidget(&labelAssistLight);
		addWidget(&fieldAssistLight);
		addWidget(&labelFlashMode);
		addWidget(&fieldFlashMode);
		addWidget(&labelFocusMeterMode);
		addWidget(&fieldFocusMeterMode);
		addWidget(&labelExposureMeterMode);
		addWidget(&fieldExposureMeterMode);
		addWidget(&labelFocusModeLiveView);
		addWidget(&fieldFocusModeLiveView);
		addWidget(&labelExposureProgram);
		addWidget(&fieldExposureProgram);
		addWidget(&labelCaptureMode);
		addWidget(&fieldCaptureMode);
		addWidget(&labelRecordingMedia);
		addWidget(&fieldRecordingMedia);
		addWidget(&labelCaptureTarget);
		addWidget(&fieldCaptureTarget);
		addWidget(&button);

		// Add some spacing around the button
		setRowMinimumHeight(36, 50);

		// Reconnect camera
		QObject::connect(&button, &QPushButton::clicked, this, [this]() {
			this->camera.disconnect();
			this->camera.connect();
		});
	}


	CameraSettingsComponent::~CameraSettingsComponent()
	{
		QObject::disconnect(&button, nullptr, nullptr, nullptr);

		labelCameraName.deleteLater();
		labelCameraPort.deleteLater();
		labelWhiteBalance.deleteLater();
		labelColorSpace.deleteLater();
		labelExposureCompensation.deleteLater();
		labelImageSize.deleteLater();
		labelImageQuality.deleteLater();
		labelDynamicLighting.deleteLater();
		labelLongExposure.deleteLater();
		labelAssistLight.deleteLater();
		labelFlashMode.deleteLater();
		labelFocusMeterMode.deleteLater();
		labelExposureMeterMode.deleteLater();
		labelFocusModeLiveView.deleteLater();
		labelExposureProgram.deleteLater();
		labelCaptureMode.deleteLater();
		labelRecordingMedia.deleteLater();
		labelCaptureTarget.deleteLater();
		fieldCameraName.deleteLater();
		fieldCameraPort.deleteLater();
		fieldWhiteBalance.deleteLater();
		fieldColorSpace.deleteLater();
		fieldExposureCompensation.deleteLater();
		fieldImageSize.deleteLater();
		fieldImageQuality.deleteLater();
		fieldDynamicLighting.deleteLater();
		fieldLongExposure.deleteLater();
		fieldAssistLight.deleteLater();
		fieldFlashMode.deleteLater();
		fieldFocusMeterMode.deleteLater();
		fieldExposureMeterMode.deleteLater();
		fieldFocusModeLiveView.deleteLater();
		fieldExposureProgram.deleteLater();
		fieldCaptureMode.deleteLater();
		fieldRecordingMedia.deleteLater();
		fieldCaptureTarget.deleteLater();
		button.deleteLater();
	}

}
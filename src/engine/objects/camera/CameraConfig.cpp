#include "CameraConfig.h"


namespace Capture3
{

	CameraConfig::CameraConfig(CameraConnection &connection) :
		shutterSpeed(CAMERA_KEY_SHUTTER_SPEED, connection),
		shutterSpeed2(CAMERA_KEY_SHUTTER_SPEED2, connection),
		aperture(CAMERA_KEY_APERTURE, connection),
		iso(CAMERA_KEY_ISO, connection),
		isoAuto(CAMERA_KEY_ISO_AUTO, connection),
		whiteBalance(CAMERA_KEY_WHITE_BALANCE, connection),
		colorSpace(CAMERA_KEY_COLOR_SPACE, connection),
		exposureCompensation(CAMERA_KEY_EXPOSURE_COMPENSATION, connection),
		imageSize(CAMERA_KEY_IMAGE_SIZE, connection),
		imageQuality(CAMERA_KEY_IMAGE_QUALITY, connection),
		dynamicLighting(CAMERA_KEY_DYNAMIC_LIGHTING, connection),
		longExposure(CAMERA_KEY_LONG_EXPOSURE, connection),
		assistLight(CAMERA_KEY_ASSIST_LIGHT, connection),
		flashMode(CAMERA_KEY_FLASH_MODE, connection),
		focusMeterMode(CAMERA_KEY_FOCUS_METER_MODE, connection),
		exposureMeterMode(CAMERA_KEY_EXPOSURE_METER_MODE, connection),
		focusMode(CAMERA_KEY_FOCUS_MODE, connection),
		focusModeLiveView(CAMERA_KEY_FOCUS_MODE_LIVE_VIEW, connection),
		focusArea(CAMERA_KEY_FOCUS_AREA, connection),
		autoFocusDrive(CAMERA_KEY_AUTO_FOCUS_DRIVE, connection),
		manualFocusDrive(CAMERA_KEY_MANUAL_FOCUS_DRIVE, connection),
		focalLengthMin(CAMERA_KEY_FOCAL_LENGTH_MIN, connection),
		focalLengthMax(CAMERA_KEY_FOCAL_LENGTH_MAX, connection),
		exposureProgram(CAMERA_KEY_EXPOSURE_PROGRAM, connection),
		caputureMode(CAMERA_KEY_CAPUTURE_MODE, connection),
		recordingMedia(CAMERA_KEY_RECORDING_MEDIA, connection),
		captureTarget(CAMERA_KEY_CAPTURE_TARGET, connection),
		batteryLevel(CAMERA_KEY_BATTERY_LEVEL, connection)
	{
		// Set defaults
		shutterSpeed.setValue(CAMERA_DEFAULT_SHUTTER_SPEED);
		shutterSpeed2.setValue(CAMERA_DEFAULT_SHUTTER_SPEED2);
		aperture.setValue(CAMERA_DEFAULT_APERTURE);
		iso.setValue(CAMERA_DEFAULT_ISO);
		isoAuto.setValue(CAMERA_DEFAULT_ISO_AUTO);
		whiteBalance.setValue(CAMERA_DEFAULT_WHITE_BALANCE);
		colorSpace.setValue(CAMERA_DEFAULT_COLOR_SPACE);
		exposureCompensation.setValue(CAMERA_DEFAULT_EXPOSURE_COMPENSATION);
		imageSize.setValue(CAMERA_DEFAULT_IMAGE_SIZE);
		imageQuality.setValue(CAMERA_DEFAULT_IMAGE_QUALITY);
		dynamicLighting.setValue(CAMERA_DEFAULT_DYNAMIC_LIGHTING);
		longExposure.setValue(CAMERA_DEFAULT_LONG_EXPOSURE);
		assistLight.setValue(CAMERA_DEFAULT_ASSIST_LIGHT);
		flashMode.setValue(CAMERA_DEFAULT_FLASH_MODE);
		focusMode.setValue(CAMERA_DEFAULT_FOCUS_MODE);
		focusMeterMode.setValue(CAMERA_DEFAULT_FOCUS_METER_MODE);
		exposureMeterMode.setValue(CAMERA_DEFAULT_EXPOSURE_METER_MODE);
		focusModeLiveView.setValue(CAMERA_DEFAULT_FOCUS_MODE_LIVE_VIEW);
		exposureProgram.setValue(CAMERA_DEFAULT_EXPOSURE_PROGRAM);
		caputureMode.setValue(CAMERA_DEFAULT_CAPUTURE_MODE);
		recordingMedia.setValue(CAMERA_DEFAULT_RECORDING_MEDIA);
		captureTarget.setValue(CAMERA_DEFAULT_CAPTURE_TARGET);
	}


	CameraConfig::~CameraConfig()
	{
		//
	}


	void CameraConfig::write()
	{
		// Write complete config
		shutterSpeed.write();
		shutterSpeed2.write();
		aperture.write();
		iso.write();
		isoAuto.write();
		whiteBalance.write();
		colorSpace.write();
		exposureCompensation.write();
		imageSize.write();
		imageQuality.write();
		dynamicLighting.write();
		longExposure.write();
		assistLight.write();
		flashMode.write();
		focusMode.write();
		focusMeterMode.write();
		exposureMeterMode.write();
		focusModeLiveView.write();
		exposureProgram.write();
		caputureMode.write();
		recordingMedia.write();
		captureTarget.write();
	}


	CameraConfigItem &CameraConfig::getShutterSpeed()
	{ return shutterSpeed; }

	CameraConfigItem &CameraConfig::getShutterSpeed2()
	{ return shutterSpeed2; }

	CameraConfigItem &CameraConfig::getAperture()
	{ return aperture; }

	CameraConfigItem &CameraConfig::getIso()
	{ return iso; }

	CameraConfigItem &CameraConfig::getIsoAuto()
	{ return isoAuto; }

	CameraConfigItem &CameraConfig::getWhiteBalance()
	{ return whiteBalance; }

	CameraConfigItem &CameraConfig::getColorSpace()
	{ return colorSpace; }

	CameraConfigItem &CameraConfig::getExposureCompensation()
	{ return exposureCompensation; }

	CameraConfigItem &CameraConfig::getImageSize()
	{ return imageSize; }

	CameraConfigItem &CameraConfig::getImageQuality()
	{ return imageQuality; }

	CameraConfigItem &CameraConfig::getDynamicLighting()
	{ return dynamicLighting; }

	CameraConfigItem &CameraConfig::getLongExposure()
	{ return longExposure; }

	CameraConfigItem &CameraConfig::getAssistLight()
	{ return assistLight; }

	CameraConfigItem &CameraConfig::getFlashMode()
	{ return flashMode; }

	CameraConfigItem &CameraConfig::getFocusMeterMode()
	{ return focusMeterMode; }

	CameraConfigItem &CameraConfig::getExposureMeterMode()
	{ return exposureMeterMode; }

	CameraConfigItem &CameraConfig::getFocusMode()
	{ return focusMode; }

	CameraConfigItem &CameraConfig::getFocusModeLiveView()
	{ return focusModeLiveView; }

	CameraConfigItem &CameraConfig::getFocusArea()
	{ return focusArea; }

	CameraConfigItem &CameraConfig::getAutoFocusDrive()
	{ return autoFocusDrive; }

	CameraConfigItem &CameraConfig::getManualFocusDrive()
	{ return manualFocusDrive; }

	CameraConfigItem &CameraConfig::getFocalLengthMin()
	{ return focalLengthMin; }

	CameraConfigItem &CameraConfig::getFocalLengthMax()
	{ return focalLengthMax; }

	CameraConfigItem &CameraConfig::getExposureProgram()
	{ return exposureProgram; }

	CameraConfigItem &CameraConfig::getCaputureMode()
	{ return caputureMode; }

	CameraConfigItem &CameraConfig::getRecordingMedia()
	{ return recordingMedia; }

	CameraConfigItem &CameraConfig::getCaptureTarget()
	{ return captureTarget; }

	CameraConfigItem &CameraConfig::getBatteryLevel()
	{ return batteryLevel; }
}
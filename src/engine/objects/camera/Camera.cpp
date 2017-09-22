#include "Camera.h"


namespace Capture3
{

	Camera::Camera(Project &project) :
		QObject(),
		project(project),
		connection(CAMERA_CONNECTION_MODEL, CAMERA_CONNECTION_PORT),
		config(connection),
		exposureSettings(
			CAMERA_SETTING_APERTURE_MIN,
			CAMERA_SETTING_APERTURE_MAX,
			CAMERA_SETTING_SHUTTER_SPEED_MIN,
			CAMERA_SETTING_SHUTTER_SPEED_MAX,
			CAMERA_SETTING_ISO_MIN,
			CAMERA_SETTING_ISO_MAX,
			CAMERA_SETTING_STOPS_APERTURE,
			CAMERA_SETTING_STOPS_SHUTTER_SPEED,
			CAMERA_SETTING_STOPS_ISO
		),
		exposureMatrix(exposureSettings),
		settings(),
		preview(),
		rawProcessor(),
		timerPreview(),
		timerBatteryLevel(),
		batteryLevel("0%"),
		count(0)
	{
		// Update camera preview
		QObject::connect(&timerPreview, &QTimer::timeout, this, &Camera::fetchPreview);
		QObject::connect(&timerBatteryLevel, &QTimer::timeout, this, &Camera::fetchBatteryLevel);

		// Start timers
		timerPreview.start(CAMERA_UPDATE_PREVIEW);
		timerBatteryLevel.start(CAMERA_UPDATE_BATTERY_LEVEL);
	}


	Camera::~Camera()
	{
		// Stop preview timer
		QObject::disconnect(&timerPreview, nullptr, nullptr, nullptr);
		timerPreview.stop();
		timerPreview.deleteLater();

		// Stop battery level timer
		QObject::disconnect(&timerBatteryLevel, nullptr, nullptr, nullptr);
		timerBatteryLevel.stop();
		timerBatteryLevel.deleteLater();
	}


	void Camera::connect()
	{
		if (connection.connect()) {
			config.write();
			timerPreview.start(CAMERA_UPDATE_PREVIEW);
			timerBatteryLevel.start(CAMERA_UPDATE_BATTERY_LEVEL);
			fetchPreview();
			fetchBatteryLevel();
		}
	}


	void Camera::disconnect()
	{
		connection.disconnect();
		timerPreview.stop();
		timerBatteryLevel.stop();
	}


	void Camera::moveFocus(const int value)
	{
		if (value != 0) {
			config.getManualFocusDrive().setValue(value * CAMERA_SETTING_FOCUS_MULTIPLIER);
		}
	}


	void Camera::autoFocus(const double x, const double y)
	{
		// Calculate focus position for camera
		QString sx = QString::number(std::round(x * CAMERA_IMAGE_WIDTH), 'f', 0);
		QString sy = QString::number(std::round(y * CAMERA_IMAGE_HEIGHT), 'f', 0);

		// Set focus area and try to auto-focus
		config.getFocusArea().setValue(sx + "x" + sy);
		config.getAutoFocusDrive().toggle();
	}


	Image *Camera::capture(
		const unsigned int indexAperture,
		const unsigned int indexShutterSpeed,
		const unsigned int indexIso,
		const unsigned int indexShots,
		const unsigned int indexRange,
		const unsigned int indexStep,
		const unsigned int indexMergeShots,
		const unsigned int indexMergeRange,
		const int focusNear,
		const int focusFar
	)
	{
		// Fetch range for shutter speed (HDR)
		const unsigned int exposureStep = indexStep + 1;
		const unsigned int exposureStart = indexShutterSpeed - (indexRange * exposureStep);
		const unsigned int exposureEnd = indexShutterSpeed + (indexRange * exposureStep);
		const unsigned int exposureRange = indexRange * 2;

		// Check if we need to focus in between shots
		const bool focus = focusNear != 0 || focusFar != 0;
		const int focusRange = focusNear + focusFar;

		// First move the focus to the start position (near)
		if (focus) {
			connection.capturePreview();
			moveFocus(-focusNear);
		}

		// Iterate over focus
		for (unsigned int f = 0; f <= focusRange; f++) {

			// Iterate over exposures
			for (unsigned int e = 0; e <= exposureRange; e++) {

				// Fetch current config for shot
				const unsigned int indexExposure = e + exposureStart + (e * indexStep);

				const CameraExposureSettingsItem *settingAperture = exposureSettings.getSettingsAperture(indexAperture);
				const CameraExposureSettingsItem *settingShutterSpeed = exposureSettings.getSettingsShutterSpeed(indexExposure);
				const CameraExposureSettingsItem *settingIso = exposureSettings.getSettingsIso(indexIso);

				// Write config
				config.getAperture().setValue(settingAperture->getValue());
				config.getShutterSpeed().setValue(settingShutterSpeed->getValue());
				config.getIso().setValue(settingIso->getValue());

				// Iterate over shots
				for (unsigned int s = 0; s <= indexShots; s++) {

					// Create new raw file reference and store meta information.
					// We use this file as a settings file to either capture the
					// image from camera or load it from disk.
					auto *raw = new RawFile(
						project.getNextFileRaw(),
						settingAperture,
						settingShutterSpeed,
						settingIso
					);

					// Capture image
					connection.capture(raw->getFilePath());

					// Store for processing
					rawProcessor.add(
						f, // Index Focus
						e, // Index Exposure
						s, // Index Shot
						raw
					);
				}
			}

			// Change focus between shots
			if (focus && f < focusRange) {
				connection.capturePreview();
				moveFocus(1);
			}
		}

		// Reset focus to original position
		if (focus) {
			connection.capturePreview();
			moveFocus(-focusFar);
		}

		// Process captured images
		Image *image = rawProcessor.process(
			indexMergeShots,
			indexMergeRange
		);

		// Store meta data
		if (image != nullptr) {
			image->getMeta().settingAperture = indexAperture;
			image->getMeta().settingShutterSpeed = indexShutterSpeed;
			image->getMeta().settingIso = indexIso;
			image->getMeta().settingShots = indexShots;
			image->getMeta().settingRange = indexRange;
			image->getMeta().settingStep = indexStep;
		}
		return image;
	}


	void Camera::fetchPreview()
	{
		CameraPreview image = connection.capturePreview();
		if (!image.isNull()) {
			preview = image;
			emit onUpdatePreview();
		}
	}


	void Camera::fetchBatteryLevel()
	{
		QString level = config.getBatteryLevel().getValue().toString();
		if (!level.isEmpty()) {
			batteryLevel = level;
			emit onUpdateBatteryLevel();
		}
	}


	const CameraPreview &Camera::getPreview() const
	{
		return preview;
	}


	const QString Camera::getBatteryLevel() const
	{
		return batteryLevel;
	}


	CameraConfig &Camera::getConfig()
	{
		return config;
	}


	const CameraExposureSettings &Camera::getExposureSettings() const
	{
		return exposureSettings;
	}


	const CameraExposureMatrix &Camera::getExposureMatrix() const
	{
		return exposureMatrix;
	}


	const CameraSettings &Camera::getSettings() const
	{
		return settings;
	}

}
#ifndef CAPTURE3_CAMERA_EXPOSURE_SETTINGS_H
#define CAPTURE3_CAMERA_EXPOSURE_SETTINGS_H


#include <cmath>
#include <vector>
#include <QtCore/QString>


#include "CameraExposureSettingsItem.h"
#include "../../../constants/CameraConstants.h"


namespace Capture3
{

	class CameraExposureSettings final
	{
		public:
			CameraExposureSettings(
				const double apertureMin,
				const double apertureMax,
				const double shutterSpeedMin,
				const double shutterSpeedMax,
				const double isoMin,
				const double isoMax,
				const double stopsAperture,
				const double stopsShutterSpeed,
				const double stopsIso
			);

			virtual ~CameraExposureSettings();

			const CameraExposureSettingsItem *getSettingsAperture(const unsigned int index) const;

			const CameraExposureSettingsItem *getSettingsShutterSpeed(const unsigned int index) const;

			const CameraExposureSettingsItem *getSettingsIso(const unsigned int index) const;

			const std::vector<const CameraExposureSettingsItem *> &getSettingsAperture() const;

			const std::vector<const CameraExposureSettingsItem *> &getSettingsShutterSpeed() const;

			const std::vector<const CameraExposureSettingsItem *> &getSettingsIso() const;

		private:
			void addAperture(const QString &label, const double number, const int i);

			void addShutterSpeed(const QString &label, const double number, const int i);

			void addIso(const QString &label, const double number, const int i);

			double getAperture(const int i) const;

			double getShutterSpeed(const int i) const;

			double getIso(const int i) const;

			double getApertureValue(const double aperture) const;

			double getShutterSpeedValue(const double shutterSpeed) const;

			double getIsoValue(const double iso) const;

			const double apertureMin;
			const double apertureMax;
			const double shutterSpeedMin;
			const double shutterSpeedMax;
			const double isoMin;
			const double isoMax;
			const double stopsAperture;
			const double stopsShutterSpeed;
			const double stopsIso;

			std::vector<const CameraExposureSettingsItem *> settingsAperture;
			std::vector<const CameraExposureSettingsItem *> settingsShutterSpeed;
			std::vector<const CameraExposureSettingsItem *> settingsIso;
	};
}


#endif // CAPTURE3_CAMERA_EXPOSURE_SETTINGS_H

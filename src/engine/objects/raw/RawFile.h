#ifndef CAPTURE3_RAW_FILE_H
#define CAPTURE3_RAW_FILE_H


#include <QtCore/QString>
#include <QtCore/QFile>
#include <QtCore/QFileInfo>


#include "../camera/CameraExposureSettingsItem.h"


namespace Capture3
{
	class RawFile final
	{

		public:
			RawFile(
				const QFileInfo file,
				const CameraExposureSettingsItem *settingAperture,
				const CameraExposureSettingsItem *settingShutterSpeed,
				const CameraExposureSettingsItem *settingIso
			);

			virtual ~RawFile();

			const QString getFileFolder() const;

			const QString getFileName() const;

			const QString getFilePath() const;

			const CameraExposureSettingsItem *getAperture() const;

			const CameraExposureSettingsItem *getShutterSpeed() const;

			const CameraExposureSettingsItem *getIso() const;

		private:
			const QFileInfo file;
			const QString fileFolder;
			const QString fileName;
			const QString filePath;
			const CameraExposureSettingsItem *settingAperture;
			const CameraExposureSettingsItem *settingShutterSpeed;
			const CameraExposureSettingsItem *settingIso;
	};
}

#endif // CAPTURE3_CAMERA_RAW_FILE_H

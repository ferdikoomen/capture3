#ifndef CAPTURE3_CAMERA_H
#define CAPTURE3_CAMERA_H


#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QTimer>
#include <QtGui/QImage>


#include "CameraConnection.h"
#include "CameraConfig.h"
#include "CameraExposureSettings.h"
#include "CameraExposureMatrix.h"
#include "CameraSettings.h"
#include "CameraExposureSettingsItem.h"
#include "CameraPreview.h"
#include "../raw/RawProcessor.h"
#include "../raw/RawFile.h"
#include "../../objects/project/Project.h"
#include "../../objects/image/Image.h"
#include "../../../constants/CameraConstants.h"


namespace Capture3
{

	class Camera final : public QObject
	{
		Q_OBJECT

		public:
			Camera(Project &project);

			virtual ~Camera();

			void connect();

			void disconnect();

			void moveFocus(const int value);

			void autoFocus(const double x, const double y);

			Image *capture(
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
			);

			const CameraPreview &getPreview() const;

			const QString getBatteryLevel() const;

			CameraConfig &getConfig();

			const CameraExposureSettings &getExposureSettings() const;

			const CameraExposureMatrix &getExposureMatrix() const;

			const CameraSettings &getSettings() const;

		signals:

			void onUpdatePreview();

			void onUpdateBatteryLevel();

		private slots:

			void fetchPreview();

			void fetchBatteryLevel();

		private:
			Project &project;
			CameraConnection connection;
			CameraConfig config;
			CameraExposureSettings exposureSettings;
			CameraExposureMatrix exposureMatrix;
			CameraSettings settings;
			CameraPreview preview;
			RawProcessor rawProcessor;
			QTimer timerPreview;
			QTimer timerBatteryLevel;
			QString batteryLevel;
			unsigned int count;
	};
}

#endif // CAPTURE3_CAMERA_H

#ifndef CAPTURE3_CAMERA_SETTINGS_H
#define CAPTURE3_CAMERA_SETTINGS_H


#include <utility>
#include <vector>
#include <QtCore/QString>


#include "../../../constants/CameraConstants.h"


namespace Capture3
{

	class CameraSettings final
	{
		public:
			CameraSettings();

			virtual ~CameraSettings();

			const std::vector<QString> &getSettingsShots() const;

			const std::vector<QString> &getSettingsRange() const;

			const std::vector<QString> &getSettingsStep() const;

			const std::vector<QString> &getSettingsMergeShots() const;

			const std::vector<QString> &getSettingsMergeRange() const;

		private:
			std::vector<QString> settingsShots;
			std::vector<QString> settingsRange;
			std::vector<QString> settingsStep;
			std::vector<QString> settingsMergeShots;
			std::vector<QString> settingsMergeRange;
	};
}


#endif // CAPTURE3_CAMERA_SETTINGS_H

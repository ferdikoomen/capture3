#include "CameraSettings.h"


namespace Capture3
{

	CameraSettings::CameraSettings() :

		settingsShots({"1", "2", "3", "4", "5", "6", "7", "8"}),
		settingsRange({"0", "+/-1", "+/-2", "+/-3", "+/-4", "+/-5"}),
		settingsStep({"1/3", "1/2", "1/1"}),

		settingsMergeShots({
			CAMERA_SETTING_MERGE_MEAN,
			CAMERA_SETTING_MERGE_MEDIAN
		}),

		settingsMergeRange({
			CAMERA_SETTING_MERGE_MEAN,
			CAMERA_SETTING_MERGE_MEDIAN,
			CAMERA_SETTING_MERGE_EXPOSURE_FUSION
		})
	{
		//
	}


	CameraSettings::~CameraSettings()
	{
		settingsShots.clear();
		settingsRange.clear();
		settingsStep.clear();
		settingsMergeShots.clear();
		settingsMergeRange.clear();
	}


	const std::vector<QString> &CameraSettings::getSettingsShots() const
	{
		return settingsShots;
	}


	const std::vector<QString> &CameraSettings::getSettingsRange() const
	{
		return settingsRange;
	}


	const std::vector<QString> &CameraSettings::getSettingsStep() const
	{
		return settingsStep;
	}


	const std::vector<QString> &CameraSettings::getSettingsMergeShots() const
	{
		return settingsMergeShots;
	}


	const std::vector<QString> &CameraSettings::getSettingsMergeRange() const
	{
		return settingsMergeRange;
	}

}
#include "RawFile.h"


namespace Capture3
{

	RawFile::RawFile(
		const QFileInfo file,
		const CameraExposureSettingsItem *settingAperture,
		const CameraExposureSettingsItem *settingShutterSpeed,
		const CameraExposureSettingsItem *settingIso
	) :
		file(file),
		fileFolder(file.path()),
		fileName(file.fileName()),
		filePath(file.filePath()),
		settingAperture(settingAperture),
		settingShutterSpeed(settingShutterSpeed),
		settingIso(settingIso)
	{
		//
	}


	RawFile::~RawFile()
	{
		settingAperture = nullptr;
		settingShutterSpeed = nullptr;
		settingIso = nullptr;
	}


	const QString RawFile::getFileFolder() const
	{
		return fileFolder;
	}


	const QString RawFile::getFileName() const
	{
		return fileName;
	}


	const QString RawFile::getFilePath() const
	{
		return filePath;
	}


	const CameraExposureSettingsItem *RawFile::getAperture() const
	{
		return settingAperture;
	}


	const CameraExposureSettingsItem *RawFile::getShutterSpeed() const
	{
		return settingShutterSpeed;
	}


	const CameraExposureSettingsItem *RawFile::getIso() const
	{
		return settingIso;
	}

}
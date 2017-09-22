#include "CameraExposureMatrix.h"


namespace Capture3
{

	CameraExposureMatrix::CameraExposureMatrix(const CameraExposureSettings &settings) :
		settingsAperture(settings.getSettingsAperture()),
		settingsShutterSpeed(settings.getSettingsShutterSpeed()),
		settingsIso(settings.getSettingsIso()),

		// Get count
		apertureCount((unsigned int) settingsAperture.size()),
		shutterSpeedCount((unsigned int) settingsShutterSpeed.size()),
		isoCount((unsigned int) settingsIso.size()),

		// Fetch min exposure value
		indexMin(
			settingsAperture.front()->getVI() +
			settingsShutterSpeed.front()->getVI() +
			settingsIso.front()->getVI()
		),

		// Fetch max exposure value
		indexMax(
			settingsAperture.back()->getVI() +
			settingsShutterSpeed.back()->getVI() +
			settingsIso.back()->getVI()
		),

		// Calculate matrix size
		width(apertureCount),
		height((unsigned int) (indexMax - indexMin) + 1),
		depth(isoCount),
		size(width * height * depth),
		count(0),

		// Headers
		headersHorizontal(width, ""),
		headersVertical(height * depth, ""),

		// Create data
		data(size, nullptr)
	{
		// Construct matrix
		for (unsigned int a = 0; a < apertureCount; a++) {
			for (unsigned int s = 0; s < shutterSpeedCount; s++) {
				for (unsigned int i = 0; i < isoCount; i++) {

					// Get data
					const CameraExposureSettingsItem *aperture = settingsAperture[a];
					const CameraExposureSettingsItem *shutterSpeed = settingsShutterSpeed[s];
					const CameraExposureSettingsItem *iso = settingsIso[i];

					const double ev = getEV(aperture, shutterSpeed, iso);
					const double lv = getLV(aperture, shutterSpeed, iso);
					const unsigned int index = getIndex(aperture, shutterSpeed, iso);

					// Get position in matrix
					const unsigned int x = a; // Aperture
					const unsigned int y = index; // Exposure Value (scaled)
					const unsigned int z = i; // Iso
					const unsigned int location = x + (y * width) + (z * width * height);

					// Set headers
					headersHorizontal[x] = aperture->getLabel();
					headersVertical[y + (z * height)] = QString::number(ev, 'f', 1) + " / " + QString::number(lv, 'f', 1);

					// Create new item
					if (data[location] == nullptr) {
						data[location] = new CameraExposureMatrixItem(
							ev,
							lv,
							index,
							x, y, z,
							aperture,
							shutterSpeed,
							iso
						);
						count++;
					}
				}
			}
		}
	}


	CameraExposureMatrix::~CameraExposureMatrix()
	{
		data.clear();
	}


	const CameraExposureMatrixItem *CameraExposureMatrix::at(
		const unsigned int x,
		const unsigned int y,
		const unsigned int z
	) const
	{
		const unsigned int index = x + (y * width) + (z * width * height);
		return data[index];
	}


	double CameraExposureMatrix::getEV(
		const CameraExposureSettingsItem *aperture,
		const CameraExposureSettingsItem *shutterSpeed,
		const CameraExposureSettingsItem *iso
	) const
	{
		return aperture->getV() + shutterSpeed->getV() + iso->getV();
	}


	double CameraExposureMatrix::getLV(
		const CameraExposureSettingsItem *aperture,
		const CameraExposureSettingsItem *shutterSpeed,
		const CameraExposureSettingsItem *iso
	) const
	{
		return aperture->getV() + shutterSpeed->getV() - iso->getV();
	}


	unsigned int CameraExposureMatrix::getIndex(
		const CameraExposureSettingsItem *aperture,
		const CameraExposureSettingsItem *shutterSpeed,
		const CameraExposureSettingsItem *iso
	) const
	{
		return (unsigned int) (
			aperture->getVI() +
			shutterSpeed->getVI() +
			iso->getVI()
		) - indexMin;
	}


	const CameraExposureMatrixItem *CameraExposureMatrix::getItem(
		const CameraExposureSettingsItem *aperture,
		const CameraExposureSettingsItem *shutterSpeed,
		const CameraExposureSettingsItem *iso
	) const
	{
		return data[getIndex(
			aperture,
			shutterSpeed,
			iso
		)];
	}


	QString CameraExposureMatrix::getHeaderHorizontal(const unsigned int index) const
	{
		return headersHorizontal[index];
	}


	QString CameraExposureMatrix::getHeaderVertical(const unsigned int index, const unsigned int iso) const
	{
		return headersVertical[index + (iso * height)];
	}


	const unsigned int CameraExposureMatrix::getWidth() const
	{
		return width;
	}


	const unsigned int CameraExposureMatrix::getHeight() const
	{
		return height;
	}


	const unsigned int CameraExposureMatrix::getDepth() const
	{
		return depth;
	}


	const unsigned int CameraExposureMatrix::getSize() const
	{
		return size;
	}


}
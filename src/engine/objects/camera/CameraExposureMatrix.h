#ifndef CAPTURE3_CAMERA_MATRIX_H
#define CAPTURE3_CAMERA_MATRIX_H


#include <cmath>
#include <vector>
#include <QtCore/QString>


#include "CameraExposureSettings.h"
#include "CameraExposureSettingsItem.h"
#include "CameraExposureMatrixItem.h"


namespace Capture3
{

	class CameraExposureMatrix final
	{
		public:
			CameraExposureMatrix(const CameraExposureSettings &settings);

			virtual ~CameraExposureMatrix();

			const CameraExposureMatrixItem *at(
				const unsigned int x,
				const unsigned int y,
				const unsigned int z
			) const;

			double getEV(
				const CameraExposureSettingsItem *aperture,
				const CameraExposureSettingsItem *shutterSpeed,
				const CameraExposureSettingsItem *iso
			) const;

			double getLV(
				const CameraExposureSettingsItem *aperture,
				const CameraExposureSettingsItem *shutterSpeed,
				const CameraExposureSettingsItem *iso
			) const;

			unsigned int getIndex(
				const CameraExposureSettingsItem *aperture,
				const CameraExposureSettingsItem *shutterSpeed,
				const CameraExposureSettingsItem *iso
			) const;

			const CameraExposureMatrixItem *getItem(
				const CameraExposureSettingsItem *aperture,
				const CameraExposureSettingsItem *shutterSpeed,
				const CameraExposureSettingsItem *iso
			) const;

			QString getHeaderHorizontal(const unsigned int index) const;

			QString getHeaderVertical(const unsigned int index, const unsigned int iso) const;

			const unsigned int getWidth() const;

			const unsigned int getHeight() const;

			const unsigned int getDepth() const;

			const unsigned int getSize() const;

		private:
			const std::vector<const CameraExposureSettingsItem *> &settingsAperture;
			const std::vector<const CameraExposureSettingsItem *> &settingsShutterSpeed;
			const std::vector<const CameraExposureSettingsItem *> &settingsIso;

			const unsigned int apertureCount;
			const unsigned int shutterSpeedCount;
			const unsigned int isoCount;
			const int indexMin;
			const int indexMax;
			const unsigned int width;
			const unsigned int height;
			const unsigned int depth;
			const unsigned int size;
			unsigned int count;

			std::vector<QString> headersHorizontal;
			std::vector<QString> headersVertical;

			std::vector<const CameraExposureMatrixItem *> data;
	};
}

#endif // CAPTURE3_CAMERA_MATRIX_H

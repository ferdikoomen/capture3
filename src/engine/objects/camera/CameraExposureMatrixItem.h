#ifndef CAPTURE3_CAMERA_EXPOSURE_MATRIX_ITEM_H
#define CAPTURE3_CAMERA_EXPOSURE_MATRIX_ITEM_H


#include "CameraExposureSettingsItem.h"


namespace Capture3
{

	class CameraExposureMatrixItem final
	{
		public:
			CameraExposureMatrixItem(
				const double ev,
				const double lv,
				const int index,
				const unsigned int x,
				const unsigned int y,
				const unsigned int z,
				const CameraExposureSettingsItem *aperture,
				const CameraExposureSettingsItem *shutterSpeed,
				const CameraExposureSettingsItem *iso
			);

			virtual ~CameraExposureMatrixItem();

			const double getEV() const;

			const double getLV() const;

			const int getIndex() const;

			const unsigned int getX() const;

			const unsigned int getY() const;

			const unsigned int getZ() const;

			const CameraExposureSettingsItem *getAperture() const;

			const CameraExposureSettingsItem *getShutterSpeed() const;

			const CameraExposureSettingsItem *getIso() const;

		private:
			const double ev;
			const double lv;
			const int index;
			const unsigned int x;
			const unsigned int y;
			const unsigned int z;
			const CameraExposureSettingsItem *aperture;
			const CameraExposureSettingsItem *shutterSpeed;
			const CameraExposureSettingsItem *iso;
	};
}

#endif // CAPTURE3_CAMERA_EXPOSURE_MATRIX_ITEM_H

#ifndef CAPTURE3_CAMERA_EXPOSURE_SETTINGS_ITEM_H
#define CAPTURE3_CAMERA_EXPOSURE_SETTINGS_ITEM_H


#include <QtCore/QString>


namespace Capture3
{

	class CameraExposureSettingsItem final
	{
		public:
			CameraExposureSettingsItem(
				const unsigned int index,
				const QString &label,
				const double value,
				const double precise,
				const double v,
				const int vi
			);

			virtual ~CameraExposureSettingsItem();

			const unsigned int getIndex() const;

			const QString getLabel() const;

			const double getValue() const;

			const double getPrecise() const;

			const double getV() const;

			const int getVI() const;

		private:
			const unsigned int index;
			const QString label;
			const double value;
			const double precise;
			const double v;
			const int vi;
	};
}

#endif // CAPTURE3_CAMERA_EXPOSURE_SETTINGS_ITEM_H

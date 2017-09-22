#ifndef CAPTURE3_IMAGE_META_H
#define CAPTURE3_IMAGE_META_H


#include <QtCore/QString>


namespace Capture3
{

	class ImageMeta final
	{

		public:
			ImageMeta();

			virtual ~ImageMeta();

			QString fileName;
			QString filePath;
			unsigned int settingAperture;
			unsigned int settingShutterSpeed;
			unsigned int settingIso;
			unsigned int settingShots;
			unsigned int settingRange;
			unsigned int settingStep;

		private:

	};
}

#endif // CAPTURE3_IMAGE_META_H

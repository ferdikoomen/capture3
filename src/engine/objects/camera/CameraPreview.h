#ifndef CAPTURE3_CAMERA_PREVIEW_H
#define CAPTURE3_CAMERA_PREVIEW_H


#include <QtGui/QImage>
#include <QtCore/QByteArray>


namespace Capture3
{
	class CameraPreview final : public QImage
	{
		public:
			CameraPreview();

			virtual ~CameraPreview();

			void load(const char *fileData, unsigned long int fileSize);

			QImage scale(const unsigned int width, const unsigned int height) const;

		private:
	};
}

#endif // CAPTURE3_CAMERA_PREVIEW_H

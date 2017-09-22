#include "CameraPreview.h"


namespace Capture3
{

	CameraPreview::CameraPreview() :
		QImage()
	{
		//
	}


	CameraPreview::~CameraPreview()
	{
		//
	}


	void CameraPreview::load(const char *fileData, unsigned long int fileSize)
	{
		QByteArray bytes = QByteArray::fromRawData(fileData, (int) fileSize);
		loadFromData(bytes, "JPG");
	}


	QImage CameraPreview::scale(const unsigned int width, const unsigned int height) const
	{
		return scaled(width, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	}

}
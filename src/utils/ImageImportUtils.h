#ifndef CAPTURE3_IMAGE_IMPORT_UTILS_H
#define CAPTURE3_IMAGE_IMPORT_UTILS_H


#include <cmath>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <QtCore/QString>
#include <QtCore/QFileInfo>
#include <QtCore/QFile>
#include <QtCore/QDir>
#include <QtCore/QPair>
#include <QtGui/QImage>
#include <QtGui/QImageReader>
#include <QtWidgets/QFileDialog>


#include "../engine/objects/image/Image.h"


namespace Capture3
{

	static Image *importImageDialog()
	{
		// Select path
		QString path = QFileDialog::getOpenFileName(
			nullptr,
			"Open File",
			"untitled.png",
			"Images (*.png *.jpg)"
		);

		// Check if we selected a valid path
		if (!path.isEmpty()) {

			// Load file
			QImageReader reader(path);
			if (reader.canRead()) {

				// Get file
				const QImage image = reader.read();
				const auto imageWidth = (unsigned int) image.width();
				const auto imageHeight = (unsigned int) image.height();

				// Create new image
				auto *output = new Image(imageWidth, imageHeight);
				double *outputData = output->getRGB().getData();

				// Copy pixels
				unsigned int index = 0;
				for (unsigned int y = 0; y < imageHeight; y++) {
					for (unsigned int x = 0; x < imageWidth; x++) {
						QRgb color = image.pixel(x, y);
						outputData[index++] = qRed(color) / 255.0;
						outputData[index++] = qGreen(color) / 255.0;
						outputData[index++] = qBlue(color) / 255.0;
					}
				}

				// Calculate data
				output->convertRGB(true);
				return output;
			}
		}

		return nullptr;
	}
}


#endif // CAPTURE3_IMAGE_IMPORT_UTILS_H

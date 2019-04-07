#ifndef CAPTURE3_IMAGE_EXPORT_UTILS_H
#define CAPTURE3_IMAGE_EXPORT_UTILS_H


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


namespace Capture3
{

	static void exportImageDialog(const cv::Mat &image)
	{
		// Select path
		const QString path = QFileDialog::getSaveFileName(
			NULL,
			"Save File",
			"untitled.png",
			"Images (*.png)"
		);

		// Check if we selected a valid path
		if (!path.isEmpty()) {

			// Convert to 8 bit image and ejxport

			// TODO: ENABLE
			// cv::Mat temp;
            // image.convertTo(temp, image.channels() == 1 ? CV_8UC1 : CV_8UC3, 255);
            // cv::cvtColor(temp, temp, cv::COLOR_RGB2BGR);
            // cv::imwrite(path.toLatin1().constData(), temp);
            // temp.release();
		}
	}

}


#endif // CAPTURE3_IMAGE_EXPORT_UTILS_H

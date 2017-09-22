#include "CameraPreviewComponentImage.h"


namespace Capture3
{

	CameraPreviewComponentImage::CameraPreviewComponentImage(Camera &camera) :
		GraphicComponent(CAMERA_PREVIEW_WIDTH, CAMERA_PREVIEW_HEIGHT),
		camera(camera),
		colorBackground(COLOR_BACKGROUND),
		colorForeground(COLOR_FOREGROUND),
		colorLines(COLOR_LINES),
		focusLine(COLOR_FOCUS),
		focusX(0.5),
		focusY(0.5)
	{
		// Set thickness of the strokes
		focusLine.setWidth(3);
		focusLine.setCapStyle(Qt::SquareCap);
		focusLine.setJoinStyle(Qt::MiterJoin);

		// Listen to camera preview updates
		QObject::connect(&camera, &Camera::onUpdatePreview, this, [this]() {
			if (isEnabled() && isVisible()) {
				redraw();
			}
		});
	}


	CameraPreviewComponentImage::~CameraPreviewComponentImage()
	{
		QObject::disconnect(&camera, nullptr, nullptr, nullptr);
	}


	void CameraPreviewComponentImage::mousePressEvent(QMouseEvent *event)
	{
		// Store focus (percentage)
		focusX = (double) event->x() / (double) width();
		focusY = (double) event->y() / (double) height();

		// Redraw interface to show selected area
		redraw();
		event->accept();

		// Auto focus camera on that area
		camera.autoFocus(focusX, focusY);
	}


	void CameraPreviewComponentImage::draw(QPainter &painter)
	{
		GraphicComponent::draw(painter);

		// Get size
		const int w = width();
		const int h = height();

		// Draw preview
		if (!camera.getPreview().isNull() && w > 0 && h > 0) {
			painter.drawImage(0, 0, camera.getPreview().scale(
				(unsigned int) w,
				(unsigned int) h
			));
		}

		// Draw lines
		painter.fillRect(QRect(0, (int) std::lround(h * 0.33), w, 1), colorLines);
		painter.fillRect(QRect(0, (int) std::lround(h * 0.66), w, 1), colorLines);
		painter.fillRect(QRect((int) std::lround(w * 0.33), 0, 1, h), colorLines);
		painter.fillRect(QRect((int) std::lround(w * 0.66), 0, 1, h), colorLines);

		// Draw focus
		painter.setPen(focusLine);
		painter.drawRect((QRect(
			(int) std::lround(w * focusX - 10.0),
			(int) std::lround(h * focusY - 10.0),
			20,
			20
		)));
	}

}
#include "GraphicComponent.h"


namespace Capture3
{

	GraphicComponent::GraphicComponent(
		const unsigned int width,
		const unsigned int height
	) :
		QLabel(),
		ratio((double) width / (double) height),
		backgroundColor(COLOR_FOREGROUND),
		backgroundImage()
	{
		// Fix margin (can't be done in CSS)
		setStyleSheet("margin: 0px;");

		// Set object name for easy styling
		setObjectName("image");

		// Don't allow focusing on this component
		setFocusPolicy(Qt::NoFocus);

		// Setup for aspect ratio scaling
		QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
		sizePolicy.setHeightForWidth(true);
		setSizePolicy(sizePolicy);
		setScaledContents(false);
		setMinimumSize(1, 1);
	}


	GraphicComponent::~GraphicComponent()
	{
		//
	}


	int GraphicComponent::heightForWidth(int width) const
	{
		return (int) std::round(width / ratio);
	}


	QSize GraphicComponent::sizeHint() const
	{
		int w = width();
		return {w, heightForWidth(w)};
	}


	void GraphicComponent::setBackgroundColor(const unsigned int r, const unsigned int g, const unsigned int b)
	{
		backgroundColor.setRgb(r, g, b);
	}


	void GraphicComponent::setBackgroundImage(QImage image)
	{
		backgroundImage = std::move(image);
	}


	void GraphicComponent::showEvent(QShowEvent *event)
	{
		QLabel::showEvent(event);
		redraw();
	}


	void GraphicComponent::resizeEvent(QResizeEvent *event)
	{
		QLabel::resizeEvent(event);
		redraw();
	}


	void GraphicComponent::draw(QPainter &painter)
	{
		// OVERWRITE IN CHILD CLASS
	}


	void GraphicComponent::redraw()
	{
		// Only draw when visible
		if (isEnabled() && isVisible()) {

			// Get size
			const int r = window()->devicePixelRatio();
			const int w = width() * r;
			const int h = height() * r;

			// Create new image and fill with background color
			QImage image(w, h, QImage::Format_ARGB32_Premultiplied);
			image.setDevicePixelRatio(r);
			QPainter painter;
			painter.begin(&image);
			painter.setRenderHint(QPainter::Antialiasing, false);
			painter.fillRect(0, 0, w, h, backgroundColor);

			// Draw background image (if needed)
			if (!backgroundImage.isNull()) {
				painter.drawImage(0, 0, backgroundImage);
			}

			// Draw content
			draw(painter);

			// Update label
			painter.end();
			setPixmap(getPixmap(image, window()->devicePixelRatio()));
		}
	}
}
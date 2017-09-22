#include "CurveComponent.h"


namespace Capture3
{

	CurveComponent::CurveComponent(
		const unsigned int width,
		const unsigned int height
	) :
		GraphicComponent(width, height),
		curve(nullptr),
		toggle("", this),

		// Colors
		colorBackground(COLOR_BACKGROUND),
		colorForeground(COLOR_FOREGROUND),
		colorLines(COLOR_LINES),
		gradientInput(),
		gradientOutput(),
		penCurve(COLOR_CONTENT),
		penLinear(Qt::white),

		// Zoom and move
		scale(1),
		offsetX(0),
		offsetY(0),
		mouseLeftDown(false),
		mouseRightDown(false),
		mousePosX(0),
		mousePosY(0),
		mouseDownX(0),
		mouseDownY(0),
		showDetails(false)
	{
		// Add toggle button
		toggle.setCheckable(true);
		toggle.setChecked(showDetails);

		// Link toggle button
		QObject::connect(&toggle, &QPushButton::clicked, this, [this]() {
			showDetails = !showDetails;
			redraw();
		});

		// Set thickness of the strokes
		penCurve.setWidth(2);
		penCurve.setCapStyle(Qt::RoundCap);
		penCurve.setJoinStyle(Qt::RoundJoin);
		penLinear.setWidth(2);
		penLinear.setCapStyle(Qt::RoundCap);
		penLinear.setJoinStyle(Qt::RoundJoin);

		// Set gradients
		gradientInput.setColorAt(0, Qt::black);
		gradientInput.setColorAt(1, Qt::white);
		gradientOutput.setColorAt(0, Qt::white);
		gradientOutput.setColorAt(1, Qt::black);

		// TODO: Add support for retina screens
	}


	CurveComponent::~CurveComponent()
	{
		QObject::disconnect(&toggle, nullptr, nullptr, nullptr);
		toggle.deleteLater();
		curve = nullptr;
	}


	void CurveComponent::mousePressEvent(QMouseEvent *event)
	{
		mouseLeftDown = (event->button() == Qt::LeftButton);
		mouseRightDown = (event->button() == Qt::RightButton);
		mouseDownX = mousePosX = event->x();
		mouseDownY = mousePosY = event->y();
		event->accept();
	}


	void CurveComponent::mouseReleaseEvent(QMouseEvent *event)
	{
		mouseLeftDown = false;
		mouseRightDown = false;
		event->accept();
	}


	void CurveComponent::mouseMoveEvent(QMouseEvent *event)
	{
		if (mouseLeftDown) {

			// Move camera
			offsetX -= (mousePosX - event->x());
			offsetY -= (mousePosY - event->y());
			redraw();

		} else if (mouseRightDown) {

			// Store previous image size
			const double w = width() - 10;
			const double h = height() - 10;
			const double originalW = w * scale;
			const double originalH = h * scale;

			// Get new scale
			scale += (mousePosY - event->y()) / (50.0 / scale);
			scale = scale < 1.0 ? 1.0 : scale;
			scale = scale > 10.0 ? 10.0 : scale;

			// Get zoom point
			const double px = (mouseDownX - offsetX - 10) / originalW;
			const double py = (mouseDownY - offsetY) / originalH;

			// Update offset
			offsetX += (originalW - (w * scale)) * px;
			offsetY += (originalH - (h * scale)) * py;
			redraw();
		}

		// Store mouse position
		mousePosX = event->x();
		mousePosY = event->y();
		event->accept();
	}


	void CurveComponent::wheelEvent(QWheelEvent *event)
	{
		event->ignore();
	}


	void CurveComponent::resizeEvent(QResizeEvent *event)
	{
		GraphicComponent::resizeEvent(event);

		// Position button in bottom right corner
		toggle.move(
			width() - toggle.width() - 2,
			height() - toggle.height() - 10
		);
	}


	void CurveComponent::show(const Curve &curve)
	{
		this->curve = &curve;
		redraw();
	}


	void CurveComponent::draw(QPainter &painter)
	{
		GraphicComponent::draw(painter);

		// Cap camera values
		const int w = width() - 8;
		const int h = height() - 8;
		const auto maxOffsetX = (int) std::lround(w - (w * scale));
		const auto maxOffsetY = (int) std::lround(h - (h * scale));
		offsetX = offsetX > 0 ? 0 : offsetX;
		offsetY = offsetY > 0 ? 0 : offsetY;
		offsetX = offsetX < maxOffsetX ? maxOffsetX : offsetX;
		offsetY = offsetY < maxOffsetY ? maxOffsetY : offsetY;

		// Create painter
		drawBackground(painter);

		// Smooth the curves
		painter.setRenderHint(QPainter::Antialiasing, true);

		// Fetch values for this curve
		if (curve != nullptr) {

			// Get models
			const CurveDataLinear &dataLinear = curve->getDataLinear();
			const CurveDataLowess &dataLowess = curve->getDataLowess();
			const CurveDataCubic &dataCubic = curve->getDataCubic();

			// Draw
			if (showDetails) {
				drawPoints(painter, curve->getPoints(), 3);
				drawLine(
					painter,
					dataLinear.getX1(),
					dataLinear.getY1(),
					dataLinear.getX2(),
					dataLinear.getY2(),
					penLinear
				);
				drawPoints(painter, dataLowess.getPointsX(), dataLowess.getPointsY(), 3, Qt::red);
				drawSpline(painter, dataCubic.getSpline(), 100, 2, Qt::red);
			} else {
				drawPoints(painter, curve->getPoints(), 3, QColor(60, 60, 60));
				drawSpline(painter, dataCubic.getSplineX(), dataCubic.getSplineY(), penCurve);
			}
		}
	}


	void CurveComponent::drawPoints(QPainter &painter, const std::vector<double> &pointsX, const std::vector<double> &pointsY, const double radius, const QColor &color)
	{
		for (unsigned int i = 0; i < pointsX.size(); i++) {
			painter.setPen(Qt::NoPen);
			painter.setBrush(color);
			painter.drawEllipse(QPointF(
				translateX(pointsY[i]),
				translateY(pointsX[i])
			), radius, radius);
		}
	}


	void CurveComponent::drawPoints(QPainter &painter, const std::vector<const CurvePoint *> &points, const double radius, const QColor &color)
	{
		for (auto point : points) {
			painter.setPen(Qt::NoPen);
			painter.setBrush(color);
			painter.drawEllipse(QPointF(
				translateX(point->getY()),
				translateY(point->getX())
			), radius, radius);
		}
	}


	void CurveComponent::drawPoints(QPainter &painter, const std::vector<const CurvePoint *> &points, const double radius)
	{
		for (auto point : points) {
			painter.setPen(Qt::NoPen);
			painter.setBrush(QColor(
				point->getPatch()->getRGB8()[0],
				point->getPatch()->getRGB8()[1],
				point->getPatch()->getRGB8()[2]
			));
			painter.drawEllipse(QPointF(
				translateX(point->getY()),
				translateY(point->getX())
			), radius, radius);
		}
	}


	void CurveComponent::drawSpline(QPainter &painter, const Spline &spline, const unsigned int steps, const double radius, const QColor &color)
	{
		for (unsigned int i = 0; i < steps; i++) {
			const double t = i / (double) (steps - 1);
			const double y = spline.at(t);
			painter.setBrush(color);
			painter.drawEllipse(QPointF(
				translateX(y),
				translateY(t)
			), radius, radius);
		}
	}


	void CurveComponent::drawSpline(QPainter &painter, const std::vector<double> &splineX, const std::vector<double> &splineY, const QPen &pen)
	{
		QPainterPath path;
		path.moveTo(
			translateX(splineY.front()),
			translateY(splineX.front())
		);

		for (unsigned int i = 1; i < splineX.size(); i++) {
			path.lineTo(
				translateX(splineY[i]),
				translateY(splineX[i])
			);
		}

		painter.setBrush(Qt::NoBrush);
		painter.setPen(pen);
		painter.drawPath(path);
	}


	void CurveComponent::drawLine(QPainter &painter, const double x1, const double y1, const double x2, const double y2, const QPen &pen)
	{
		painter.setBrush(Qt::NoBrush);
		painter.setPen(pen);
		painter.drawLine(
			QPoint((int) std::lround(translateX(y1)), (int) std::lround(translateY(x1))),
			QPoint((int) std::lround(translateX(y2)), (int) std::lround(translateY(x2)))
		);
	}


	void CurveComponent::drawBackground(QPainter &painter)
	{
		// Get size
		const int w = width();
		const int h = height();
		const int w2 = w - 5;
		const int h2 = h - 5;
		const int w3 = w - 8;
		const int h3 = h - 8;

		// Draw background
		painter.fillRect(0, 0, w, h, colorBackground);
		painter.fillRect(8, 0, w3, h3, colorForeground);

		// Draw gradients
		gradientInput.setStart(offsetX + 5, 0);
		gradientInput.setFinalStop(w2 * scale + offsetX + 5, 0);
		gradientOutput.setStart(0, offsetY);
		gradientOutput.setFinalStop(0, h2 * scale + offsetY);
		painter.fillRect(5, h2, w2, 5, gradientInput);
		painter.fillRect(0, 0, 5, h2, gradientOutput);

		// Draw lines
		painter.setClipRect(8, 0, w3, h3);
		painter.fillRect(QRect(8, (int) std::lround(translateY(0.25)), w3, 1), colorLines);
		painter.fillRect(QRect(8, (int) std::lround(translateY(0.50)), w3, 1), colorLines);
		painter.fillRect(QRect(8, (int) std::lround(translateY(0.75)), w3, 1), colorLines);
		painter.fillRect(QRect((int) std::lround(translateX(0.25)), 0, 1, h3), colorLines);
		painter.fillRect(QRect((int) std::lround(translateX(0.50)), 0, 1, h3), colorLines);
		painter.fillRect(QRect((int) std::lround(translateX(0.75)), 0, 1, h3), colorLines);
		painter.setPen(colorLines);
		painter.drawLine(
			(int) std::lround(translateX(0)),
			(int) std::lround(translateY(0)),
			(int) std::lround(translateX(1)),
			(int) std::lround(translateY(1))
		);
	}


	const double CurveComponent::translateX(const double x)
	{
		return (((width() - 8) * scale * x) + offsetX + 8);
	}


	const double CurveComponent::translateY(const double y)
	{
		return (((height() - 8) * scale * (1.0 - y)) + offsetY);
	}


	void CurveComponent::reset()
	{
		curve = nullptr;
		redraw();
	}

}
#ifndef CAPTURE3_CURVE_COMPONENT_H
#define CAPTURE3_CURVE_COMPONENT_H


#include <vector>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtGui/QPixmap>
#include <QtGui/QPainter>
#include <QtGui/QPainterPath>
#include <QtGui/QColor>
#include <QtGui/QLinearGradient>
#include <QtGui/QResizeEvent>
#include <QtGui/QMouseEvent>
#include <QtGui/QWheelEvent>
#include <QtGui/QMatrix4x4>


#include "../graphic/GraphicComponent.h"
#include "../../../engine/objects/curve/Curve.h"
#include "../../../engine/objects/curve/CurveDataLinear.h"
#include "../../../engine/objects/curve/CurveDataLowess.h"
#include "../../../engine/objects/curve/CurveDataCubic.h"
#include "../../../engine/objects/curve/CurvePoint.h"
#include "../../../engine/objects/spline/Spline.h"
#include "../../../engine/objects/colorChart/ColorChartPatch.h"
#include "../../../constants/ColorConstants.h"


namespace Capture3
{
	class CurveComponent : public GraphicComponent
	{
		Q_OBJECT

		public:
			CurveComponent(
				const unsigned int width,
				const unsigned int height
			);

			virtual ~CurveComponent();

			void show(const Curve &curve);

			void reset();

		protected:
			virtual void mousePressEvent(QMouseEvent *event);

			virtual void mouseReleaseEvent(QMouseEvent *event);

			virtual void mouseMoveEvent(QMouseEvent *event);

			virtual void wheelEvent(QWheelEvent *event);

			virtual void resizeEvent(QResizeEvent *event);

			virtual void draw(QPainter &painter);

		private:
			void drawPoints(QPainter &painter, const std::vector<double> &pointsX, const std::vector<double> &pointsY, const double radius, const QColor &color);

			void drawPoints(QPainter &painter, const std::vector<const CurvePoint *> &points, const double radius, const QColor &color);

			void drawPoints(QPainter &painter, const std::vector<const CurvePoint *> &points, const double radius);

			void drawSpline(QPainter &painter, const Spline &spline, const unsigned int steps, const double radius, const QColor &color);

			void drawSpline(QPainter &painter, const std::vector<double> &splineX, const std::vector<double> &splineY, const QPen &pen);

			void drawLine(QPainter &painter, const double x1, const double y1, const double x2, const double y2, const QPen &pen);

			void drawBackground(QPainter &painter);

			const double translateX(const double x);

			const double translateY(const double y);

			const Curve *curve;
			QPushButton toggle;
			const QColor colorBackground;
			const QColor colorForeground;
			const QColor colorLines;
			QLinearGradient gradientInput;
			QLinearGradient gradientOutput;
			QPen penCurve;
			QPen penLinear;
			double scale;
			double offsetX;
			double offsetY;
			bool mouseLeftDown;
			bool mouseRightDown;
			int mousePosX;
			int mousePosY;
			int mouseDownX;
			int mouseDownY;
			bool showDetails;
	};
}


#endif // CAPTURE3_CURVE_COMPONENT_H

#ifndef CAPTURE3_GRAPHIC_COMPONENT_H
#define CAPTURE3_GRAPHIC_COMPONENT_H


#include <cmath>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLayout>
#include <QtGui/QPixmap>
#include <QtGui/QImage>
#include <QtGui/QPainter>
#include <QtGui/QShowEvent>
#include <QtGui/QResizeEvent>
#include <QtGui/QColor>


#include "../../../constants/ColorConstants.h"
#include "../../../utils/PixmapUtils.h"


namespace Capture3
{
	class GraphicComponent : public QLabel
	{
		Q_OBJECT

		public:
			GraphicComponent(
				const unsigned int width,
				const unsigned int height
			);

			virtual ~GraphicComponent();

			virtual int heightForWidth(int width) const;

			virtual QSize sizeHint() const;

			void setBackgroundColor(const unsigned int r, const unsigned int g, const unsigned int b);

			void setBackgroundImage(QImage image);

			void redraw();

		protected:
			virtual void draw(QPainter &painter);

			virtual void showEvent(QShowEvent *event);

			virtual void resizeEvent(QResizeEvent *event);

		private:
			const double ratio;
			QColor backgroundColor;
			QImage backgroundImage;
	};
}


#endif // CAPTURE3_GRAPHIC_COMPONENT_H

#ifndef CAPTURE3_IMAGE_HISTOGRAM_COMPONENT_ITEM_H
#define CAPTURE3_IMAGE_HISTOGRAM_COMPONENT_ITEM_H


#include <QtWidgets/QWidget>
#include <QtGui/QImage>
#include <QtGui/QPainter>
#include <QtGui/QColor>
#include <QtGui/QLinearGradient>


#include "../graphic/GraphicComponent.h"
#include "../../../constants/ColorConstants.h"
#include "../../../engine/objects/image/ImageChannel.h"


namespace Capture3
{
	class ImageHistogramComponentItem final : public GraphicComponent
	{
		Q_OBJECT

		public:
			ImageHistogramComponentItem();

			virtual ~ImageHistogramComponentItem();

			void reset();

			QImage &getImage();

		protected:
			virtual void draw(QPainter &painter);

		private:
			const QColor colorBackground;
			const QColor colorForeground;
			QLinearGradient gradient;
			QImage image;
	};
}


#endif // CAPTURE3_IMAGE_HISTOGRAM_COMPONENT_ITEM_H

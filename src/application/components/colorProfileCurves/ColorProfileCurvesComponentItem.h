#ifndef CAPTURE3_COLOR_PROFILE_CURVES_COMPONENT_ITEM_H
#define CAPTURE3_COLOR_PROFILE_CURVES_COMPONENT_ITEM_H


#include <QtWidgets/QWidget>
#include <QtGui/QPainter>
#include <QtGui/QColor>


#include "../curve/CurveComponent.h"


namespace Capture3
{
	class ColorProfileCurvesComponentItem final : public CurveComponent
	{
		Q_OBJECT

		public:
			ColorProfileCurvesComponentItem();

			virtual ~ColorProfileCurvesComponentItem();

		protected:
			virtual void draw(QPainter &painter);

	};
}


#endif // CAPTURE3_COLOR_PROFILE_CURVES_COMPONENT_ITEM_H

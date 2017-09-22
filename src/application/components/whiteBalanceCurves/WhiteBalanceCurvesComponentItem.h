#ifndef CAPTURE3_WHITE_BALANCE_CURVES_COMPONENT_ITEM_H
#define CAPTURE3_WHITE_BALANCE_CURVES_COMPONENT_ITEM_H


#include <QtWidgets/QWidget>
#include <QtGui/QPainter>
#include <QtGui/QColor>


#include "../curve/CurveComponent.h"


namespace Capture3
{
	class WhiteBalanceCurvesComponentItem final : public CurveComponent
	{
		Q_OBJECT

		public:
			WhiteBalanceCurvesComponentItem();

			virtual ~WhiteBalanceCurvesComponentItem();

		protected:
			virtual void draw(QPainter &painter);
	};
}


#endif // CAPTURE3_WHITE_BALANCE_CURVES_COMPONENT_ITEM_H

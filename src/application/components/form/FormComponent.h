#ifndef CAPTURE3_FORM_COMPONENT_H
#define CAPTURE3_FORM_COMPONENT_H


#include <QtWidgets/QWidget>


#include "../panelTab/PanelTabComponent.h"


namespace Capture3
{
	class FormComponent : public PanelTabComponent
	{
		Q_OBJECT

		public:
			FormComponent();

			virtual ~FormComponent();
	};
}


#endif // CAPTURE3_TABLE_COMPONENT_H

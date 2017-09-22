#ifndef CAPTURE3_WELCOME_COMPONENT_H
#define CAPTURE3_WELCOME_COMPONENT_H


#include <QtWidgets/QWidget>


#include "../panelTab/PanelTabComponent.h"


namespace Capture3
{
	class WelcomeComponent final : public PanelTabComponent
	{
		Q_OBJECT

		public:
			WelcomeComponent();

			virtual ~WelcomeComponent();

	};
}


#endif // CAPTURE3_WELCOME_COMPONENT_H

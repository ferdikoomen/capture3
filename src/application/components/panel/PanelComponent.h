#ifndef CAPTURE3_PANEL_COMPONENT_H
#define CAPTURE3_PANEL_COMPONENT_H


#include <QtWidgets/QWidget>
#include <QtWidgets/QFrame>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>


#include "../panelTabs/PanelTabsComponent.h"


namespace Capture3
{
	class PanelComponent : public QFrame
	{
		Q_OBJECT

		public:
			PanelComponent();

			virtual ~PanelComponent();

			void addTabs(PanelTabsComponent *tabs);

			void setStretchFactor(const int index, const int stretch);

		private slots:

			void toggle();

		private:
			QVBoxLayout layout;
			QPushButton button;
			QSplitter content;
			int contentMinimumWidth;
			int contentMinimumHeight;
			int panelMinimumWidth;
			int panelMaximumWidth;
			bool open;

	};
}


#endif // CAPTURE3_PANEL_COMPONENT_H

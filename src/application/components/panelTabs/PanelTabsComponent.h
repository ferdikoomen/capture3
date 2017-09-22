#ifndef CAPTURE3_PANEL_TABS_COMPONENT_H
#define CAPTURE3_PANEL_TABS_COMPONENT_H


#include <QtWidgets/QWidget>
#include <QtWidgets/QFrame>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTabBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QMenu>
#include <QtWidgets/QAction>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStyle>
#include <QtGui/QResizeEvent>
#include <QtGui/QFocusEvent>
#include <QtCore/QEvent>


#include "../panelTab/PanelTabComponent.h"


namespace Capture3
{
	class PanelTabsComponent : public QFrame
	{
		Q_OBJECT

		public:
			PanelTabsComponent();

			virtual ~PanelTabsComponent();

			void addTab(PanelTabComponent *tab);

		protected:
			virtual void resizeEvent(QResizeEvent *event);

			virtual void focusInEvent(QFocusEvent *event);

			virtual void focusOutEvent(QFocusEvent *event);

		private slots:

			void focusIn();

			void focusOut();

			void showMenu();

		private:
			bool eventFilter(QObject *watcher, QEvent *event);

			QVBoxLayout layout;
			QTabWidget tabs;
			QMenu menu;
			QAction action1;
			QAction action2;
			QAction action3;
			QAction action4;
			QPushButton button;
			bool open;

	};
}


#endif // CAPTURE3_PANEL_TABS_COMPONENT_H

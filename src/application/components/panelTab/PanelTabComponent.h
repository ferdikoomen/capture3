#ifndef CAPTURE3_PANEL_TAB_COMPONENT_H
#define CAPTURE3_PANEL_TAB_COMPONENT_H


#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtGui/QWheelEvent>
#include <QtCore/QEvent>


#include "../panelGroup/PanelGroupComponent.h"


namespace Capture3
{
	class PanelTabComponent : public QScrollArea
	{
		Q_OBJECT

		public:
			PanelTabComponent(const QString &name);

			virtual ~PanelTabComponent();

			const QString getName() const;

			void setSpacing(const int value);

			void setMargin(const int value);

			void setMargins(const int left, const int top, const int right, const int bottom);

			void setRowStretch(const int row, const int stretch);

			void setColumnStretch(const int column, const int stretch);

			void setRowMinimumHeight(const int row, const int height);

			void setColumnMinimumWidth(const int column, const int width);

			void addWidget(QWidget *item);

			void addWidget(QWidget *item, const int row, const int col);

			void addWidget(QWidget *item, const int row, const int col, const int rowSpan, const int colSpan);

			void addLayout(QLayout *item, const int row, const int col);

			void addLayout(QLayout *item, const int row, const int col, const int rowSpan, const int colSpan);

			void removeWidget(QWidget *item);

		signals:

			void onFocusIn();

			void onFocusOut();

		protected:
			virtual void wheelEvent(QWheelEvent *event);

		private:
			bool eventFilter(QObject *watched, QEvent *event);

			QString name;
			QWidget container;
			QGridLayout layout;
	};
}

#endif // CAPTURE3_PANEL_TAB_COMPONENT_H

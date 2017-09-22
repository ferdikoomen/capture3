#ifndef CAPTURE3_PANEL_GROUP_COMPONENT_H
#define CAPTURE3_PANEL_GROUP_COMPONENT_H


#include <QtWidgets/QWidget>
#include <QtWidgets/QFrame>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtCore/QEvent>


namespace Capture3
{
	class PanelGroupComponent : public QFrame
	{
		Q_OBJECT

		public:
			PanelGroupComponent(const QString &name);

			virtual ~PanelGroupComponent();

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

		private slots:

			void toggle();

		private:
			bool eventFilter(QObject *watched, QEvent *event);

			const QString labelOpen;
			const QString labelClose;
			QVBoxLayout layout;
			QPushButton button;
			QFrame content;
			QGridLayout contentLayout;
			bool open;

	};
}


#endif // CAPTURE3_PANEL_GROUP_COMPONENT_H

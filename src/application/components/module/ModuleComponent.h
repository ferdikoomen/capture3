#ifndef CAPTURE3_MODULE_COMPONENT_H
#define CAPTURE3_MODULE_COMPONENT_H


#include <QtWidgets/QWidget>
#include <QtWidgets/QSplitter>


#include "../panel/PanelComponent.h"
#include "../panelTabs/PanelTabsComponent.h"
#include "../panelTab/PanelTabComponent.h"


namespace Capture3
{
	class ModuleComponent : public QScrollArea
	{
		Q_OBJECT

		public:
			ModuleComponent(const QString &name);

			virtual ~ModuleComponent();

			void addWidget(QWidget *item);

			void setStretchFactor(const int index, const int stretch);

			const QString getName() const;

		private:
			const QString name;
			QSplitter container;


	};
}


#endif // CAPTURE3_MODULE_COMPONENT_H

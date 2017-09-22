#ifndef CAPTURE3_WINDOW_COMPONENT_H
#define CAPTURE3_WINDOW_COMPONENT_H


#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTabBar>


#include "../module/ModuleComponent.h"


namespace Capture3
{
	class WindowComponent final : public QMainWindow
	{
		Q_OBJECT

		public:
			WindowComponent();

			virtual ~WindowComponent();

			void add(ModuleComponent *module);

		private:
			QTabWidget tabs;

	};
}


#endif // CAPTURE3_WINDOW_COMPONENT_H

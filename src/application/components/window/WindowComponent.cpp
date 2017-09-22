#include "WindowComponent.h"


namespace Capture3
{

	WindowComponent::WindowComponent() :
		QMainWindow(),
		tabs()
	{
		// Set tabs to bottom
		tabs.setTabPosition(QTabWidget::South);
		setCentralWidget(&tabs);
	}


	WindowComponent::~WindowComponent()
	{
		tabs.deleteLater();
	}


	void WindowComponent::add(ModuleComponent *module)
	{
		tabs.addTab(module, module->getName());
	}

}
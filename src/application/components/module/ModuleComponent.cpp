#include "ModuleComponent.h"


namespace Capture3
{

	ModuleComponent::ModuleComponent(const QString &name) :
		QScrollArea(),
		container(Qt::Horizontal),
		name(name)
	{
		// Don't allow splitter items to collapse
		container.setChildrenCollapsible(false);

		// Add container and make sure the scroll area can resize
		setWidget(&container);
		setWidgetResizable(true);
		setFocusPolicy(Qt::NoFocus);

		// Don't show scrollbars
		setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	}


	ModuleComponent::~ModuleComponent()
	{
		container.deleteLater();
	}


	void ModuleComponent::addWidget(QWidget *item)
	{
		container.addWidget(item);
	}


	void ModuleComponent::setStretchFactor(const int index, const int stretch)
	{
		container.setStretchFactor(index, stretch);
	}


	const QString ModuleComponent::getName() const
	{
		return name;
	}
}
#include "PanelComponent.h"


namespace Capture3
{

	PanelComponent::PanelComponent() :
		QFrame(),
		layout(),
		button("●"),
		content(Qt::Vertical),
		contentMinimumWidth(0),
		contentMinimumHeight(0),
		panelMinimumWidth(0),
		panelMaximumWidth(0),
		open(true)
	{
		// Don't allow splitter items to collapse
		content.setChildrenCollapsible(false);
		content.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

		// Add items
		layout.setSpacing(0);
		layout.setMargin(0);
		layout.setContentsMargins(0, 0, 0, 0);
		layout.setAlignment(Qt::AlignTop | Qt::AlignLeft);
		layout.addWidget(&button);
		layout.addWidget(&content);
		setLayout(&layout);

		// Show toggle button on top
		button.setObjectName("toggle");
		button.raise();

		// Link events
		QObject::connect(&button, &QPushButton::clicked, this, &PanelComponent::toggle);
	}


	PanelComponent::~PanelComponent()
	{
		QObject::disconnect(&button, nullptr, nullptr, nullptr);

		content.deleteLater();
		button.deleteLater();
		layout.deleteLater();
	}


	void PanelComponent::addTabs(PanelTabsComponent *tabs)
	{
		content.addWidget(tabs);
	}


	void PanelComponent::setStretchFactor(const int index, const int stretch)
	{
		content.setStretchFactor(index, stretch);
	}


	void PanelComponent::toggle()
	{
		if (open) {
			open = false;
			button.setText("▸");
			panelMinimumWidth = minimumWidth();
			panelMaximumWidth = maximumWidth();
			contentMinimumWidth = content.minimumWidth();
			contentMinimumHeight = content.minimumHeight();
			content.setEnabled(false);
			content.setMinimumWidth(0);
			content.setMinimumHeight(0);
			setMinimumWidth(button.minimumWidth());
			setMaximumWidth(button.minimumWidth());
		} else {
			open = true;
			button.setText("●");
			content.setMinimumWidth(contentMinimumWidth);
			content.setMinimumHeight(contentMinimumHeight);
			content.setEnabled(true);
			setMinimumWidth(panelMinimumWidth);
			setMaximumWidth(panelMaximumWidth);
		}
	}

}

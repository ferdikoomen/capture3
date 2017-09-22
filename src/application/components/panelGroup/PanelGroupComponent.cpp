#include "PanelGroupComponent.h"


namespace Capture3
{

	PanelGroupComponent::PanelGroupComponent(const QString &name) :
		QFrame(),
		layout(),
		labelOpen("▾ " + name),
		labelClose("▸ " + name),
		button(labelOpen),
		content(),
		contentLayout(),
		open(true)
	{
		// Set layout to expand (horizontally)
		contentLayout.setSpacing(3);
		contentLayout.setMargin(0);
		contentLayout.setContentsMargins(0, 0, 0, 0);
		contentLayout.setAlignment(Qt::AlignTop | Qt::AlignLeft);
		content.setLayout(&contentLayout);
		content.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

		// Add items
		layout.setSpacing(0);
		layout.setMargin(0);
		layout.setContentsMargins(0, 0, 0, 0);
		layout.setAlignment(Qt::AlignTop | Qt::AlignLeft);
		layout.addWidget(&button);
		layout.addWidget(&content);
		setLayout(&layout);
		setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

		// Show toggle button on top
		button.raise();
		button.setObjectName("toggle");
		button.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

		// Link events
		QObject::connect(&button, &QPushButton::clicked, this, &PanelGroupComponent::toggle);
	}


	PanelGroupComponent::~PanelGroupComponent()
	{
		QObject::disconnect(&button, nullptr, nullptr, nullptr);

		contentLayout.deleteLater();
		content.deleteLater();
		button.deleteLater();
		layout.deleteLater();
	}


	void PanelGroupComponent::setSpacing(const int value)
	{
		contentLayout.setSpacing(value);
	}


	void PanelGroupComponent::setMargin(const int value)
	{
		contentLayout.setMargin(value);
	}


	void PanelGroupComponent::setMargins(const int left, const int top, const int right, const int bottom)
	{
		contentLayout.setContentsMargins(left, top, right, bottom);
	}


	void PanelGroupComponent::setRowStretch(const int row, const int stretch)
	{
		contentLayout.setRowStretch(row, stretch);
	}


	void PanelGroupComponent::setColumnStretch(const int column, const int stretch)
	{
		contentLayout.setColumnStretch(column, stretch);
	}


	void PanelGroupComponent::setRowMinimumHeight(const int row, const int height)
	{
		contentLayout.setRowMinimumHeight(row, height);
	}


	void PanelGroupComponent::setColumnMinimumWidth(const int column, const int width)
	{
		contentLayout.setColumnMinimumWidth(column, width);
	}


	void PanelGroupComponent::addWidget(QWidget *item)
	{
		item->installEventFilter(this);
		contentLayout.addWidget(item);
	}


	void PanelGroupComponent::addWidget(QWidget *item, const int row, const int col)
	{
		item->installEventFilter(this);
		contentLayout.addWidget(item, row, col);
	}


	void PanelGroupComponent::addWidget(QWidget *item, const int row, const int col, const int rowSpan, const int colSpan)
	{
		item->installEventFilter(this);
		contentLayout.addWidget(item, row, col, rowSpan, colSpan);
	}


	void PanelGroupComponent::addLayout(QLayout *item, const int row, const int col)
	{
		for (unsigned int i = 0; i < item->count(); i++) {
			QWidget *widget = item->itemAt(i)->widget();
			if (widget != nullptr) {
				widget->installEventFilter(this);
			}
		}
		contentLayout.addLayout(item, row, col, Qt::AlignTop | Qt::AlignLeft);
	}


	void PanelGroupComponent::addLayout(QLayout *item, const int row, const int col, const int rowSpan, const int colSpan)
	{
		for (unsigned int i = 0; i < item->count(); i++) {
			QWidget *widget = item->itemAt(i)->widget();
			if (widget != nullptr) {
				widget->installEventFilter(this);
			}
		}
		contentLayout.addLayout(item, row, col, rowSpan, colSpan, Qt::AlignTop | Qt::AlignLeft);
	}


	void PanelGroupComponent::removeWidget(QWidget *item)
	{
		item->removeEventFilter(this);
		contentLayout.removeWidget(item);
	}


	bool PanelGroupComponent::eventFilter(QObject *watched, QEvent *event)
	{
		// Trigger signals if children get focus
		if (event->type() == QEvent::FocusIn) {
			emit onFocusIn();
		}
		if (event->type() == QEvent::FocusOut) {
			emit onFocusOut();
		}

		return QWidget::eventFilter(watched, event);
	}


	void PanelGroupComponent::toggle()
	{
		if (open) {
			open = false;
			button.setText(labelClose);
			content.hide();
		} else {
			open = true;
			button.setText(labelOpen);
			content.show();
		}
	}

}
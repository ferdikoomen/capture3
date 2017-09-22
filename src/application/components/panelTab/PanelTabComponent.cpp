#include "PanelTabComponent.h"


namespace Capture3
{

	PanelTabComponent::PanelTabComponent(const QString &name) :
		QScrollArea(),
		name(name),
		container(),
		layout()
	{
		// Set layout
		layout.setSpacing(3);
		layout.setMargin(0);
		layout.setContentsMargins(0, 0, 0, 0);
		layout.setAlignment(Qt::AlignTop | Qt::AlignLeft);

		// Add container
		container.setLayout(&layout);
		container.setObjectName("content");

		// Make sure the scroll area can resize
		setWidget(&container);
		setWidgetResizable(true);
		setFocusPolicy(Qt::NoFocus);

		// Don't show scroll bars
		setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	}


	PanelTabComponent::~PanelTabComponent()
	{
		container.deleteLater();
		layout.deleteLater();
	}


	const QString PanelTabComponent::getName() const
	{
		return name;
	}


	void PanelTabComponent::setSpacing(const int value)
	{
		layout.setSpacing(value);
	}


	void PanelTabComponent::setMargin(const int value)
	{
		layout.setMargin(value);
	}


	void PanelTabComponent::setMargins(const int left, const int top, const int right, const int bottom)
	{
		layout.setContentsMargins(left, top, right, bottom);
	}


	void PanelTabComponent::setRowStretch(const int row, const int stretch)
	{
		layout.setRowStretch(row, stretch);
	}


	void PanelTabComponent::setColumnStretch(const int column, const int stretch)
	{
		layout.setColumnStretch(column, stretch);
	}


	void PanelTabComponent::setRowMinimumHeight(const int row, const int height)
	{
		layout.setRowMinimumHeight(row, height);
	}


	void PanelTabComponent::setColumnMinimumWidth(const int column, const int width)
	{
		layout.setColumnMinimumWidth(column, width);
	}


	void PanelTabComponent::addWidget(QWidget *item)
	{
		item->installEventFilter(this);
		layout.addWidget(item);
	}


	void PanelTabComponent::addWidget(QWidget *item, const int row, const int col)
	{
		item->installEventFilter(this);
		layout.addWidget(item, row, col);
	}


	void PanelTabComponent::addWidget(QWidget *item, const int row, const int col, const int rowSpan, const int colSpan)
	{
		item->installEventFilter(this);
		layout.addWidget(item, row, col, rowSpan, colSpan);
	}


	void PanelTabComponent::addLayout(QLayout *item, const int row, const int col)
	{
		for (unsigned int i = 0; i < item->count(); i++) {
			QWidget *widget = item->itemAt(i)->widget();
			if (widget != nullptr) {
				widget->installEventFilter(this);
			}
		}
		layout.addLayout(item, row, col, Qt::AlignTop | Qt::AlignLeft);
	}


	void PanelTabComponent::addLayout(QLayout *item, const int row, const int col, const int rowSpan, const int colSpan)
	{
		for (unsigned int i = 0; i < item->count(); i++) {
			QWidget *widget = item->itemAt(i)->widget();
			if (widget != nullptr) {
				widget->installEventFilter(this);
			}
		}
		layout.addLayout(item, row, col, rowSpan, colSpan, Qt::AlignTop | Qt::AlignLeft);
	}


	void PanelTabComponent::removeWidget(QWidget *item)
	{
		item->removeEventFilter(this);
		layout.removeWidget(item);
	}


	void PanelTabComponent::wheelEvent(QWheelEvent *event)
	{
		QScrollArea::wheelEvent(event);
	}


	bool PanelTabComponent::eventFilter(QObject *watched, QEvent *event)
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
}

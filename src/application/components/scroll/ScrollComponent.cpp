#include "ScrollComponent.h"


namespace Capture3
{

	ScrollComponent::ScrollComponent() :
		QScrollArea(),
		container(),
		layout()
	{
		// Add items
		layout.setSpacing(3);
		layout.setMargin(0);
		layout.setContentsMargins(0, 0, 0, 0);
		layout.setAlignment(Qt::AlignTop | Qt::AlignLeft);
		container.setLayout(&layout);
		container.setObjectName("content");

		// Make sure the scroll area can resize
		setWidget(&container);
		setWidgetResizable(true);
		setFocusPolicy(Qt::NoFocus);

		// Hide scroll bars
		setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	}


	ScrollComponent::~ScrollComponent()
	{
		container.deleteLater();
		layout.deleteLater();
	}


	void ScrollComponent::setSpacing(const int value)
	{
		layout.setSpacing(value);
	}


	void ScrollComponent::setMargin(const int value)
	{
		layout.setMargin(value);
	}


	void ScrollComponent::setMargins(const int left, const int top, const int right, const int bottom)
	{
		layout.setContentsMargins(left, top, right, bottom);
	}


	void ScrollComponent::setRowStretch(const int row, const int stretch)
	{
		layout.setRowStretch(row, stretch);
	}


	void ScrollComponent::setColumnStretch(const int column, const int stretch)
	{
		layout.setColumnStretch(column, stretch);
	}


	void ScrollComponent::setRowMinimumHeight(const int row, const int height)
	{
		layout.setRowMinimumHeight(row, height);
	}


	void ScrollComponent::setColumnMinimumWidth(const int column, const int width)
	{
		layout.setColumnMinimumWidth(column, width);
	}


	void ScrollComponent::addWidget(QWidget *item)
	{
		layout.addWidget(item);
	}


	void ScrollComponent::addWidget(QWidget *item, const int row, const int col)
	{
		layout.addWidget(item, row, col);
	}


	void ScrollComponent::addWidget(QWidget *item, const int row, const int col, const int rowSpan, const int colSpan)
	{
		layout.addWidget(item, row, col, rowSpan, colSpan);
	}


	void ScrollComponent::addLayout(QLayout *item, const int row, const int col)
	{
		layout.addLayout(item, row, col, Qt::AlignTop | Qt::AlignLeft);
	}


	void ScrollComponent::addLayout(QLayout *item, const int row, const int col, const int rowSpan, const int colSpan)
	{
		layout.addLayout(item, row, col, rowSpan, colSpan, Qt::AlignTop | Qt::AlignLeft);
	}


	void ScrollComponent::removeWidget(QWidget *item)
	{
		layout.removeWidget(item);
	}
}

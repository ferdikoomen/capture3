#include "TableComponent.h"


namespace Capture3
{

	TableComponent::TableComponent(const unsigned int rows, const unsigned int columns) :
		QTableWidget(rows, columns)
	{
		// Default row and column options
		verticalHeader()->hide();
		verticalHeader()->setDefaultSectionSize(18);
		verticalHeader()->setDefaultAlignment(Qt::AlignLeft);
		verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
		horizontalHeader()->setDefaultSectionSize(50);
		horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
		horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
		setShowGrid(false);

		// Enable scrollbars when needed
		setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

		// Do not allow selection
		setSelectionMode(QAbstractItemView::NoSelection);

		// Don't allow focus
		setFocusPolicy(Qt::NoFocus);
	}


	TableComponent::~TableComponent()
	{
		//
	}


	void TableComponent::setHorizontalHeader(const unsigned int index, const QString &label)
	{
		setHorizontalHeaderItem(index, new QTableWidgetItem(label));
	}


	void TableComponent::setVerticalHeader(const unsigned int index, const QString &label)
	{
		setVerticalHeaderItem(index, new QTableWidgetItem(label));
	}


	void TableComponent::addItem(const unsigned int row, const unsigned int column, const double value, const int precision)
	{
		setItem(row, column, new QTableWidgetItem(QString::number(value, 'f', precision)));
	}


	void TableComponent::addItem(const unsigned int row, const unsigned int column, const int value)
	{
		setItem(row, column, new QTableWidgetItem(QString::number(value)));
	}


	void TableComponent::addItem(const unsigned int row, const unsigned int column, const unsigned int value)
	{
		setItem(row, column, new QTableWidgetItem(QString::number(value)));
	}


	void TableComponent::addItem(const unsigned int row, const unsigned int column, const QString &label)
	{
		setItem(row, column, new QTableWidgetItem(label));
	}


	void TableComponent::addItem(const unsigned int row, const unsigned int column, const QPixmap &pixmap, const QString &label)
	{
		setItem(row, column, new QTableWidgetItem(QIcon(pixmap), label));
	}


	void TableComponent::addItem(const unsigned int row, const unsigned int column, const bool value)
	{
		auto *item = new QTableWidgetItem(value ? "✓" : "✕");
		item->setTextColor(
			value ?
			COLOR_GREEN :
			COLOR_RED
		);
		setItem(row, column, item);
	}


	void TableComponent::addLabel(const unsigned int row, const unsigned int column, const QString &label)
	{
		setCellWidget(row, column, new QLabel(label));
	}


	QLabel *TableComponent::getLabel(const unsigned int row, const unsigned int column)
	{
		return (QLabel *) cellWidget(row, column);
	}
}
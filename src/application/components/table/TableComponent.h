#ifndef CAPTURE3_TABLE_COMPONENT_H
#define CAPTURE3_TABLE_COMPONENT_H


#include <QtWidgets/QWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTableWidgetItem>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtGui/QIcon>
#include <QtGui/QPixmap>


#include "../../../constants/ColorConstants.h"


namespace Capture3
{
	class TableComponent final : public QTableWidget
	{
		Q_OBJECT

		public:
			TableComponent(const unsigned int rows = 0, const unsigned int columns = 0);

			virtual ~TableComponent();

			void setHorizontalHeader(const unsigned int index, const QString &label);

			void setVerticalHeader(const unsigned int index, const QString &label);

			void addItem(const unsigned int row, const unsigned int column, const double value, const int precision = 2);

			void addItem(const unsigned int row, const unsigned int column, const int value);

			void addItem(const unsigned int row, const unsigned int column, const unsigned int value);

			void addItem(const unsigned int row, const unsigned int column, const QString &label);

			void addItem(const unsigned int row, const unsigned int column, const QPixmap &pixmap, const QString &label);

			void addItem(const unsigned int row, const unsigned int column, const bool value);

			void addLabel(const unsigned int row, const unsigned int column, const QString &label);

			QLabel *getLabel(const unsigned int row, const unsigned int column);

		private:
	};
}


#endif // CAPTURE3_TABLE_COMPONENT_H

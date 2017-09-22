#ifndef CAPTURE3_PROJECT_H
#define CAPTURE3_PROJECT_H


#include <vector>
#include <QtCore/QObject>
#include <QtCore/QFileInfo>
#include <QtCore/QFile>
#include <QtCore/QDir>
#include <QtCore/QStandardPaths>
#include <QtCore/QVector>
#include <QtCore/QMap>
#include <QtCore/QVariant>
#include <QtSql/QtSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QtWidgets/QFileDialog>


#include "../image/Image.h"
#include "../../../utils/FileUtils.h"
#include "../../../constants/ApplicationConstants.h"


namespace Capture3
{

	class Project final : public QObject
	{
		Q_OBJECT

		public:
			Project();

			virtual ~Project();

			const QFileInfo getNextFileRaw();

			const QFileInfo getNextFileImage();

			void open(const QString &path);

			void select();

			void add(Image *image);

			void remove(const Image *image);

		private:
			unsigned int countRaw;
			unsigned int countImage;
			QFileInfo nextFileRaw;
			QFileInfo nextFileImage;
			QSqlDatabase database;
			QSqlQuery databaseQuery;
			std::vector<const Image *> images;
	};
}

#endif // CAPTURE3_PROJECT_H

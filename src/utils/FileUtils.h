#ifndef CAPTURE3_FILE_UTILS_H
#define CAPTURE3_FILE_UTILS_H


#include <QtCore/QString>
#include <QtCore/QFile>


namespace Capture3
{

	static void readBytes(double *data, const unsigned int bytes, const QString &path)
	{
		QFile file(path);
		file.open(QIODevice::ReadOnly);
		file.read((char *) data, bytes * sizeof(double));
		file.close();
	}


	static void writeBytes(const double *data, const unsigned int bytes, const QString &path)
	{
		QFile file(path);
		file.open(QIODevice::WriteOnly);
		file.write((const char *) data, bytes * sizeof(double));
		file.close();
	}


	static QString readString(const QString &path)
	{
		QFile file(path);
		file.open(QFile::ReadOnly);
		QString content = file.readAll();
		file.close();
		return content;
	}
}


#endif // CAPTURE3_FILE_UTILS_H

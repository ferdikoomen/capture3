#include "Project.h"


namespace Capture3
{

	Project::Project() :
		QObject(),
		nextFileRaw(),
		nextFileImage(),
		countRaw(1),
		countImage(1),
		database(QSqlDatabase::addDatabase("QSQLITE")),
		databaseQuery(database),
		images()
	{
		// Open path
		open(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/" + APPLICATION_NAME);
	}


	Project::~Project()
	{
		database.close();
		databaseQuery.clear();
		images.clear();
	}


	void Project::select()
	{
		// Open file dialog and select folder
		QString path = QFileDialog::getExistingDirectory();
		if (!path.isEmpty()) {
			open(path);
		}
	}


	const QFileInfo Project::getNextFileRaw()
	{
		// Return relative path to next image (files/dsc/DSC_0003.NEF)
		const QString fileNumber = QString("%1").arg(countRaw++, 4, 10, QChar('0'));
		const QString filePath = "files/dsc/DSC_" + fileNumber + ".NEF";
		nextFileRaw.setFile(filePath);
		return nextFileRaw;
	}


	const QFileInfo Project::getNextFileImage()
	{
		// Return relative path to next image (files/img/IMG_0001.RAW)
		const QString fileNumber = QString("%1").arg(countImage++, 4, 10, QChar('0'));
		const QString filePath = "files/img/IMG_" + fileNumber + ".RAW";
		nextFileImage.setFile(filePath);
		return nextFileImage;
	}


	void Project::open(const QString &path)
	{
		// Create file directories
		QDir dir;
		dir.mkpath(path);
		dir.mkpath(path + "/files");
		dir.mkpath(path + "/files/dsc");
		dir.mkpath(path + "/files/img");

		// Set current working directory
		QDir::setCurrent(path);

		// Open database
		database.close();
		database.setDatabaseName("project.sqlite");
		database.open();

		// Create tables
		QStringList query;
		query << "CREATE TABLE IF NOT EXISTS 'images' (";
		query << "'id' integer PRIMARY KEY AUTOINCREMENT,";
		query << "'file_name' char(128),";
		query << "'file_path' char(128),";
		query << "'file_width' integer,";
		query << "'file_height' integer,";
		query << "'setting_aperture' integer,";
		query << "'setting_shutter_speed' integer,";
		query << "'setting_iso' integer,";
		query << "'setting_shots' integer,";
		query << "'setting_range' integer,";
		query << "'setting_step' integer";
		query << ")";
		databaseQuery.prepare(query.join(" "));
		databaseQuery.exec();
		databaseQuery.clear();

		// Load images from database
		databaseQuery.prepare("SELECT * FROM 'images'");
		if (databaseQuery.exec()) {
			while (databaseQuery.next()) {

				// Fetch meta information
				const QString fileName = databaseQuery.value("file_name").toString();
				const QString filePath = databaseQuery.value("file_path").toString();
				const unsigned int fileWidth = databaseQuery.value("file_width").toUInt();
				const unsigned int fileHeight = databaseQuery.value("file_Height").toUInt();

				// Create new image
				auto *image = new Image(fileWidth, fileHeight);

				// Store meta information
				image->getMeta().fileName = fileName;
				image->getMeta().filePath = filePath;
				image->getMeta().settingAperture = databaseQuery.value("setting_aperture").toUInt();
				image->getMeta().settingShutterSpeed = databaseQuery.value("setting_shutter_speed").toUInt();
				image->getMeta().settingIso = databaseQuery.value("setting_iso").toUInt();
				image->getMeta().settingShots = databaseQuery.value("setting_shots").toUInt();
				image->getMeta().settingRange = databaseQuery.value("setting_range").toUInt();
				image->getMeta().settingStep = databaseQuery.value("setting_step").toUInt();
				image->read(filePath + fileName);
				// images.push_back(image);
			}
		}

		databaseQuery.clear();
	}


	void Project::add(Image *image)
	{
		// Add image
		QStringList query;
		query << "INSERT INTO 'images'";
		query << "(";
		query << "'file_name',";
		query << "'file_path',";
		query << "'file_width',";
		query << "'file_height',";
		query << "'setting_aperture',";
		query << "'setting_shutter_speed',";
		query << "'setting_iso',";
		query << "'setting_shots',";
		query << "'setting_range',";
		query << "'setting_step'";
		query << ")";
		query << "VALUES";
		query << "(";
		query << "'" + image->getMeta().fileName + "',";
		query << "'" + image->getMeta().filePath + "',";
		query << "'" + QString::number(image->getSize().getWidth()) + "',";
		query << "'" + QString::number(image->getSize().getHeight()) + "',";
		query << "'" + QString::number(image->getMeta().settingAperture) + "',";
		query << "'" + QString::number(image->getMeta().settingShutterSpeed) + "',";
		query << "'" + QString::number(image->getMeta().settingIso) + "',";
		query << "'" + QString::number(image->getMeta().settingShots) + "',";
		query << "'" + QString::number(image->getMeta().settingRange) + "',";
		query << "'" + QString::number(image->getMeta().settingStep) + "'";
		query << ")";
		databaseQuery.prepare(query.join(" "));
		databaseQuery.exec();
		databaseQuery.clear();

		// Add image to list
		// images.push_back(image);
	}


	void Project::remove(const Image *image)
	{
		// Remove image from database
		databaseQuery.prepare("DELETE FROM 'images' WHERE file_name = '" + image->getMeta().fileName + "'");
		databaseQuery.exec();
		databaseQuery.clear();

		// Remove image from list
		for (unsigned int i = 0; i < images.size(); i++) {
			if (images[i] == image) {

				// Clear image
				const Image *item = images[i];
				delete item;

				// Remove from list
				images[i] = nullptr;
				images.erase(images.begin() + i);
				break;
			}
		}
	}

}
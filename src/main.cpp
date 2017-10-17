#include <QtWidgets/QApplication>
#include <QtGui/QSurfaceFormat>


#include "constants/ApplicationConstants.h"
#include "application/Application.h"


int main(int argc, char *argv[])
{
	// OpenGL format
	QSurfaceFormat format;
	format.setVersion(4, 1);
	format.setProfile(QSurfaceFormat::CoreProfile);
	format.setDepthBufferSize(16);
	format.setSamples(4);
	QSurfaceFormat::setDefaultFormat(format);

	// Start application wrapper
	QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QApplication::setApplicationName(Capture3::APPLICATION_NAME);
	QApplication::setApplicationVersion(Capture3::APPLICATION_VERSION);
	QApplication::setOrganizationName(Capture3::APPLICATION_COMPANY);
	QApplication::setQuitOnLastWindowClosed(true);
	QApplication::setDesktopSettingsAware(true);
	QApplication app(argc, argv);

	// Run application
	Capture3::Application application;

	// Wait for event loop exit
	return app.exec();
}
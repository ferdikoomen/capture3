#include "Application.h"

#include <QDebug>

namespace Capture3
{

	Application::Application() :
		QObject(),
		engine(),
		window(),
		welcomeModule(engine),
		exposureModule(engine),
		ambientModule(engine),
		colorChartModule(engine),
		colorProfileModule(engine),
		captureModule(engine),
		exportModule(engine)
	{
		// Add modules
		window.add(&welcomeModule);
		window.add(&exposureModule);
		window.add(&ambientModule);
		window.add(&colorChartModule);
		window.add(&colorProfileModule);
		window.add(&captureModule);
		window.add(&exportModule);

		// Load GUI styles
		loadStylesheet();

		// Show window
		updateTitle();
		window.show();
	}


	Application::~Application()
	{
		window.deleteLater();
		welcomeModule.deleteLater();
		exposureModule.deleteLater();
		ambientModule.deleteLater();
		colorChartModule.deleteLater();
		colorProfileModule.deleteLater();
		captureModule.deleteLater();
		exportModule.deleteLater();
	}


	void Application::updateTitle()
	{
		// Show current working dir in title
		QStringList title;
		title << APPLICATION_NAME;
		title << " - ";
		title << "[";
		title << QDir::current().currentPath();
		title << "]";
		window.setWindowTitle(title.join(""));
	}


	void Application::loadStylesheet()
	{
		qApp->setStyleSheet(
			readString(FILE_STYLE)
		);
	}
}
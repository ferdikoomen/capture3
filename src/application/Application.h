#ifndef CAPTURE3_APPLICATION_H
#define CAPTURE3_APPLICATION_H


#include <QtCore/QObject>
#include <QtCore/QFile>
#include <QtCore/QDir>
#include <QtCore/QThreadPool>
#include <QtCore/QRunnable>
#include <QtWidgets/QApplication>


#include "components/window/WindowComponent.h"
#include "modules/welcome/WelcomeModule.h"
#include "modules/exposure/ExposureModule.h"
#include "modules/ambient/AmbientModule.h"
#include "modules/colorChart/ColorChartModule.h"
#include "modules/colorProfile/ColorProfileModule.h"
#include "modules/capture/CaptureModule.h"
#include "modules/export/ExportModule.h"
#include "../engine/Engine.h"
#include "../engine/objects/image/Image.h"
#include "../constants/ApplicationConstants.h"
#include "../constants/ResourceConstants.h"
#include "../utils/FileUtils.h"


namespace Capture3
{
	class Application final : public QObject
	{
		Q_OBJECT

		public:
			Application();

			virtual ~Application();

		private:
			void updateTitle();

			void loadStylesheet();

			Engine engine;
			WindowComponent window;
			WelcomeModule welcomeModule;
			ExposureModule exposureModule;
			AmbientModule ambientModule;
			ColorChartModule colorChartModule;
			ColorProfileModule colorProfileModule;
			CaptureModule captureModule;
			ExportModule exportModule;

	};
}


#endif // CAPTURE3_APPLICATION_H

#ifndef CAPTURE3_WELCOME_MODULE_H
#define CAPTURE3_WELCOME_MODULE_H


#include <QtWidgets/QPushButton>


#include "../../panels/camera/CameraPanel.h"
#include "../../panels/thumbnails/ThumbnailsPanel.h"
#include "../../panels/image/ImagePanel.h"
#include "../../panels/imageData/ImageDataPanel.h"
#include "../../panels/dynamicRange/DynamicRangePanel.h"
#include "../../panels/profileCurves/ProfileCurvesPanel.h"
#include "../../panels/profileResult/ProfileResultPanel.h"
#include "../../panels/patches/PatchesPanel.h"
#include "../../components/module/ModuleComponent.h"
#include "../../components/thumbnails/ThumbnailsComponent.h"
#include "../../components/progressBar/ProgressBarComponent.h"
#include "../../components/progressDialog/ProgressDialogComponent.h"
#include "../../../engine/Engine.h"
#include "../../../engine/objects/colorChart/ColorChart.h"
#include "../../../engine/objects/colorProfile/ColorProfile.h"
#include "../../../engine/objects/image/Image.h"
#include "../../../engine/objects/project/Project.h"
#include "../../../engine/objects/whiteBalance/WhiteBalance.h"
#include "../../../engine/objects/whiteLevel/WhiteLevel.h"
#include "../../../utils/ColorChartDetectionUtils.h"
#include "../../../utils/ColorChartPreviewUtils.h"
#include "../../../utils/ImageExportUtils.h"
#include "../../../utils/ImageImportUtils.h"


namespace Capture3
{
	class WelcomeModule final : public ModuleComponent
	{
		Q_OBJECT

		public:
			WelcomeModule(Engine &engine);

			virtual ~WelcomeModule();

		public slots:

			void showImage(const Image *image);

			void removeImage(const Image *image);

			void exportImage(const Image *image);

			void capture();

		private:
			Engine &engine;
			CameraPanel cameraPanel;
			ThumbnailsPanel thumbnailsPanel;
			ImagePanel imagePanel;
			ImageDataPanel imageDataPanel;
			DynamicRangePanel dynamicRangePanel;
			ProfileCurvesPanel profileCurvesPanel;
			ProfileResultPanel profileResultPanel;
			PatchesPanel patchesPanel;
	};
}


#endif // CAPTURE3_WELCOME_MODULE_H

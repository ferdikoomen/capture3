#ifndef CAPTURE3_CAMERA_PANEL_H
#define CAPTURE3_CAMERA_PANEL_H


#include "../../components/panel/PanelComponent.h"
#include "../../components/panelTabs/PanelTabsComponent.h"
#include "../../components/cameraPreview/CameraPreviewComponent.h"
#include "../../components/cameraSettings/CameraSettingsComponent.h"
#include "../../components/cameraControl/CameraControlComponent.h"
#include "../../../engine/objects/camera/Camera.h"


namespace Capture3
{
	class CameraPanel final : public PanelComponent
	{
		Q_OBJECT

		public:
			CameraPanel(Camera &camera);

			virtual ~CameraPanel();

			CameraPreviewComponent &getCameraPreview();

			CameraSettingsComponent &getCameraSettings();

			CameraControlComponent &getCameraControl();

		private:
			PanelTabsComponent tabs1;
			PanelTabsComponent tabs2;
			CameraPreviewComponent cameraPreview;
			CameraSettingsComponent cameraSettings;
			CameraControlComponent cameraControl;

	};
}


#endif // CAPTURE3_CAMERA_PANEL_H

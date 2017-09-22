#include "CameraPanel.h"


namespace Capture3
{

	CameraPanel::CameraPanel(Camera &camera) :
		PanelComponent(),
		tabs1(),
		tabs2(),
		cameraPreview(camera),
		cameraSettings(camera),
		cameraControl(camera)
	{
		// Add items
		tabs1.addTab(&cameraPreview);
		tabs2.addTab(&cameraControl);
		tabs2.addTab(&cameraSettings);
		addTabs(&tabs1);
		addTabs(&tabs2);

		setStretchFactor(0, 1);
		setStretchFactor(1, 2);
	}


	CameraPanel::~CameraPanel()
	{
		cameraPreview.deleteLater();
		cameraSettings.deleteLater();
		cameraControl.deleteLater();
		tabs1.deleteLater();
		tabs2.deleteLater();
	}


	CameraPreviewComponent &CameraPanel::getCameraPreview()
	{
		return cameraPreview;
	}


	CameraSettingsComponent &CameraPanel::getCameraSettings()
	{
		return cameraSettings;
	}


	CameraControlComponent &CameraPanel::getCameraControl()
	{
		return cameraControl;
	}

}
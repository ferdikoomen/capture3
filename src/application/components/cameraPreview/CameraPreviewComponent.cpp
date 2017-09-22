#include "CameraPreviewComponent.h"


namespace Capture3
{

	CameraPreviewComponent::CameraPreviewComponent(Camera &camera) :
		PanelTabComponent("Camera Preview"),
		camera(camera),
		image(camera),
		labelBattery("Battery: 0%")
	{
		// Add items
		addWidget(&image);
		addWidget(&labelBattery);

		// Listen to battery level updates
		QObject::connect(&camera, &Camera::onUpdateBatteryLevel, [this]() {
			labelBattery.setText("Battery: " + this->camera.getBatteryLevel());
		});
	}


	CameraPreviewComponent::~CameraPreviewComponent()
	{
		QObject::disconnect(&camera, nullptr, nullptr, nullptr);
		image.deleteLater();
		labelBattery.deleteLater();
	}
}
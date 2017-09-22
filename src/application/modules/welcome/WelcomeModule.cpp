#include "WelcomeModule.h"


namespace Capture3
{

	WelcomeModule::WelcomeModule(Engine &engine) :
		ModuleComponent("Welcome"),
		engine(engine),
		cameraPanel(engine.getCamera()),
		thumbnailsPanel(),
		imagePanel(),
		imageDataPanel(),
		dynamicRangePanel(),
		profileCurvesPanel(),
		profileResultPanel(),
		patchesPanel()
	{
		// Add items
		addWidget(&cameraPanel);
		addWidget(&thumbnailsPanel);
		addWidget(&imagePanel);
		addWidget(&imageDataPanel);
		// addWidget(&dynamicRangePanel);
		// addWidget(&profileResultPanel);
		addWidget(&profileCurvesPanel);
		addWidget(&patchesPanel);

		QObject::connect(&thumbnailsPanel.getThumbnails(), &ThumbnailsComponent::onSelectClicked, this, &WelcomeModule::showImage);
		QObject::connect(&thumbnailsPanel.getThumbnails(), &ThumbnailsComponent::onRemoveClicked, this, &WelcomeModule::removeImage);
		QObject::connect(&thumbnailsPanel.getThumbnails(), &ThumbnailsComponent::onExportClicked, this, &WelcomeModule::exportImage);
		QObject::connect(&cameraPanel.getCameraControl().getButton(), &QPushButton::clicked, this, &WelcomeModule::capture);
	}


	WelcomeModule::~WelcomeModule()
	{
		QObject::disconnect(&thumbnailsPanel.getThumbnails(), nullptr, nullptr, nullptr);
		QObject::disconnect(&cameraPanel.getCameraControl().getButton(), nullptr, nullptr, nullptr);

		cameraPanel.deleteLater();
		thumbnailsPanel.deleteLater();
		imagePanel.deleteLater();
		imageDataPanel.deleteLater();
		dynamicRangePanel.deleteLater();
		profileCurvesPanel.deleteLater();
		profileResultPanel.deleteLater();
		patchesPanel.deleteLater();
	}


	void WelcomeModule::showImage(const Image *image)
	{
		thumbnailsPanel.getThumbnails().select(image);
		imagePanel.getImageViewer().show(image);
		imageDataPanel.getImageHistogram().show(image);
		imageDataPanel.getImageGraph().show(image);
		imageDataPanel.getImageWaveform().show(image);
	}


	void WelcomeModule::removeImage(const Image *image)
	{
		thumbnailsPanel.getThumbnails().remove(image);
		imagePanel.getImageViewer().reset();
		imageDataPanel.getImageHistogram().reset();
		imageDataPanel.getImageGraph().reset();
		imageDataPanel.getImageWaveform().reset();
	}


	void WelcomeModule::exportImage(const Image *image)
	{
		exportImageDialog(image->getRGB().getMat());
	}


	void WelcomeModule::capture()
	{
		// Capture / load background image
		Image *imageWhite = engine.getCamera().capture(
			cameraPanel.getCameraControl().getIndexAperture(),
			cameraPanel.getCameraControl().getIndexShutterSpeed(),
			cameraPanel.getCameraControl().getIndexIso(),
			cameraPanel.getCameraControl().getIndexShots(),
			cameraPanel.getCameraControl().getIndexRange(),
			cameraPanel.getCameraControl().getIndexStep(),
			cameraPanel.getCameraControl().getIndexMergeShots(),
			cameraPanel.getCameraControl().getIndexMergeRange(),
			cameraPanel.getCameraControl().getFocusNear(),
			cameraPanel.getCameraControl().getFocusFar()
		);

		// Capture / load background image
		Image *imageColorChart = engine.getCamera().capture(
			cameraPanel.getCameraControl().getIndexAperture(),
			cameraPanel.getCameraControl().getIndexShutterSpeed(),
			cameraPanel.getCameraControl().getIndexIso(),
			cameraPanel.getCameraControl().getIndexShots(),
			cameraPanel.getCameraControl().getIndexRange(),
			cameraPanel.getCameraControl().getIndexStep(),
			cameraPanel.getCameraControl().getIndexMergeShots(),
			cameraPanel.getCameraControl().getIndexMergeRange(),
			cameraPanel.getCameraControl().getFocusNear(),
			cameraPanel.getCameraControl().getFocusFar()
		);

		// Convert background image to white level map
		auto *whiteLevel = new WhiteLevel(imageWhite);
		whiteLevel->apply(imageColorChart);
		imageColorChart->convertRGB();

		// Detect color chart and create color profile
		auto *colorChartReference = new ColorChart();
		ColorChart *colorChartDetected = detectColorChart(imageColorChart);
		auto *colorProfile = new ColorProfile(colorChartReference, colorChartDetected);
		auto *whiteBalance = new WhiteBalance(colorChartReference, colorChartDetected);

		// Display the color chart image with gamma correction
		imageColorChart->gammaCorrection();

		// Show!
		thumbnailsPanel.getThumbnails().add(imageWhite);
		thumbnailsPanel.getThumbnails().add(imageColorChart);
		thumbnailsPanel.getThumbnails().add(generatePreview(colorChartReference));
		thumbnailsPanel.getThumbnails().add(generatePreview(colorChartDetected));
		patchesPanel.getColorChart().show(colorProfile);
		profileCurvesPanel.getColorProfileCurves().show(colorProfile);
		profileCurvesPanel.getWhiteBalanceCurves().show(whiteBalance);
		profileResultPanel.getColorProfileGraph().show(colorChartReference, colorChartDetected);
		profileResultPanel.getColorProfileMatrix().show(colorChartReference, colorChartDetected);
		showImage(imageColorChart);
	}

}
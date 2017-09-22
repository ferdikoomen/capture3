#include "ImageViewerComponent.h"


namespace Capture3
{

	ImageViewerComponent::ImageViewerComponent() :
		PanelTabComponent("Image"),
		display(),
		menu(),
		image(nullptr),
		cursorX(0),
		cursorY(0)
	{
		// Add items
		addWidget(&display, 0, 0);
		addWidget(&menu, 0, 1);
		setSpacing(4);

		// Only stretch the image display
		setColumnStretch(0, 1);
		setColumnStretch(1, 1);

		// Link buttons
		QObject::connect(&menu.getButtonRGB(), &QRadioButton::clicked, this, &ImageViewerComponent::showImage);
		QObject::connect(&menu.getButtonRGB_R(), &QRadioButton::clicked, this, &ImageViewerComponent::showImage);
		QObject::connect(&menu.getButtonRGB_G(), &QRadioButton::clicked, this, &ImageViewerComponent::showImage);
		QObject::connect(&menu.getButtonRGB_B(), &QRadioButton::clicked, this, &ImageViewerComponent::showImage);
		QObject::connect(&menu.getButtonHSB(), &QRadioButton::clicked, this, &ImageViewerComponent::showImage);
		QObject::connect(&menu.getButtonHSB_H(), &QRadioButton::clicked, this, &ImageViewerComponent::showImage);
		QObject::connect(&menu.getButtonHSB_S(), &QRadioButton::clicked, this, &ImageViewerComponent::showImage);
		QObject::connect(&menu.getButtonHSB_B(), &QRadioButton::clicked, this, &ImageViewerComponent::showImage);
		QObject::connect(&menu.getButtonXYZ(), &QRadioButton::clicked, this, &ImageViewerComponent::showImage);
		QObject::connect(&menu.getButtonXYZ_X(), &QRadioButton::clicked, this, &ImageViewerComponent::showImage);
		QObject::connect(&menu.getButtonXYZ_Y(), &QRadioButton::clicked, this, &ImageViewerComponent::showImage);
		QObject::connect(&menu.getButtonXYZ_Z(), &QRadioButton::clicked, this, &ImageViewerComponent::showImage);
		QObject::connect(&menu.getButtonXYV(), &QRadioButton::clicked, this, &ImageViewerComponent::showImage);
		QObject::connect(&menu.getButtonXYV_X(), &QRadioButton::clicked, this, &ImageViewerComponent::showImage);
		QObject::connect(&menu.getButtonXYV_Y(), &QRadioButton::clicked, this, &ImageViewerComponent::showImage);
		QObject::connect(&menu.getButtonXYV_V(), &QRadioButton::clicked, this, &ImageViewerComponent::showImage);
		QObject::connect(&menu.getButtonLAB(), &QRadioButton::clicked, this, &ImageViewerComponent::showImage);
		QObject::connect(&menu.getButtonLAB_L(), &QRadioButton::clicked, this, &ImageViewerComponent::showImage);
		QObject::connect(&menu.getButtonLAB_A(), &QRadioButton::clicked, this, &ImageViewerComponent::showImage);
		QObject::connect(&menu.getButtonLAB_B(), &QRadioButton::clicked, this, &ImageViewerComponent::showImage);
		QObject::connect(&menu.getCheckboxShadowClipping(), &QCheckBox::clicked, this, &ImageViewerComponent::showImage);
		QObject::connect(&menu.getCheckboxHighlightClipping(), &QCheckBox::clicked, this, &ImageViewerComponent::showImage);

		// Link mouse movement
		QObject::connect(&display, &ImageViewerComponentDisplay::showColor, this, &ImageViewerComponent::showColor);
	}


	ImageViewerComponent::~ImageViewerComponent()
	{
		QObject::disconnect(&menu.getButtonRGB(), nullptr, nullptr, nullptr);
		QObject::disconnect(&menu.getButtonRGB_R(), nullptr, nullptr, nullptr);
		QObject::disconnect(&menu.getButtonRGB_G(), nullptr, nullptr, nullptr);
		QObject::disconnect(&menu.getButtonRGB_B(), nullptr, nullptr, nullptr);
		QObject::disconnect(&menu.getButtonHSB(), nullptr, nullptr, nullptr);
		QObject::disconnect(&menu.getButtonHSB_H(), nullptr, nullptr, nullptr);
		QObject::disconnect(&menu.getButtonHSB_S(), nullptr, nullptr, nullptr);
		QObject::disconnect(&menu.getButtonHSB_B(), nullptr, nullptr, nullptr);
		QObject::disconnect(&menu.getButtonXYZ(), nullptr, nullptr, nullptr);
		QObject::disconnect(&menu.getButtonXYZ_X(), nullptr, nullptr, nullptr);
		QObject::disconnect(&menu.getButtonXYZ_Y(), nullptr, nullptr, nullptr);
		QObject::disconnect(&menu.getButtonXYZ_Z(), nullptr, nullptr, nullptr);
		QObject::disconnect(&menu.getButtonXYV(), nullptr, nullptr, nullptr);
		QObject::disconnect(&menu.getButtonXYV_X(), nullptr, nullptr, nullptr);
		QObject::disconnect(&menu.getButtonXYV_Y(), nullptr, nullptr, nullptr);
		QObject::disconnect(&menu.getButtonXYV_V(), nullptr, nullptr, nullptr);
		QObject::disconnect(&menu.getButtonLAB(), nullptr, nullptr, nullptr);
		QObject::disconnect(&menu.getButtonLAB_L(), nullptr, nullptr, nullptr);
		QObject::disconnect(&menu.getButtonLAB_A(), nullptr, nullptr, nullptr);
		QObject::disconnect(&menu.getButtonLAB_B(), nullptr, nullptr, nullptr);
		QObject::disconnect(&display, nullptr, nullptr, nullptr);

		display.deleteLater();
		menu.deleteLater();
		image = nullptr;
	}


	void ImageViewerComponent::show(const Image *image)
	{
		this->image = image;
		showImage();
		showColor(cursorX, cursorY);
	}


	void ImageViewerComponent::reset()
	{
		// Remove image and clear menu color
		image = nullptr;
		display.show(QImage());
		menu.setColor(
			0, 0, 0,
			0, 0, 0,
			0, 0, 0,
			0, 0, 0,
			0, 0, 0
		);
	}


	void ImageViewerComponent::showImage()
	{
		// Check if we should show shadow / highlight clipping
		const bool showShadowClipping = menu.getCheckboxShadowClipping().isChecked();
		const bool showHighlightClipping = menu.getCheckboxHighlightClipping().isChecked();

		// Generate correct preview based on selected radio button
		if (image != nullptr) {
			display.show(
				menu.getButtonRGB_R().isChecked() ? generatePreviewImageX(image->getRGB(), showShadowClipping, showHighlightClipping) :
				menu.getButtonRGB_G().isChecked() ? generatePreviewImageY(image->getRGB(), showShadowClipping, showHighlightClipping) :
				menu.getButtonRGB_B().isChecked() ? generatePreviewImageZ(image->getRGB(), showShadowClipping, showHighlightClipping) :
				menu.getButtonHSB().isChecked() ? generatePreviewImage(image->getHSB(), showShadowClipping, showHighlightClipping) :
				menu.getButtonHSB_H().isChecked() ? generatePreviewImageX(image->getHSB(), showShadowClipping, showHighlightClipping) :
				menu.getButtonHSB_S().isChecked() ? generatePreviewImageY(image->getHSB(), showShadowClipping, showHighlightClipping) :
				menu.getButtonHSB_B().isChecked() ? generatePreviewImageZ(image->getHSB(), showShadowClipping, showHighlightClipping) :
				menu.getButtonXYZ().isChecked() ? generatePreviewImage(image->getXYZ(), showShadowClipping, showHighlightClipping) :
				menu.getButtonXYZ_X().isChecked() ? generatePreviewImageX(image->getXYZ(), showShadowClipping, showHighlightClipping) :
				menu.getButtonXYZ_Y().isChecked() ? generatePreviewImageY(image->getXYZ(), showShadowClipping, showHighlightClipping) :
				menu.getButtonXYZ_Z().isChecked() ? generatePreviewImageZ(image->getXYZ(), showShadowClipping, showHighlightClipping) :
				menu.getButtonXYV().isChecked() ? generatePreviewImage(image->getXYV(), showShadowClipping, showHighlightClipping) :
				menu.getButtonXYV_X().isChecked() ? generatePreviewImageX(image->getXYV(), showShadowClipping, showHighlightClipping) :
				menu.getButtonXYV_Y().isChecked() ? generatePreviewImageY(image->getXYV(), showShadowClipping, showHighlightClipping) :
				menu.getButtonXYV_V().isChecked() ? generatePreviewImageZ(image->getXYV(), showShadowClipping, showHighlightClipping) :
				menu.getButtonLAB().isChecked() ? generatePreviewImage(image->getLAB(), showShadowClipping, showHighlightClipping) :
				menu.getButtonLAB_L().isChecked() ? generatePreviewImageX(image->getLAB(), showShadowClipping, showHighlightClipping) :
				menu.getButtonLAB_A().isChecked() ? generatePreviewImageY(image->getLAB(), showShadowClipping, showHighlightClipping) :
				menu.getButtonLAB_B().isChecked() ? generatePreviewImageZ(image->getLAB(), showShadowClipping, showHighlightClipping) :
				generatePreviewImage(image->getRGB(), showShadowClipping, showHighlightClipping)
			);
		}
	}


	void ImageViewerComponent::showColor(const int x, const int y)
	{
		if (image != nullptr) {

			// Limit values
			cursorX = x;
			cursorY = y;
			cursorX = cursorX < 0 ? 0 : cursorX;
			cursorY = cursorY < 0 ? 0 : cursorY;
			cursorX = cursorX > image->getSize().getWidth() - 1 ? (int) image->getSize().getWidth() - 1 : cursorX;
			cursorY = cursorY > image->getSize().getHeight() - 1 ? (int) image->getSize().getHeight() - 1 : cursorY;

			// Find index in data
			int index = (image->getSize().getWidth() * cursorY) + cursorX;

			// Show color in menu
			menu.setColor(
				image->getRGB().getData()[(index * 3) + 0],
				image->getRGB().getData()[(index * 3) + 1],
				image->getRGB().getData()[(index * 3) + 2],
				image->getHSB().getData()[(index * 3) + 0],
				image->getHSB().getData()[(index * 3) + 1],
				image->getHSB().getData()[(index * 3) + 2],
				image->getXYZ().getData()[(index * 3) + 0],
				image->getXYZ().getData()[(index * 3) + 1],
				image->getXYZ().getData()[(index * 3) + 2],
				image->getXYV().getData()[(index * 3) + 0],
				image->getXYV().getData()[(index * 3) + 1],
				image->getXYV().getData()[(index * 3) + 2],
				image->getLAB().getData()[(index * 3) + 0],
				image->getLAB().getData()[(index * 3) + 1],
				image->getLAB().getData()[(index * 3) + 2]
			);

			// Update cursor position
			display.setCursorPosition(cursorX, cursorY);
		}
	}

}
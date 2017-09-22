#include "ColorProfileMatrixComponent.h"


namespace Capture3
{

	ColorProfileMatrixComponent::ColorProfileMatrixComponent() :
		PanelTabComponent("Color Profile Matrix"),

		// Groups
		groupPreview("Preview"),
		groupTable("Matrix"),
		groupRow1("Row (X)"),
		groupRow2("Row (Y)"),
		groupRow3("Row (Z)"),

		// Matrix preview and table
		preview(256, 246),
		table(),

		// Fields
		sliderM11(Qt::Horizontal),
		sliderM12(Qt::Horizontal),
		sliderM13(Qt::Horizontal),
		sliderM14(Qt::Horizontal),
		sliderM21(Qt::Horizontal),
		sliderM22(Qt::Horizontal),
		sliderM23(Qt::Horizontal),
		sliderM24(Qt::Horizontal),
		sliderM31(Qt::Horizontal),
		sliderM32(Qt::Horizontal),
		sliderM33(Qt::Horizontal),
		sliderM34(Qt::Horizontal),
		fieldM11(),
		fieldM12(),
		fieldM13(),
		fieldM14(),
		fieldM21(),
		fieldM22(),
		fieldM23(),
		fieldM24(),
		fieldM31(),
		fieldM32(),
		fieldM33(),
		fieldM34(),

		// Data
		matrix(),
		positions(840),
		colors(840),

		// Color charts
		colorChartReference(nullptr),
		colorChartDetected(nullptr)
	{
		// Set point size
		preview.setPointSize(2.0f);
		preview.setLineSize(2.0f);

		// Default table options
		table.verticalHeader()->show();
		table.verticalHeader()->setDefaultSectionSize(18);
		table.horizontalHeader()->setDefaultSectionSize(55);
		table.setColumnCount(4);
		table.setRowCount(3);
		table.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

		// Set headers
		table.setHorizontalHeader(0, "X'");
		table.setHorizontalHeader(1, "Y'");
		table.setHorizontalHeader(2, "Z'");
		table.setHorizontalHeader(3, "Offset");
		table.setVerticalHeader(0, "X");
		table.setVerticalHeader(1, "Y");
		table.setVerticalHeader(2, "Z");

		// Remove nasty focus outlines from spin boxes
		fieldM11.setAttribute(Qt::WA_MacShowFocusRect, false);
		fieldM12.setAttribute(Qt::WA_MacShowFocusRect, false);
		fieldM13.setAttribute(Qt::WA_MacShowFocusRect, false);
		fieldM14.setAttribute(Qt::WA_MacShowFocusRect, false);
		fieldM21.setAttribute(Qt::WA_MacShowFocusRect, false);
		fieldM22.setAttribute(Qt::WA_MacShowFocusRect, false);
		fieldM23.setAttribute(Qt::WA_MacShowFocusRect, false);
		fieldM24.setAttribute(Qt::WA_MacShowFocusRect, false);
		fieldM31.setAttribute(Qt::WA_MacShowFocusRect, false);
		fieldM32.setAttribute(Qt::WA_MacShowFocusRect, false);
		fieldM33.setAttribute(Qt::WA_MacShowFocusRect, false);
		fieldM34.setAttribute(Qt::WA_MacShowFocusRect, false);

		// Set options for fields
		fieldM11.setRange(-500, 500);
		fieldM12.setRange(-500, 500);
		fieldM13.setRange(-500, 500);
		fieldM14.setRange(-500, 500);
		fieldM21.setRange(-500, 500);
		fieldM22.setRange(-500, 500);
		fieldM23.setRange(-500, 500);
		fieldM24.setRange(-500, 500);
		fieldM31.setRange(-500, 500);
		fieldM32.setRange(-500, 500);
		fieldM33.setRange(-500, 500);
		fieldM34.setRange(-500, 500);

		// Set options for slider
		sliderM11.setRange(-500, 500);
		sliderM12.setRange(-500, 500);
		sliderM13.setRange(-500, 500);
		sliderM14.setRange(-500, 500);
		sliderM21.setRange(-500, 500);
		sliderM22.setRange(-500, 500);
		sliderM23.setRange(-500, 500);
		sliderM24.setRange(-500, 500);
		sliderM31.setRange(-500, 500);
		sliderM32.setRange(-500, 500);
		sliderM33.setRange(-500, 500);
		sliderM34.setRange(-500, 500);

		// Set values
		fieldM11.setValue(100);
		fieldM22.setValue(100);
		fieldM33.setValue(100);
		sliderM11.setValue(100);
		sliderM22.setValue(100);
		sliderM33.setValue(100);

		// Add items
		groupPreview.addWidget(&preview);
		groupTable.addWidget(&table);
		groupRow1.addWidget(&sliderM11, 0, 0);
		groupRow1.addWidget(&sliderM12, 1, 0);
		groupRow1.addWidget(&sliderM13, 2, 0);
		groupRow1.addWidget(&sliderM14, 3, 0);
		groupRow1.addWidget(&fieldM11, 0, 1);
		groupRow1.addWidget(&fieldM12, 1, 1);
		groupRow1.addWidget(&fieldM13, 2, 1);
		groupRow1.addWidget(&fieldM14, 3, 1);
		groupRow2.addWidget(&sliderM21, 0, 0);
		groupRow2.addWidget(&sliderM22, 1, 0);
		groupRow2.addWidget(&sliderM23, 2, 0);
		groupRow2.addWidget(&sliderM24, 3, 0);
		groupRow2.addWidget(&fieldM21, 0, 1);
		groupRow2.addWidget(&fieldM22, 1, 1);
		groupRow2.addWidget(&fieldM23, 2, 1);
		groupRow2.addWidget(&fieldM24, 3, 1);
		groupRow3.addWidget(&sliderM31, 0, 0);
		groupRow3.addWidget(&sliderM32, 1, 0);
		groupRow3.addWidget(&sliderM33, 2, 0);
		groupRow3.addWidget(&sliderM34, 3, 0);
		groupRow3.addWidget(&fieldM31, 0, 1);
		groupRow3.addWidget(&fieldM32, 1, 1);
		groupRow3.addWidget(&fieldM33, 2, 1);
		groupRow3.addWidget(&fieldM34, 3, 1);
		addWidget(&groupPreview);
		addWidget(&groupTable);
		addWidget(&groupRow1);
		addWidget(&groupRow2);
		addWidget(&groupRow3);

		// Connect signals
		QObject::connect(&sliderM11, &QSlider::valueChanged, this, &ColorProfileMatrixComponent::onSliderChanged);
		QObject::connect(&sliderM12, &QSlider::valueChanged, this, &ColorProfileMatrixComponent::onSliderChanged);
		QObject::connect(&sliderM13, &QSlider::valueChanged, this, &ColorProfileMatrixComponent::onSliderChanged);
		QObject::connect(&sliderM14, &QSlider::valueChanged, this, &ColorProfileMatrixComponent::onSliderChanged);
		QObject::connect(&sliderM21, &QSlider::valueChanged, this, &ColorProfileMatrixComponent::onSliderChanged);
		QObject::connect(&sliderM22, &QSlider::valueChanged, this, &ColorProfileMatrixComponent::onSliderChanged);
		QObject::connect(&sliderM23, &QSlider::valueChanged, this, &ColorProfileMatrixComponent::onSliderChanged);
		QObject::connect(&sliderM24, &QSlider::valueChanged, this, &ColorProfileMatrixComponent::onSliderChanged);
		QObject::connect(&sliderM31, &QSlider::valueChanged, this, &ColorProfileMatrixComponent::onSliderChanged);
		QObject::connect(&sliderM32, &QSlider::valueChanged, this, &ColorProfileMatrixComponent::onSliderChanged);
		QObject::connect(&sliderM33, &QSlider::valueChanged, this, &ColorProfileMatrixComponent::onSliderChanged);
		QObject::connect(&sliderM34, &QSlider::valueChanged, this, &ColorProfileMatrixComponent::onSliderChanged);
		QObject::connect(&fieldM11, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &ColorProfileMatrixComponent::onFieldChanged);
		QObject::connect(&fieldM12, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &ColorProfileMatrixComponent::onFieldChanged);
		QObject::connect(&fieldM13, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &ColorProfileMatrixComponent::onFieldChanged);
		QObject::connect(&fieldM14, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &ColorProfileMatrixComponent::onFieldChanged);
		QObject::connect(&fieldM21, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &ColorProfileMatrixComponent::onFieldChanged);
		QObject::connect(&fieldM22, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &ColorProfileMatrixComponent::onFieldChanged);
		QObject::connect(&fieldM23, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &ColorProfileMatrixComponent::onFieldChanged);
		QObject::connect(&fieldM24, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &ColorProfileMatrixComponent::onFieldChanged);
		QObject::connect(&fieldM31, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &ColorProfileMatrixComponent::onFieldChanged);
		QObject::connect(&fieldM32, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &ColorProfileMatrixComponent::onFieldChanged);
		QObject::connect(&fieldM33, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &ColorProfileMatrixComponent::onFieldChanged);
		QObject::connect(&fieldM34, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &ColorProfileMatrixComponent::onFieldChanged);
	}


	ColorProfileMatrixComponent::~ColorProfileMatrixComponent()
	{
		// Disconnect signals
		QObject::disconnect(&sliderM11, nullptr, nullptr, nullptr);
		QObject::disconnect(&sliderM12, nullptr, nullptr, nullptr);
		QObject::disconnect(&sliderM13, nullptr, nullptr, nullptr);
		QObject::disconnect(&sliderM14, nullptr, nullptr, nullptr);
		QObject::disconnect(&sliderM21, nullptr, nullptr, nullptr);
		QObject::disconnect(&sliderM22, nullptr, nullptr, nullptr);
		QObject::disconnect(&sliderM23, nullptr, nullptr, nullptr);
		QObject::disconnect(&sliderM24, nullptr, nullptr, nullptr);
		QObject::disconnect(&sliderM31, nullptr, nullptr, nullptr);
		QObject::disconnect(&sliderM32, nullptr, nullptr, nullptr);
		QObject::disconnect(&sliderM33, nullptr, nullptr, nullptr);
		QObject::disconnect(&sliderM34, nullptr, nullptr, nullptr);
		QObject::disconnect(&fieldM11, nullptr, nullptr, nullptr);
		QObject::disconnect(&fieldM12, nullptr, nullptr, nullptr);
		QObject::disconnect(&fieldM13, nullptr, nullptr, nullptr);
		QObject::disconnect(&fieldM14, nullptr, nullptr, nullptr);
		QObject::disconnect(&fieldM21, nullptr, nullptr, nullptr);
		QObject::disconnect(&fieldM22, nullptr, nullptr, nullptr);
		QObject::disconnect(&fieldM23, nullptr, nullptr, nullptr);
		QObject::disconnect(&fieldM24, nullptr, nullptr, nullptr);
		QObject::disconnect(&fieldM31, nullptr, nullptr, nullptr);
		QObject::disconnect(&fieldM32, nullptr, nullptr, nullptr);
		QObject::disconnect(&fieldM33, nullptr, nullptr, nullptr);
		QObject::disconnect(&fieldM34, nullptr, nullptr, nullptr);

		// Cleanup data
		preview.reset();
		positions.clear();
		colors.clear();

		// Cleanup
		preview.deleteLater();
		table.deleteLater();
		sliderM11.deleteLater();
		sliderM12.deleteLater();
		sliderM13.deleteLater();
		sliderM14.deleteLater();
		sliderM21.deleteLater();
		sliderM22.deleteLater();
		sliderM23.deleteLater();
		sliderM24.deleteLater();
		sliderM31.deleteLater();
		sliderM32.deleteLater();
		sliderM33.deleteLater();
		sliderM34.deleteLater();
		fieldM11.deleteLater();
		fieldM12.deleteLater();
		fieldM13.deleteLater();
		fieldM14.deleteLater();
		fieldM21.deleteLater();
		fieldM22.deleteLater();
		fieldM23.deleteLater();
		fieldM24.deleteLater();
		fieldM31.deleteLater();
		fieldM32.deleteLater();
		fieldM33.deleteLater();
		fieldM34.deleteLater();
		groupPreview.deleteLater();
		groupTable.deleteLater();
		groupRow1.deleteLater();
		groupRow2.deleteLater();
		groupRow3.deleteLater();

		// Clear reference
		colorChartReference = nullptr;
		colorChartDetected = nullptr;
	}


	void ColorProfileMatrixComponent::show(
		const ColorChart *colorChartReference,
		const ColorChart *colorChartDetected
	)
	{
		// Save reference
		this->colorChartReference = colorChartReference;
		this->colorChartDetected = colorChartDetected;
		draw();
	}


	void ColorProfileMatrixComponent::onFieldChanged()
	{
		sliderM11.setValue(fieldM11.value());
		sliderM12.setValue(fieldM12.value());
		sliderM13.setValue(fieldM13.value());
		sliderM14.setValue(fieldM14.value());
		sliderM21.setValue(fieldM21.value());
		sliderM22.setValue(fieldM22.value());
		sliderM23.setValue(fieldM23.value());
		sliderM24.setValue(fieldM24.value());
		sliderM31.setValue(fieldM31.value());
		sliderM32.setValue(fieldM32.value());
		sliderM33.setValue(fieldM33.value());
		sliderM34.setValue(fieldM34.value());
		draw();
	}


	void ColorProfileMatrixComponent::onSliderChanged()
	{
		fieldM11.setValue(sliderM11.value());
		fieldM12.setValue(sliderM12.value());
		fieldM13.setValue(sliderM13.value());
		fieldM14.setValue(sliderM14.value());
		fieldM21.setValue(sliderM21.value());
		fieldM22.setValue(sliderM22.value());
		fieldM23.setValue(sliderM23.value());
		fieldM24.setValue(sliderM24.value());
		fieldM31.setValue(sliderM31.value());
		fieldM32.setValue(sliderM32.value());
		fieldM33.setValue(sliderM33.value());
		fieldM34.setValue(sliderM34.value());
		draw();
	}


	void ColorProfileMatrixComponent::draw()
	{
		// Return if we don't have any data
		if (colorChartReference == nullptr || colorChartDetected == nullptr) {
			return;
		}

		// Fetch matrix data
		matrix.reset();
		matrix.setData(
			fieldM11.value() / 100.0, fieldM12.value() / 100.0, fieldM13.value() / 100.0, fieldM14.value() / 100.0,
			fieldM21.value() / 100.0, fieldM22.value() / 100.0, fieldM23.value() / 100.0, fieldM24.value() / 100.0,
			fieldM31.value() / 100.0, fieldM32.value() / 100.0, fieldM33.value() / 100.0, fieldM34.value() / 100.0
		);

		// Fetch patches
		const std::vector<ColorChartPatch *> &patchesReference = colorChartReference->getPatches();
		const std::vector<ColorChartPatch *> &patchesDetected = colorChartDetected->getPatches();

		unsigned int indexColor = 0;
		unsigned int indexPosition = 0;

		for (unsigned int index = 0; index < COLOR_CHART_COUNT; index++) {

			// Fetch patches
			const ColorChartPatch *patchReference = patchesReference[index];
			const ColorChartPatch *patchDetected = patchesDetected[index];

			// Fetch colors
			const double *referenceRGB = patchReference->getRGB();
			const double *detectedRGB = patchDetected->getRGB();

			const double outX = matrix.getX(detectedRGB[0], detectedRGB[1], detectedRGB[2]);
			const double outY = matrix.getY(detectedRGB[0], detectedRGB[1], detectedRGB[2]);
			const double outZ = matrix.getZ(detectedRGB[0], detectedRGB[1], detectedRGB[2]);

			// Store colors
			colors[indexColor++] = (float) referenceRGB[0];
			colors[indexColor++] = (float) referenceRGB[1];
			colors[indexColor++] = (float) referenceRGB[2];
			colors[indexColor++] = (float) outX;
			colors[indexColor++] = (float) outY;
			colors[indexColor++] = (float) outZ;

			// Store positions
			positions[indexPosition++] = (float) (referenceRGB[0] - 0.5);
			positions[indexPosition++] = (float) (referenceRGB[1] - 0.5);
			positions[indexPosition++] = (float) (referenceRGB[2] - 0.5);
			positions[indexPosition++] = (float) (outX - 0.5);
			positions[indexPosition++] = (float) (outY - 0.5);
			positions[indexPosition++] = (float) (outZ - 0.5);
		}

		// Update preview
		preview.setData(
			positions,
			colors,
			280,
			280
		);

		// Add items
		const double *data = matrix.getData();
		table.addItem(0, 0, data[0], 4);
		table.addItem(0, 1, data[1], 4);
		table.addItem(0, 2, data[2], 4);
		table.addItem(0, 3, data[3], 4);
		table.addItem(1, 0, data[4], 4);
		table.addItem(1, 1, data[5], 4);
		table.addItem(1, 2, data[6], 4);
		table.addItem(1, 3, data[7], 4);
		table.addItem(2, 0, data[8], 4);
		table.addItem(2, 1, data[9], 4);
		table.addItem(2, 2, data[10], 4);
		table.addItem(2, 3, data[11], 4);
	}

}
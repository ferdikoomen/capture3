#include "CameraControlComponent.h"


namespace Capture3
{

	CameraControlComponent::CameraControlComponent(Camera &camera) :
		PanelTabComponent("Camera Control"),
		camera(camera),

		// Layout group
		layoutFocusNear(),
		layoutFocusFar(),

		// Labels
		labelAperture("Aperture"),
		labelShutterSpeed("Shutter Speed"),
		labelIso("Iso"),
		labelRange("Range"),
		labelStep("Step"),
		labelShots("Shots"),
		labelFocusNear("Focus Near"),
		labelFocusFar("Focus Far"),
		labelMergeShots("Merge"),
		labelMergeRange("HDR"),

		// Fields
		inputAperture(),
		inputShutterSpeed(),
		inputIso(),
		inputRange(),
		inputStep(),
		inputShots(),
		inputMergeShots(),
		inputMergeRange(),
		sliderFocusNear(Qt::Horizontal),
		sliderFocusFar(Qt::Horizontal),
		fieldFocusNear(),
		fieldFocusFar(),

		// Buttons
		buttonFocusNearMin("−"),
		buttonFocusNearPlus("+"),
		buttonFocusNearPreview("▸"),
		buttonFocusFarMin("−"),
		buttonFocusFarPlus("+"),
		buttonFocusFarPreview("▸"),
		button("Capture"),

		// Exposure matrix
		group("Exposure Value (EV) / Light Value (LV)"),
		table(),

		// Flow logic
		timer(),
		focus(0),
		blocked(false)
	{

		// Append camera settings
		for (const CameraExposureSettingsItem *item : camera.getExposureSettings().getSettingsAperture()) {
			inputAperture.addItem(item->getLabel());
		}
		for (const CameraExposureSettingsItem *item : camera.getExposureSettings().getSettingsShutterSpeed()) {
			inputShutterSpeed.addItem(item->getLabel());
		}
		for (const CameraExposureSettingsItem *item : camera.getExposureSettings().getSettingsIso()) {
			inputIso.addItem(item->getLabel());
		}
		for (const QString &item : camera.getSettings().getSettingsShots()) {
			inputShots.addItem(item);
		}
		for (const QString &item : camera.getSettings().getSettingsRange()) {
			inputRange.addItem(item);
		}
		for (const QString &item : camera.getSettings().getSettingsStep()) {
			inputStep.addItem(item);
		}
		for (const QString &item : camera.getSettings().getSettingsMergeShots()) {
			inputMergeShots.addItem(item);
		}
		for (const QString &item : camera.getSettings().getSettingsMergeRange()) {
			inputMergeRange.addItem(item);
		}

		// Set default values
		inputAperture.setCurrentIndex(CAMERA_INDEX_APERTURE);
		inputShutterSpeed.setCurrentIndex(CAMERA_INDEX_SHUTTER_SPEED);
		inputIso.setCurrentIndex(CAMERA_INDEX_ISO);
		inputShots.setCurrentIndex(CAMERA_INDEX_SHOTS);
		inputRange.setCurrentIndex(CAMERA_INDEX_RANGE);
		inputStep.setCurrentIndex(CAMERA_INDEX_STEP);
		inputMergeShots.setCurrentIndex(CAMERA_INDEX_MERGE_SHOTS);
		inputMergeRange.setCurrentIndex(CAMERA_INDEX_MERGE_RANGE);

		// Remove nasty focus outlines from spin boxes
		fieldFocusNear.setAttribute(Qt::WA_MacShowFocusRect, false);
		fieldFocusFar.setAttribute(Qt::WA_MacShowFocusRect, false);

		// Set options for focus fields
		sliderFocusNear.setRange(0, CAMERA_SETTING_FOCUS_NEAR);
		sliderFocusFar.setRange(0, CAMERA_SETTING_FOCUS_FAR);
		fieldFocusNear.setRange(0, CAMERA_SETTING_FOCUS_NEAR);
		fieldFocusFar.setRange(0, CAMERA_SETTING_FOCUS_FAR);

		// Small button style
		buttonFocusNearMin.setObjectName("small");
		buttonFocusNearPlus.setObjectName("small");
		buttonFocusNearPreview.setObjectName("small");
		buttonFocusFarMin.setObjectName("small");
		buttonFocusFarPlus.setObjectName("small");
		buttonFocusFarPreview.setObjectName("small");

		// Default table options
		table.verticalHeader()->show();
		table.verticalHeader()->setDefaultSectionSize(18);
		table.horizontalHeader()->setDefaultSectionSize(50);
		table.setColumnCount(camera.getExposureMatrix().getWidth());
		table.setRowCount(camera.getExposureMatrix().getHeight());

		// Set headers and create empty labels
		for (unsigned int y = 0; y < camera.getExposureMatrix().getHeight(); y++) {
			for (unsigned int x = 0; x < camera.getExposureMatrix().getWidth(); x++) {
				table.addLabel(y, x, QString::null);
			}
		}

		// Add items
		addWidget(&labelAperture, 0, 0);
		addWidget(&inputAperture, 1, 0);
		addWidget(&labelShutterSpeed, 0, 1);
		addWidget(&inputShutterSpeed, 1, 1);
		addWidget(&labelIso, 0, 2);
		addWidget(&inputIso, 1, 2);
		addWidget(&labelRange, 2, 0);
		addWidget(&inputRange, 3, 0);
		addWidget(&labelStep, 2, 1);
		addWidget(&inputStep, 3, 1);
		addWidget(&labelShots, 2, 2);
		addWidget(&inputShots, 3, 2);

		group.addWidget(&table);
		addWidget(&group, 4, 0, 1, 4);

		layoutFocusNear.setSpacing(3);
		layoutFocusNear.setMargin(0);
		layoutFocusNear.setAlignment(Qt::AlignTop | Qt::AlignLeft);
		layoutFocusNear.addWidget(&sliderFocusNear);
		layoutFocusNear.addWidget(&fieldFocusNear);
		layoutFocusNear.addWidget(&buttonFocusNearMin);
		layoutFocusNear.addWidget(&buttonFocusNearPlus);
		layoutFocusNear.addWidget(&buttonFocusNearPreview);
		addWidget(&labelFocusNear, 5, 0, 1, 4);
		addLayout(&layoutFocusNear, 6, 0, 1, 4);

		layoutFocusFar.setSpacing(3);
		layoutFocusFar.setMargin(0);
		layoutFocusFar.setAlignment(Qt::AlignTop | Qt::AlignLeft);
		layoutFocusFar.addWidget(&sliderFocusFar);
		layoutFocusFar.addWidget(&fieldFocusFar);
		layoutFocusFar.addWidget(&buttonFocusFarMin);
		layoutFocusFar.addWidget(&buttonFocusFarPlus);
		layoutFocusFar.addWidget(&buttonFocusFarPreview);
		addWidget(&labelFocusFar, 7, 0, 1, 4);
		addLayout(&layoutFocusFar, 8, 0, 1, 4);

		addWidget(&labelMergeShots, 9, 0);
		addWidget(&inputMergeShots, 10, 0);
		addWidget(&labelMergeRange, 9, 1);
		addWidget(&inputMergeRange, 10, 1);
		addWidget(&button, 10, 2);

		// Add some spacing after the button
		setRowMinimumHeight(11, 20);

		// Stretch columns
		setColumnStretch(0, 1);
		setColumnStretch(1, 1);
		setColumnStretch(2, 1);

		// Link signals
		QObject::connect(&inputAperture, &QComboBox::currentTextChanged, this, &CameraControlComponent::inputChanged);
		QObject::connect(&inputShutterSpeed, &QComboBox::currentTextChanged, this, &CameraControlComponent::inputChanged);
		QObject::connect(&inputIso, &QComboBox::currentTextChanged, this, &CameraControlComponent::inputChanged);
		QObject::connect(&inputShots, &QComboBox::currentTextChanged, this, &CameraControlComponent::inputChanged);
		QObject::connect(&inputRange, &QComboBox::currentTextChanged, this, &CameraControlComponent::inputChanged);
		QObject::connect(&inputStep, &QComboBox::currentTextChanged, this, &CameraControlComponent::inputChanged);
		QObject::connect(&table, &QTableWidget::cellClicked, this, &CameraControlComponent::cellClicked);

		// Listen to changes on field
		QObject::connect(&sliderFocusNear, &QSlider::valueChanged, this, [this]() {
			fieldFocusNear.setValue(sliderFocusNear.value());
		});
		QObject::connect(&sliderFocusFar, &QSlider::valueChanged, this, [this]() {
			fieldFocusFar.setValue(sliderFocusFar.value());
		});
		QObject::connect(&fieldFocusNear, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &CameraControlComponent::focusNearChanged);
		QObject::connect(&fieldFocusFar, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &CameraControlComponent::focusFarChanged);
		QObject::connect(&buttonFocusNearPreview, &QPushButton::pressed, this, &CameraControlComponent::focusNearPreview);
		QObject::connect(&buttonFocusFarPreview, &QPushButton::pressed, this, &CameraControlComponent::focusFarPreview);
		QObject::connect(&buttonFocusNearPreview, &QPushButton::released, this, &CameraControlComponent::focusReset);
		QObject::connect(&buttonFocusFarPreview, &QPushButton::released, this, &CameraControlComponent::focusReset);
		QObject::connect(&timer, &QTimer::timeout, this, &CameraControlComponent::focusReset);

		// Link buttons to fields
		QObject::connect(&buttonFocusNearMin, &QPushButton::clicked, this, [this]() {
			int val = QApplication::keyboardModifiers().testFlag(Qt::ShiftModifier) ? 10 : 1;
			fieldFocusNear.setValue(fieldFocusNear.value() - val);
		});
		QObject::connect(&buttonFocusNearPlus, &QPushButton::clicked, this, [this]() {
			int val = QApplication::keyboardModifiers().testFlag(Qt::ShiftModifier) ? 10 : 1;
			fieldFocusNear.setValue(fieldFocusNear.value() + val);
		});
		QObject::connect(&buttonFocusFarMin, &QPushButton::clicked, this, [this]() {
			int val = QApplication::keyboardModifiers().testFlag(Qt::ShiftModifier) ? 10 : 1;
			fieldFocusFar.setValue(fieldFocusFar.value() - val);
		});
		QObject::connect(&buttonFocusFarPlus, &QPushButton::clicked, this, [this]() {
			int val = QApplication::keyboardModifiers().testFlag(Qt::ShiftModifier) ? 10 : 1;
			fieldFocusFar.setValue(fieldFocusFar.value() + val);
		});

		// Update table
		QTimer::singleShot(1, this, &CameraControlComponent::inputChanged);
	}


	CameraControlComponent::~CameraControlComponent()
	{
		QObject::disconnect(&inputAperture, nullptr, nullptr, nullptr);
		QObject::disconnect(&inputShutterSpeed, nullptr, nullptr, nullptr);
		QObject::disconnect(&inputIso, nullptr, nullptr, nullptr);
		QObject::disconnect(&inputShots, nullptr, nullptr, nullptr);
		QObject::disconnect(&inputRange, nullptr, nullptr, nullptr);
		QObject::disconnect(&inputStep, nullptr, nullptr, nullptr);
		QObject::disconnect(&fieldFocusNear, nullptr, nullptr, nullptr);
		QObject::disconnect(&fieldFocusFar, nullptr, nullptr, nullptr);
		QObject::disconnect(&table, nullptr, nullptr, nullptr);
		QObject::disconnect(&buttonFocusNearMin, nullptr, nullptr, nullptr);
		QObject::disconnect(&buttonFocusNearPlus, nullptr, nullptr, nullptr);
		QObject::disconnect(&buttonFocusNearPreview, nullptr, nullptr, nullptr);
		QObject::disconnect(&buttonFocusFarMin, nullptr, nullptr, nullptr);
		QObject::disconnect(&buttonFocusFarPlus, nullptr, nullptr, nullptr);
		QObject::disconnect(&buttonFocusFarPreview, nullptr, nullptr, nullptr);
		QObject::disconnect(&timer, nullptr, nullptr, nullptr);

		timer.stop();
		timer.deleteLater();

		labelAperture.deleteLater();
		labelShutterSpeed.deleteLater();
		labelIso.deleteLater();
		labelRange.deleteLater();
		labelStep.deleteLater();
		labelShots.deleteLater();
		labelFocusNear.deleteLater();
		labelFocusFar.deleteLater();
		labelMergeShots.deleteLater();
		labelMergeRange.deleteLater();
		inputAperture.deleteLater();
		inputShutterSpeed.deleteLater();
		inputIso.deleteLater();
		inputRange.deleteLater();
		inputStep.deleteLater();
		inputShots.deleteLater();
		inputMergeShots.deleteLater();
		inputMergeRange.deleteLater();
		fieldFocusNear.deleteLater();
		fieldFocusFar.deleteLater();
		table.deleteLater();
		group.deleteLater();
		buttonFocusNearMin.deleteLater();
		buttonFocusNearPlus.deleteLater();
		buttonFocusNearPreview.deleteLater();
		buttonFocusFarMin.deleteLater();
		buttonFocusFarPlus.deleteLater();
		buttonFocusFarPreview.deleteLater();
		layoutFocusNear.deleteLater();
		layoutFocusFar.deleteLater();
		button.deleteLater();
	}


	void CameraControlComponent::cellClicked(const int row, const int col)
	{
		// Get position in matrix
		auto x = (unsigned int) col;
		auto y = (unsigned int) row;
		auto z = (unsigned int) inputIso.currentIndex();

		// Fetch item
		const CameraExposureMatrixItem *item = camera.getExposureMatrix().at(x, y, z);
		if (item != nullptr) {

			// Update combobox
			blocked = true;
			inputAperture.setCurrentIndex(item->getAperture()->getIndex());
			inputShutterSpeed.setCurrentIndex(item->getShutterSpeed()->getIndex());
			inputIso.setCurrentIndex(item->getIso()->getIndex());
			blocked = false;

			// Update table
			update(false);
		}
	}


	void CameraControlComponent::inputChanged()
	{
		update(true);
	}


	void CameraControlComponent::update(const bool scroll)
	{
		if (!blocked) {

			// Get indexes
			const auto indexAperture = (unsigned int) inputAperture.currentIndex();
			const auto indexShutterSpeed = (unsigned int) inputShutterSpeed.currentIndex();
			const auto indexIso = (unsigned int) inputIso.currentIndex();
			const auto indexRange = (unsigned int) inputRange.currentIndex() + 1;
			const auto indexStep = (unsigned int) inputStep.currentIndex() + 1;

			// Update table
			// Get current settings
			const CameraExposureSettingsItem *aperture = camera.getExposureSettings().getSettingsAperture(indexAperture);
			const CameraExposureSettingsItem *shutterSpeed = camera.getExposureSettings().getSettingsShutterSpeed(indexShutterSpeed);
			const CameraExposureSettingsItem *iso = camera.getExposureSettings().getSettingsIso(indexIso);

			// Get the exposure value index
			const unsigned int index = camera.getExposureMatrix().getIndex(
				aperture,
				shutterSpeed,
				iso
			);

			// Rows and columns
			const unsigned int matrixWidth = camera.getExposureMatrix().getWidth();
			const unsigned int matrixHeight = camera.getExposureMatrix().getHeight();

			// Fetch headers
			for (unsigned int i = 0; i < matrixWidth; i++) {
				table.setHorizontalHeader(i, camera.getExposureMatrix().getHeaderHorizontal(i));
			}
			for (unsigned int i = 0; i < matrixHeight; i++) {
				table.setVerticalHeader(i, camera.getExposureMatrix().getHeaderVertical(i, indexIso));
			}

			// Iterate over the matrix
			for (unsigned int x = 0; x < matrixWidth; x++) {
				for (unsigned int y = 0; y < matrixHeight; y++) {

					// Fetch label
					QLabel *label = table.getLabel(y, x);
					QString labelClass = "";
					QString labelText = "";

					// Fetch item and highlight row and column
					const CameraExposureMatrixItem *item = camera.getExposureMatrix().at(x, y, indexIso);
					if (item != nullptr) {
						labelText = item->getShutterSpeed()->getLabel();
						if (item->getIndex() == index || item->getAperture()->getIndex() == indexAperture) {
							labelClass = "highlight";
						}
					}

					// Set text
					if (label->text() != labelText) {
						label->setText(labelText);
					}

					// Set styling
					if (label->objectName() != labelClass) {
						label->setObjectName(labelClass);
						style()->unpolish(label);
						style()->polish(label);
					}
				}
			}

			// Highlight current item
			QLabel *current = table.getLabel(index, indexAperture);
			current->setObjectName("focus");
			style()->unpolish(current);
			style()->polish(current);

			// Show range for HDR capture
			for (unsigned int i = 1; i < indexRange; i++) {
				QLabel *labelA = table.getLabel(index - (i * indexStep), indexAperture);
				QLabel *labelB = table.getLabel(index + (i * indexStep), indexAperture);
				labelA->setObjectName(labelA->text().isEmpty() ? "error" : "focus");
				labelB->setObjectName(labelB->text().isEmpty() ? "error" : "focus");
				style()->unpolish(labelA);
				style()->unpolish(labelB);
				style()->polish(labelA);
				style()->polish(labelB);
			}

			// Center current cell
			if (scroll) {

				// Get column count
				const auto offsetRow = (int) (table.height() / 18 / 2 - 0.5);
				const auto offsetCol = (int) (table.width() / 50 / 2 - 0.5);

				// Calculate final position
				unsigned int row = index + offsetRow;
				unsigned int col = indexAperture + offsetCol;
				row = row > matrixHeight - 1 ? matrixHeight - 1 : row;
				col = col > matrixWidth - 1 ? matrixWidth - 1 : col;

				// Scroll to cell
				table.setCurrentCell(0, 0);
				table.setCurrentCell(row, col);
			}
		}
	}


	void CameraControlComponent::focusNearPreview()
	{
		const int value = -fieldFocusNear.value();
		camera.moveFocus(value - focus);
		focus = value;
	}


	void CameraControlComponent::focusFarPreview()
	{
		const int value = fieldFocusFar.value();
		camera.moveFocus(value - focus);
		focus = value;
	}


	void CameraControlComponent::focusNearChanged()
	{
		// Show preview, reset after 2 seconds
		sliderFocusNear.setValue(fieldFocusNear.value());
		timer.stop();
		timer.start(2000);
		focusNearPreview();
	}


	void CameraControlComponent::focusFarChanged()
	{
		// Show preview, reset after 2 seconds
		sliderFocusFar.setValue(fieldFocusFar.value());
		timer.stop();
		timer.start(2000);
		focusFarPreview();
	}


	void CameraControlComponent::focusReset()
	{
		// Reset focus
		timer.stop();
		camera.moveFocus(-focus);
		focus = 0;
	}


	const int CameraControlComponent::getFocusNear() const
	{
		return fieldFocusNear.value();
	}


	const int CameraControlComponent::getFocusFar() const
	{
		return fieldFocusFar.value();
	}


	const unsigned int CameraControlComponent::getIndexAperture() const
	{
		return (unsigned int) inputAperture.currentIndex();
	}


	const unsigned int CameraControlComponent::getIndexShutterSpeed() const
	{
		return (unsigned int) inputShutterSpeed.currentIndex();
	}


	const unsigned int CameraControlComponent::getIndexIso() const
	{
		return (unsigned int) inputIso.currentIndex();
	}


	const unsigned int CameraControlComponent::getIndexRange() const
	{
		return (unsigned int) inputRange.currentIndex();
	}


	const unsigned int CameraControlComponent::getIndexStep() const
	{
		return (unsigned int) inputStep.currentIndex();
	}


	const unsigned int CameraControlComponent::getIndexShots() const
	{
		return (unsigned int) inputShots.currentIndex();
	}


	const unsigned int CameraControlComponent::getIndexMergeShots() const
	{
		return (unsigned int) inputMergeShots.currentIndex();
	}


	const unsigned int CameraControlComponent::getIndexMergeRange() const
	{
		return (unsigned int) inputMergeRange.currentIndex();
	}


	const QPushButton &CameraControlComponent::getButton() const
	{
		return button;
	}
}
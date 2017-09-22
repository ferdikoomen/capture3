#ifndef CAPTURE3_CAMERA_CONTROL_COMPONENT_H
#define CAPTURE3_CAMERA_CONTROL_COMPONENT_H


#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtCore/QTimer>

#include "../panelTab/PanelTabComponent.h"
#include "../panelGroup/PanelGroupComponent.h"
#include "../table/TableComponent.h"
#include "../../../engine/objects/camera/Camera.h"


namespace Capture3
{
	class CameraControlComponent final : public PanelTabComponent
	{
		Q_OBJECT

		public:
			CameraControlComponent(Camera &camera);

			virtual ~CameraControlComponent();

			const unsigned int getIndexAperture() const;

			const unsigned int getIndexShutterSpeed() const;

			const unsigned int getIndexIso() const;

			const unsigned int getIndexRange() const;

			const unsigned int getIndexStep() const;

			const unsigned int getIndexShots() const;

			const unsigned int getIndexMergeShots() const;

			const unsigned int getIndexMergeRange() const;

			const int getFocusNear() const;

			const int getFocusFar() const;

			const QPushButton &getButton() const;

		private slots:

			void cellClicked(const int row, const int col);

			void inputChanged();

			void focusNearPreview();

			void focusFarPreview();

			void focusNearChanged();

			void focusFarChanged();

			void focusReset();

		private:
			void update(const bool scroll);

			Camera &camera;
			QHBoxLayout layoutFocusNear;
			QHBoxLayout layoutFocusFar;
			QLabel labelAperture;
			QLabel labelShutterSpeed;
			QLabel labelIso;
			QLabel labelRange;
			QLabel labelStep;
			QLabel labelShots;
			QLabel labelFocusNear;
			QLabel labelFocusFar;
			QLabel labelMergeShots;
			QLabel labelMergeRange;
			QComboBox inputAperture;
			QComboBox inputShutterSpeed;
			QComboBox inputIso;
			QComboBox inputRange;
			QComboBox inputStep;
			QComboBox inputShots;
			QComboBox inputMergeShots;
			QComboBox inputMergeRange;
			PanelGroupComponent group;
			TableComponent table;

			QSlider sliderFocusNear;
			QSlider sliderFocusFar;
			QSpinBox fieldFocusNear;
			QSpinBox fieldFocusFar;
			QPushButton buttonFocusNearMin;
			QPushButton buttonFocusNearPlus;
			QPushButton buttonFocusNearPreview;
			QPushButton buttonFocusFarMin;
			QPushButton buttonFocusFarPlus;
			QPushButton buttonFocusFarPreview;
			QPushButton button;
			QTimer timer;
			int focus;
			bool blocked;
	};
}


#endif // CAPTURE3_CAMERA_CONTROL_COMPONENT_H

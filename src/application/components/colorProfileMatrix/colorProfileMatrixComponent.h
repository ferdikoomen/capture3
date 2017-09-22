#ifndef CAPTURE3_COLOR_PROFILE_MATRIX_COMPONENT_H
#define CAPTURE3_COLOR_PROFILE_MATRIX_COMPONENT_H


#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSlider>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtCore/QTimer>


#include "../panelTab/PanelTabComponent.h"
#include "../panelGroup/PanelGroupComponent.h"
#include "../table/TableComponent.h"
#include "../render/RenderComponent.h"
#include "../../../engine/objects/colorMatrix/ColorMatrix.h"
#include "../../../engine/objects/colorChart/ColorChart.h"


namespace Capture3
{
	class ColorProfileMatrixComponent final : public PanelTabComponent
	{
		Q_OBJECT

		public:
			ColorProfileMatrixComponent();

			virtual ~ColorProfileMatrixComponent();

			void show(
				const ColorChart *colorChartReference,
				const ColorChart *colorChartDetected
			);

		private slots:

			void onFieldChanged();

			void onSliderChanged();

		private:
			void draw();

			PanelGroupComponent groupPreview;
			PanelGroupComponent groupTable;
			PanelGroupComponent groupRow1;
			PanelGroupComponent groupRow2;
			PanelGroupComponent groupRow3;
			RenderComponent preview;
			TableComponent table;
			QSlider sliderM11;
			QSlider sliderM12;
			QSlider sliderM13;
			QSlider sliderM14;
			QSlider sliderM21;
			QSlider sliderM22;
			QSlider sliderM23;
			QSlider sliderM24;
			QSlider sliderM31;
			QSlider sliderM32;
			QSlider sliderM33;
			QSlider sliderM34;
			QSpinBox fieldM11;
			QSpinBox fieldM12;
			QSpinBox fieldM13;
			QSpinBox fieldM14;
			QSpinBox fieldM21;
			QSpinBox fieldM22;
			QSpinBox fieldM23;
			QSpinBox fieldM24;
			QSpinBox fieldM31;
			QSpinBox fieldM32;
			QSpinBox fieldM33;
			QSpinBox fieldM34;
			ColorMatrix matrix;
			std::vector<float> positions;
			std::vector<float> colors;
			const ColorChart *colorChartReference;
			const ColorChart *colorChartDetected;
	};
}


#endif // CAPTURE3_COLOR_PROFILE_MATRIX_COMPONENT_H

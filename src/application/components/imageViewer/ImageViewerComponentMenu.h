#ifndef CAPTURE3_IMAGE_VIEWER_COMPONENT_MENU_H
#define CAPTURE3_IMAGE_VIEWER_COMPONENT_MENU_H


#include <cmath>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QButtonGroup>


#include "../scroll/ScrollComponent.h"
#include "../panelGroup/PanelGroupComponent.h"
#include "../graphic/GraphicComponent.h"
#include "../../../utils/ColorUtils.h"


namespace Capture3
{
	class ImageViewerComponentMenu final : public ScrollComponent
	{
		Q_OBJECT

		public:
			ImageViewerComponentMenu();

			virtual ~ImageViewerComponentMenu();

			void setColor(
				const double rgb_r, const double rgb_g, const double rgb_b,
				const double hsb_h, const double hsb_s, const double hsb_b,
				const double xyz_x, const double xyz_y, const double xyz_z,
				const double xyv_x, const double xyv_y, const double xyv_v,
				const double lab_l, const double lab_a, const double lab_b
			);

			const QRadioButton &getButtonRGB() const;

			const QRadioButton &getButtonRGB_R() const;

			const QRadioButton &getButtonRGB_G() const;

			const QRadioButton &getButtonRGB_B() const;

			const QRadioButton &getButtonHSB() const;

			const QRadioButton &getButtonHSB_H() const;

			const QRadioButton &getButtonHSB_S() const;

			const QRadioButton &getButtonHSB_B() const;

			const QRadioButton &getButtonXYZ() const;

			const QRadioButton &getButtonXYZ_X() const;

			const QRadioButton &getButtonXYZ_Y() const;

			const QRadioButton &getButtonXYZ_Z() const;

			const QRadioButton &getButtonXYV() const;

			const QRadioButton &getButtonXYV_X() const;

			const QRadioButton &getButtonXYV_Y() const;

			const QRadioButton &getButtonXYV_V() const;

			const QRadioButton &getButtonLAB() const;

			const QRadioButton &getButtonLAB_L() const;

			const QRadioButton &getButtonLAB_A() const;

			const QRadioButton &getButtonLAB_B() const;

			const QCheckBox &getCheckboxShadowClipping() const;

			const QCheckBox &getCheckboxHighlightClipping() const;

		private:
			PanelGroupComponent buttonGroupRGB;
			PanelGroupComponent buttonGroupHSB;
			PanelGroupComponent buttonGroupXYZ;
			PanelGroupComponent buttonGroupXYV;
			PanelGroupComponent buttonGroupLAB;
			QRadioButton buttonRGB;
			QRadioButton buttonRGB_R;
			QRadioButton buttonRGB_G;
			QRadioButton buttonRGB_B;
			QRadioButton buttonHSB;
			QRadioButton buttonHSB_H;
			QRadioButton buttonHSB_S;
			QRadioButton buttonHSB_B;
			QRadioButton buttonXYZ;
			QRadioButton buttonXYZ_X;
			QRadioButton buttonXYZ_Y;
			QRadioButton buttonXYZ_Z;
			QRadioButton buttonXYV;
			QRadioButton buttonXYV_X;
			QRadioButton buttonXYV_Y;
			QRadioButton buttonXYV_V;
			QRadioButton buttonLAB;
			QRadioButton buttonLAB_L;
			QRadioButton buttonLAB_A;
			QRadioButton buttonLAB_B;
			QButtonGroup buttonGroup;
			PanelGroupComponent checkboxGroup;
			QCheckBox checkboxShadowClipping;
			QCheckBox checkboxHighlightClipping;
			PanelGroupComponent fieldGroupColor;
			PanelGroupComponent fieldGroupRGB;
			PanelGroupComponent fieldGroupHSB;
			PanelGroupComponent fieldGroupXYZ;
			PanelGroupComponent fieldGroupXYV;
			PanelGroupComponent fieldGroupLAB;
			GraphicComponent color;
			QLineEdit fieldRGB_R;
			QLineEdit fieldRGB_G;
			QLineEdit fieldRGB_B;
			QLineEdit fieldHSB_H;
			QLineEdit fieldHSB_S;
			QLineEdit fieldHSB_B;
			QLineEdit fieldXYZ_X;
			QLineEdit fieldXYZ_Y;
			QLineEdit fieldXYZ_Z;
			QLineEdit fieldXYV_X;
			QLineEdit fieldXYV_Y;
			QLineEdit fieldXYV_V;
			QLineEdit fieldLAB_L;
			QLineEdit fieldLAB_A;
			QLineEdit fieldLAB_B;
	};
}


#endif // CAPTURE3_IMAGE_VIEWER_COMPONENT_MENU_H

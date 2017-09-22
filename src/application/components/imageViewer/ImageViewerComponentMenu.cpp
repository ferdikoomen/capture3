#include "ImageViewerComponentMenu.h"


namespace Capture3
{

	ImageViewerComponentMenu::ImageViewerComponentMenu() :
		ScrollComponent(),

		// Layers
		buttonGroupRGB("Channels - RGB"),
		buttonGroupHSB("Channels - HSB"),
		buttonGroupXYZ("Channels - XYZ"),
		buttonGroupXYV("Channels - xyY"),
		buttonGroupLAB("Channels - LAB"),
		buttonRGB("RGB"),
		buttonRGB_R("R"),
		buttonRGB_G("G"),
		buttonRGB_B("B"),
		buttonHSB("HSB"),
		buttonHSB_H("H"),
		buttonHSB_S("S"),
		buttonHSB_B("B"),
		buttonXYZ("XYZ"),
		buttonXYZ_X("X"),
		buttonXYZ_Y("Y"),
		buttonXYZ_Z("Z"),
		buttonXYV("xyY"),
		buttonXYV_X("x"),
		buttonXYV_Y("y"),
		buttonXYV_V("Y"),
		buttonLAB("LAB"),
		buttonLAB_L("L"),
		buttonLAB_A("A"),
		buttonLAB_B("B"),
		buttonGroup(),

		// Checkbox with clipping options
		checkboxGroup("Show Clipping"),
		checkboxShadowClipping("Shadow (Blue)"),
		checkboxHighlightClipping("Highlight (Red)"),

		// Colors
		fieldGroupColor("Color"),
		fieldGroupRGB("Color - RGB"),
		fieldGroupHSB("Color - HSB"),
		fieldGroupXYZ("Color - XYZ"),
		fieldGroupXYV("Color - xyY"),
		fieldGroupLAB("Color - LAB"),

		// Color preview
		color(1, 1),

		// Fields
		fieldRGB_R("0"),
		fieldRGB_G("0"),
		fieldRGB_B("0"),
		fieldHSB_H("0"),
		fieldHSB_S("0"),
		fieldHSB_B("0"),
		fieldXYZ_X("0"),
		fieldXYZ_Y("0"),
		fieldXYZ_Z("0"),
		fieldXYV_X("0"),
		fieldXYV_Y("0"),
		fieldXYV_V("0"),
		fieldLAB_L("0"),
		fieldLAB_A("0"),
		fieldLAB_B("0")
	{
		// Set color value fields as read only
		fieldRGB_R.setReadOnly(true);
		fieldRGB_G.setReadOnly(true);
		fieldRGB_B.setReadOnly(true);
		fieldHSB_H.setReadOnly(true);
		fieldHSB_S.setReadOnly(true);
		fieldHSB_B.setReadOnly(true);
		fieldXYZ_X.setReadOnly(true);
		fieldXYZ_Y.setReadOnly(true);
		fieldXYZ_Z.setReadOnly(true);
		fieldXYV_X.setReadOnly(true);
		fieldXYV_Y.setReadOnly(true);
		fieldXYV_V.setReadOnly(true);
		fieldLAB_L.setReadOnly(true);
		fieldLAB_A.setReadOnly(true);
		fieldLAB_B.setReadOnly(true);

		// Fix: Make sure the layer buttons stretch out
		buttonRGB.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
		buttonRGB_R.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
		buttonRGB_G.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
		buttonRGB_B.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
		buttonHSB.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
		buttonHSB_H.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
		buttonHSB_S.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
		buttonHSB_B.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
		buttonXYZ.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
		buttonXYZ_X.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
		buttonXYZ_Y.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
		buttonXYZ_Z.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
		buttonXYV.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
		buttonXYV_X.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
		buttonXYV_Y.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
		buttonXYV_V.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
		buttonLAB.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
		buttonLAB_L.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
		buttonLAB_A.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
		buttonLAB_B.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

		// Add items in radio button group
		buttonGroup.addButton(&buttonRGB);
		buttonGroup.addButton(&buttonRGB_R);
		buttonGroup.addButton(&buttonRGB_G);
		buttonGroup.addButton(&buttonRGB_B);
		buttonGroup.addButton(&buttonHSB);
		buttonGroup.addButton(&buttonHSB_H);
		buttonGroup.addButton(&buttonHSB_S);
		buttonGroup.addButton(&buttonHSB_B);
		buttonGroup.addButton(&buttonXYZ);
		buttonGroup.addButton(&buttonXYZ_X);
		buttonGroup.addButton(&buttonXYZ_Y);
		buttonGroup.addButton(&buttonXYZ_Z);
		buttonGroup.addButton(&buttonXYV);
		buttonGroup.addButton(&buttonXYV_X);
		buttonGroup.addButton(&buttonXYV_Y);
		buttonGroup.addButton(&buttonXYV_V);
		buttonGroup.addButton(&buttonLAB);
		buttonGroup.addButton(&buttonLAB_L);
		buttonGroup.addButton(&buttonLAB_A);
		buttonGroup.addButton(&buttonLAB_B);
		buttonRGB.setChecked(true);


		// Add items
		buttonGroupRGB.setSpacing(1);
		buttonGroupHSB.setSpacing(1);
		buttonGroupXYZ.setSpacing(1);
		buttonGroupXYV.setSpacing(1);
		buttonGroupLAB.setSpacing(1);
		buttonGroupRGB.addWidget(&buttonRGB);
		buttonGroupRGB.addWidget(&buttonRGB_R);
		buttonGroupRGB.addWidget(&buttonRGB_G);
		buttonGroupRGB.addWidget(&buttonRGB_B);
		buttonGroupHSB.addWidget(&buttonHSB);
		buttonGroupHSB.addWidget(&buttonHSB_H);
		buttonGroupHSB.addWidget(&buttonHSB_S);
		buttonGroupHSB.addWidget(&buttonHSB_B);
		buttonGroupXYZ.addWidget(&buttonXYZ);
		buttonGroupXYZ.addWidget(&buttonXYZ_X);
		buttonGroupXYZ.addWidget(&buttonXYZ_Y);
		buttonGroupXYZ.addWidget(&buttonXYZ_Z);
		buttonGroupXYV.addWidget(&buttonXYV);
		buttonGroupXYV.addWidget(&buttonXYV_X);
		buttonGroupXYV.addWidget(&buttonXYV_Y);
		buttonGroupXYV.addWidget(&buttonXYV_V);
		buttonGroupLAB.addWidget(&buttonLAB);
		buttonGroupLAB.addWidget(&buttonLAB_L);
		buttonGroupLAB.addWidget(&buttonLAB_A);
		buttonGroupLAB.addWidget(&buttonLAB_B);

		// Add checkboxes
		checkboxShadowClipping.setChecked(true);
		checkboxHighlightClipping.setChecked(true);
		checkboxGroup.addWidget(&checkboxShadowClipping);
		checkboxGroup.addWidget(&checkboxHighlightClipping);

		// Add color preview item
		color.setObjectName("color");
		color.setFocusPolicy(Qt::NoFocus);
		fieldGroupColor.addWidget(&color);

		// Add items
		fieldGroupRGB.setSpacing(1);
		fieldGroupHSB.setSpacing(1);
		fieldGroupXYZ.setSpacing(1);
		fieldGroupXYV.setSpacing(1);
		fieldGroupLAB.setSpacing(1);
		fieldGroupRGB.addWidget(&fieldRGB_R);
		fieldGroupRGB.addWidget(&fieldRGB_G);
		fieldGroupRGB.addWidget(&fieldRGB_B);
		fieldGroupHSB.addWidget(&fieldHSB_H);
		fieldGroupHSB.addWidget(&fieldHSB_S);
		fieldGroupHSB.addWidget(&fieldHSB_B);
		fieldGroupXYZ.addWidget(&fieldXYZ_X);
		fieldGroupXYZ.addWidget(&fieldXYZ_Y);
		fieldGroupXYZ.addWidget(&fieldXYZ_Z);
		fieldGroupXYV.addWidget(&fieldXYV_X);
		fieldGroupXYV.addWidget(&fieldXYV_Y);
		fieldGroupXYV.addWidget(&fieldXYV_V);
		fieldGroupLAB.addWidget(&fieldLAB_L);
		fieldGroupLAB.addWidget(&fieldLAB_A);
		fieldGroupLAB.addWidget(&fieldLAB_B);

		// Add items
		addWidget(&buttonGroupRGB);
		addWidget(&buttonGroupHSB);
		addWidget(&buttonGroupXYZ);
		addWidget(&buttonGroupXYV);
		addWidget(&buttonGroupLAB);
		addWidget(&checkboxGroup);
		addWidget(&fieldGroupColor);
		addWidget(&fieldGroupRGB);
		addWidget(&fieldGroupHSB);
		addWidget(&fieldGroupXYZ);
		addWidget(&fieldGroupXYV);
		addWidget(&fieldGroupLAB);
	}


	ImageViewerComponentMenu::~ImageViewerComponentMenu()
	{
		buttonRGB.deleteLater();
		buttonRGB_R.deleteLater();
		buttonRGB_G.deleteLater();
		buttonRGB_B.deleteLater();
		buttonHSB.deleteLater();
		buttonHSB_H.deleteLater();
		buttonHSB_S.deleteLater();
		buttonHSB_B.deleteLater();
		buttonXYZ.deleteLater();
		buttonXYZ_X.deleteLater();
		buttonXYZ_Y.deleteLater();
		buttonXYZ_Z.deleteLater();
		buttonXYV.deleteLater();
		buttonXYV_X.deleteLater();
		buttonXYV_Y.deleteLater();
		buttonXYV_V.deleteLater();
		buttonLAB.deleteLater();
		buttonLAB_L.deleteLater();
		buttonLAB_A.deleteLater();
		buttonLAB_B.deleteLater();
		buttonGroup.deleteLater();
		buttonGroupRGB.deleteLater();
		buttonGroupHSB.deleteLater();
		buttonGroupXYZ.deleteLater();
		buttonGroupXYV.deleteLater();
		buttonGroupLAB.deleteLater();
		color.deleteLater();
		fieldRGB_R.deleteLater();
		fieldRGB_G.deleteLater();
		fieldRGB_B.deleteLater();
		fieldHSB_H.deleteLater();
		fieldHSB_S.deleteLater();
		fieldHSB_B.deleteLater();
		fieldXYZ_X.deleteLater();
		fieldXYZ_Y.deleteLater();
		fieldXYZ_Z.deleteLater();
		fieldXYV_X.deleteLater();
		fieldXYV_Y.deleteLater();
		fieldXYV_V.deleteLater();
		fieldLAB_L.deleteLater();
		fieldLAB_A.deleteLater();
		fieldLAB_B.deleteLater();
		checkboxShadowClipping.deleteLater();
		checkboxHighlightClipping.deleteLater();
		checkboxGroup.deleteLater();
		fieldGroupColor.deleteLater();
		fieldGroupRGB.deleteLater();
		fieldGroupHSB.deleteLater();
		fieldGroupXYZ.deleteLater();
		fieldGroupXYV.deleteLater();
		fieldGroupLAB.deleteLater();
	}


	void ImageViewerComponentMenu::setColor(
		const double rgb_r, const double rgb_g, const double rgb_b,
		const double hsb_h, const double hsb_s, const double hsb_b,
		const double xyz_x, const double xyz_y, const double xyz_z,
		const double xyv_x, const double xyv_y, const double xyv_v,
		const double lab_l, const double lab_a, const double lab_b
	)
	{
		// Get color
		const unsigned int r = to8Bit(rgb_r);
		const unsigned int g = to8Bit(rgb_g);
		const unsigned int b = to8Bit(rgb_b);

		fieldRGB_R.setText(QString::number((int) std::round(rgb_r * 255)) + " / " + QString::number(rgb_r, 'f', 6));
		fieldRGB_G.setText(QString::number((int) std::round(rgb_g * 255)) + " / " + QString::number(rgb_g, 'f', 6));
		fieldRGB_B.setText(QString::number((int) std::round(rgb_b * 255)) + " / " + QString::number(rgb_b, 'f', 6));
		fieldHSB_H.setText(QString::number((int) std::round(hsb_h * 360)) + " / " + QString::number(hsb_h, 'f', 6));
		fieldHSB_S.setText(QString::number((int) std::round(hsb_s * 100)) + " / " + QString::number(hsb_s, 'f', 6));
		fieldHSB_B.setText(QString::number((int) std::round(hsb_b * 100)) + " / " + QString::number(hsb_b, 'f', 6));
		fieldXYZ_X.setText(QString::number(xyz_x, 'f', 6));
		fieldXYZ_Y.setText(QString::number(xyz_y, 'f', 6));
		fieldXYZ_Z.setText(QString::number(xyz_z, 'f', 6));
		fieldXYV_X.setText(QString::number(xyv_x, 'f', 6));
		fieldXYV_Y.setText(QString::number(xyv_y, 'f', 6));
		fieldXYV_V.setText(QString::number(xyv_v, 'f', 6));
		fieldLAB_L.setText(QString::number((lab_l * 100), 'f', 6));
		fieldLAB_A.setText(QString::number((lab_a * 256.0) - 128.0, 'f', 6));
		fieldLAB_B.setText(QString::number((lab_b * 256.0) - 128.0, 'f', 6));

		// Update preview
		color.setBackgroundColor(r, g, b);
		color.redraw();
	}


	const QRadioButton &ImageViewerComponentMenu::getButtonRGB() const
	{
		return buttonRGB;
	}


	const QRadioButton &ImageViewerComponentMenu::getButtonRGB_R() const
	{
		return buttonRGB_R;
	}


	const QRadioButton &ImageViewerComponentMenu::getButtonRGB_G() const
	{
		return buttonRGB_G;
	}


	const QRadioButton &ImageViewerComponentMenu::getButtonRGB_B() const
	{
		return buttonRGB_B;
	}


	const QRadioButton &ImageViewerComponentMenu::getButtonHSB() const
	{
		return buttonHSB;
	}


	const QRadioButton &ImageViewerComponentMenu::getButtonHSB_H() const
	{
		return buttonHSB_H;
	}


	const QRadioButton &ImageViewerComponentMenu::getButtonHSB_S() const
	{
		return buttonHSB_S;
	}


	const QRadioButton &ImageViewerComponentMenu::getButtonHSB_B() const
	{
		return buttonHSB_B;
	}


	const QRadioButton &ImageViewerComponentMenu::getButtonLAB() const
	{
		return buttonLAB;
	}


	const QRadioButton &ImageViewerComponentMenu::getButtonXYZ() const
	{
		return buttonXYZ;
	}


	const QRadioButton &ImageViewerComponentMenu::getButtonXYZ_X() const
	{
		return buttonXYZ_X;
	}


	const QRadioButton &ImageViewerComponentMenu::getButtonXYZ_Y() const
	{
		return buttonXYZ_Y;
	}


	const QRadioButton &ImageViewerComponentMenu::getButtonXYZ_Z() const
	{
		return buttonXYZ_Z;
	}


	const QRadioButton &ImageViewerComponentMenu::getButtonXYV() const
	{
		return buttonXYV;
	}


	const QRadioButton &ImageViewerComponentMenu::getButtonXYV_X() const
	{
		return buttonXYV_X;
	}


	const QRadioButton &ImageViewerComponentMenu::getButtonXYV_Y() const
	{
		return buttonXYV_Y;
	}


	const QRadioButton &ImageViewerComponentMenu::getButtonXYV_V() const
	{
		return buttonXYV_V;
	}


	const QRadioButton &ImageViewerComponentMenu::getButtonLAB_L() const
	{
		return buttonLAB_L;
	}


	const QRadioButton &ImageViewerComponentMenu::getButtonLAB_A() const
	{
		return buttonLAB_A;
	}


	const QRadioButton &ImageViewerComponentMenu::getButtonLAB_B() const
	{
		return buttonLAB_B;
	}


	const QCheckBox &ImageViewerComponentMenu::getCheckboxShadowClipping() const
	{
		return checkboxShadowClipping;
	}


	const QCheckBox &ImageViewerComponentMenu::getCheckboxHighlightClipping() const
	{
		return checkboxHighlightClipping;
	}

}
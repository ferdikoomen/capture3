#include "ColorProfileCurvesComponent.h"


namespace Capture3
{

	ColorProfileCurvesComponent::ColorProfileCurvesComponent() :
		PanelTabComponent("Color Profile Curves"),
		groupRGB("Color Profile Curve - RGB"),
		groupHSB("Color Profile Curve - HSB"),
		groupXYZ("Color Profile Curve - XYZ"),
		groupXYV("Color Profile Curve - xyY"),
		groupLAB("Color Profile Curve - LAB"),
		itemRGB_R(),
		itemRGB_G(),
		itemRGB_B(),
		itemHSB_H(),
		itemHSB_S(),
		itemHSB_B(),
		itemXYZ_X(),
		itemXYZ_Y(),
		itemXYZ_Z(),
		itemXYV_X(),
		itemXYV_Y(),
		itemXYV_V(),
		itemLAB_L(),
		itemLAB_A(),
		itemLAB_B()
	{
		// Add items
		groupRGB.addWidget(&itemRGB_R, 0, 0);
		groupRGB.addWidget(&itemRGB_G, 0, 1);
		groupRGB.addWidget(&itemRGB_B, 0, 2);
		groupHSB.addWidget(&itemHSB_H, 0, 0);
		groupHSB.addWidget(&itemHSB_S, 0, 1);
		groupHSB.addWidget(&itemHSB_B, 0, 2);
		groupXYZ.addWidget(&itemXYZ_X, 0, 0);
		groupXYZ.addWidget(&itemXYZ_Y, 0, 1);
		groupXYZ.addWidget(&itemXYZ_Z, 0, 2);
		groupXYV.addWidget(&itemXYV_X, 0, 0);
		groupXYV.addWidget(&itemXYV_Y, 0, 1);
		groupXYV.addWidget(&itemXYV_V, 0, 2);
		groupLAB.addWidget(&itemLAB_L, 0, 0);
		groupLAB.addWidget(&itemLAB_A, 0, 1);
		groupLAB.addWidget(&itemLAB_B, 0, 2);
		addWidget(&groupRGB);
		addWidget(&groupHSB);
		addWidget(&groupXYZ);
		addWidget(&groupXYV);
		addWidget(&groupLAB);

		groupRGB.setColumnStretch(0, 1);
		groupRGB.setColumnStretch(1, 1);
		groupRGB.setColumnStretch(2, 1);
		groupHSB.setColumnStretch(0, 1);
		groupHSB.setColumnStretch(1, 1);
		groupHSB.setColumnStretch(2, 1);
		groupXYZ.setColumnStretch(0, 1);
		groupXYZ.setColumnStretch(1, 1);
		groupXYZ.setColumnStretch(2, 1);
		groupXYV.setColumnStretch(0, 1);
		groupXYV.setColumnStretch(1, 1);
		groupXYV.setColumnStretch(2, 1);
		groupLAB.setColumnStretch(0, 1);
		groupLAB.setColumnStretch(1, 1);
		groupLAB.setColumnStretch(2, 1);
	}


	ColorProfileCurvesComponent::~ColorProfileCurvesComponent()
	{
		itemRGB_R.deleteLater();
		itemRGB_G.deleteLater();
		itemRGB_B.deleteLater();
		itemHSB_H.deleteLater();
		itemHSB_S.deleteLater();
		itemHSB_B.deleteLater();
		itemXYZ_X.deleteLater();
		itemXYZ_Y.deleteLater();
		itemXYZ_Z.deleteLater();
		itemXYV_X.deleteLater();
		itemXYV_Y.deleteLater();
		itemXYV_V.deleteLater();
		itemLAB_L.deleteLater();
		itemLAB_A.deleteLater();
		itemLAB_B.deleteLater();
		groupRGB.deleteLater();
		groupHSB.deleteLater();
		groupXYZ.deleteLater();
		groupXYV.deleteLater();
		groupLAB.deleteLater();
	}


	void ColorProfileCurvesComponent::show(const ColorProfile *colorProfile)
	{
		itemRGB_R.show(colorProfile->getCurvesRGB().getCurveX());
		itemRGB_G.show(colorProfile->getCurvesRGB().getCurveY());
		itemRGB_B.show(colorProfile->getCurvesRGB().getCurveZ());
		itemHSB_H.show(colorProfile->getCurvesHSB().getCurveX());
		itemHSB_S.show(colorProfile->getCurvesHSB().getCurveY());
		itemHSB_B.show(colorProfile->getCurvesHSB().getCurveZ());
		itemXYZ_X.show(colorProfile->getCurvesXYZ().getCurveX());
		itemXYZ_Y.show(colorProfile->getCurvesXYZ().getCurveY());
		itemXYZ_Z.show(colorProfile->getCurvesXYZ().getCurveZ());
		itemXYV_X.show(colorProfile->getCurvesXYV().getCurveX());
		itemXYV_Y.show(colorProfile->getCurvesXYV().getCurveY());
		itemXYV_V.show(colorProfile->getCurvesXYV().getCurveZ());
		itemLAB_L.show(colorProfile->getCurvesLAB().getCurveX());
		itemLAB_A.show(colorProfile->getCurvesLAB().getCurveY());
		itemLAB_B.show(colorProfile->getCurvesLAB().getCurveZ());
	}


	void ColorProfileCurvesComponent::clear()
	{
		itemRGB_R.clear();
		itemRGB_G.clear();
		itemRGB_B.clear();
		itemHSB_H.clear();
		itemHSB_S.clear();
		itemHSB_B.clear();
		itemXYZ_X.clear();
		itemXYZ_Y.clear();
		itemXYZ_Z.clear();
		itemXYV_X.clear();
		itemXYV_Y.clear();
		itemXYV_V.clear();
		itemLAB_L.clear();
		itemLAB_A.clear();
		itemLAB_B.clear();
	}
}
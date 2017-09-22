#include "WhiteBalanceCurvesComponent.h"


namespace Capture3
{

	WhiteBalanceCurvesComponent::WhiteBalanceCurvesComponent() :
		PanelTabComponent("White Balance Curves"),
		groupRGB("White Balance Curve - RGB"),
		groupHSB("White Balance Curve - HSB"),
		groupXYZ("White Balance Curve - XYZ"),
		groupXYV("White Balance Curve - xyY"),
		groupLAB("White Balance Curve - LAB"),
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


	WhiteBalanceCurvesComponent::~WhiteBalanceCurvesComponent()
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


	void WhiteBalanceCurvesComponent::show(const WhiteBalance *whiteBalance)
	{
		itemRGB_R.show(whiteBalance->getCurvesRGB().getCurveX());
		itemRGB_G.show(whiteBalance->getCurvesRGB().getCurveY());
		itemRGB_B.show(whiteBalance->getCurvesRGB().getCurveZ());
		itemHSB_H.show(whiteBalance->getCurvesHSB().getCurveX());
		itemHSB_S.show(whiteBalance->getCurvesHSB().getCurveY());
		itemHSB_B.show(whiteBalance->getCurvesHSB().getCurveZ());
		itemXYZ_X.show(whiteBalance->getCurvesXYZ().getCurveX());
		itemXYZ_Y.show(whiteBalance->getCurvesXYZ().getCurveY());
		itemXYZ_Z.show(whiteBalance->getCurvesXYZ().getCurveZ());
		itemXYV_X.show(whiteBalance->getCurvesXYV().getCurveX());
		itemXYV_Y.show(whiteBalance->getCurvesXYV().getCurveY());
		itemXYV_V.show(whiteBalance->getCurvesXYV().getCurveZ());
		itemLAB_L.show(whiteBalance->getCurvesLAB().getCurveX());
		itemLAB_A.show(whiteBalance->getCurvesLAB().getCurveY());
		itemLAB_B.show(whiteBalance->getCurvesLAB().getCurveZ());
	}


	void WhiteBalanceCurvesComponent::clear()
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
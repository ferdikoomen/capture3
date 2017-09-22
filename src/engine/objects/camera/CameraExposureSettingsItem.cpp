#include "CameraExposureSettingsItem.h"


namespace Capture3
{

	CameraExposureSettingsItem::CameraExposureSettingsItem(
		const unsigned int index,
		const QString &label,
		const double value,
		const double precise,
		const double v,
		const int vi
	) :
		index(index),
		label(label),
		value(value),
		precise(precise),
		v(v),
		vi(vi)
	{
		//
	}


	CameraExposureSettingsItem::~CameraExposureSettingsItem()
	{
		//
	}


	const unsigned int CameraExposureSettingsItem::getIndex() const
	{
		return index;
	}


	const QString CameraExposureSettingsItem::getLabel() const
	{
		return label;
	}


	const double CameraExposureSettingsItem::getValue() const
	{
		return value;
	}


	const double CameraExposureSettingsItem::getPrecise() const
	{
		return precise;
	}


	const double CameraExposureSettingsItem::getV() const
	{
		return v;
	}


	const int CameraExposureSettingsItem::getVI() const
	{
		return vi;
	}

}
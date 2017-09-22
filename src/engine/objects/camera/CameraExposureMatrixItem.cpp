#include "CameraExposureMatrixItem.h"


namespace Capture3
{


	CameraExposureMatrixItem::CameraExposureMatrixItem(
		const double ev,
		const double lv,
		const int index,
		const unsigned int x,
		const unsigned int y,
		const unsigned int z,
		const CameraExposureSettingsItem *aperture,
		const CameraExposureSettingsItem *shutterSpeed,
		const CameraExposureSettingsItem *iso
	) :
		ev(ev),
		lv(lv),
		index(index),
		x(x),
		y(y),
		z(z),
		aperture(aperture),
		shutterSpeed(shutterSpeed),
		iso(iso)
	{
		//
	}


	CameraExposureMatrixItem::~CameraExposureMatrixItem()
	{
		aperture = nullptr;
		shutterSpeed = nullptr;
		iso = nullptr;
	}


	const double CameraExposureMatrixItem::getEV() const
	{
		return ev;
	}


	const double CameraExposureMatrixItem::getLV() const
	{
		return lv;
	}


	const int CameraExposureMatrixItem::getIndex() const
	{
		return index;
	}


	const unsigned int CameraExposureMatrixItem::getX() const
	{
		return x;
	}


	const unsigned int CameraExposureMatrixItem::getY() const
	{
		return y;
	}


	const unsigned int CameraExposureMatrixItem::getZ() const
	{
		return z;
	}


	const CameraExposureSettingsItem *CameraExposureMatrixItem::getAperture() const
	{
		return aperture;
	}


	const CameraExposureSettingsItem *CameraExposureMatrixItem::getShutterSpeed() const
	{
		return shutterSpeed;
	}


	const CameraExposureSettingsItem *CameraExposureMatrixItem::getIso() const
	{
		return iso;
	}

}
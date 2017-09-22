#include "CameraExposureSettings.h"


namespace Capture3
{

	CameraExposureSettings::CameraExposureSettings(
		const double apertureMin,
		const double apertureMax,
		const double shutterSpeedMin,
		const double shutterSpeedMax,
		const double isoMin,
		const double isoMax,
		const double stopsAperture,
		const double stopsShutterSpeed,
		const double stopsIso
	) :
		apertureMin(apertureMin),
		apertureMax(apertureMax),
		shutterSpeedMin(shutterSpeedMin),
		shutterSpeedMax(shutterSpeedMax),
		isoMin(isoMin),
		isoMax(isoMax),
		stopsAperture(stopsAperture),
		stopsShutterSpeed(stopsShutterSpeed),
		stopsIso(stopsIso),
		settingsAperture(),
		settingsShutterSpeed(),
		settingsIso()
	{
		// Values for aperture (where f/1 == 0)
		addAperture("f/1.0", 1.0, 0);
		addAperture("f/1.1", 1.1, 1);
		addAperture("f/1.2", 1.2, 2);
		addAperture("f/1.4", 1.4, 3);
		addAperture("f/1.6", 1.6, 4);
		addAperture("f/1.8", 1.8, 5);
		addAperture("f/2", 2, 6);
		addAperture("f/2.2", 2.2, 7);
		addAperture("f/2.5", 2.5, 8);
		addAperture("f/2.8", 2.8, 9);
		addAperture("f/3.2", 3.2, 10);
		addAperture("f/3.5", 3.5, 11);
		addAperture("f/4", 4, 12);
		addAperture("f/4.5", 4.5, 13);
		addAperture("f/5", 5, 14);
		addAperture("f/5.6", 5.6, 15);
		addAperture("f/6.3", 6.3, 16);
		addAperture("f/7.1", 7.1, 17);
		addAperture("f/8", 8, 18);
		addAperture("f/9", 9, 19);
		addAperture("f/10", 10, 20);
		addAperture("f/11", 11, 21);
		addAperture("f/13", 13, 22);
		addAperture("f/14", 14, 23);
		addAperture("f/16", 16, 24);
		addAperture("f/18", 18, 25);
		addAperture("f/20", 20, 26);
		addAperture("f/22", 22, 27);
		addAperture("f/25", 25, 28);
		addAperture("f/29", 29, 29);
		addAperture("f/32", 32, 30);

		// Values for shutter (where 1s == 0)
		addShutterSpeed("30s", 30, -15);
		addShutterSpeed("25s", 25, -14);
		addShutterSpeed("20s", 20, -13);
		addShutterSpeed("15s", 15, -12);
		addShutterSpeed("13s", 13, -11);
		addShutterSpeed("10s", 10, -10);
		addShutterSpeed("8s", 8, -9);
		addShutterSpeed("6s", 6, -8);
		addShutterSpeed("5s", 5, -7);
		addShutterSpeed("4s", 4, -6);
		addShutterSpeed("3s", 3, -5);
		addShutterSpeed("2.5s", 2.5, -4);
		addShutterSpeed("2s", 2, -3);
		addShutterSpeed("1.6s", 1.6, -2);
		addShutterSpeed("1.3s", 1.3, -1);
		addShutterSpeed("1s", 1, 0);
		addShutterSpeed("1/1.3s", 1.0 / 1.3, 1);
		addShutterSpeed("1/1.6s", 1.0 / 1.6, 2);
		addShutterSpeed("1/2s", 1.0 / 2, 3);
		addShutterSpeed("1/2.5s", 1.0 / 2.5, 4);
		addShutterSpeed("1/3s", 1.0 / 3, 5);
		addShutterSpeed("1/4s", 1.0 / 4, 6);
		addShutterSpeed("1/5s", 1.0 / 5, 7);
		addShutterSpeed("1/6s", 1.0 / 6, 8);
		addShutterSpeed("1/8s", 1.0 / 8, 9);
		addShutterSpeed("1/10s", 1.0 / 10, 10);
		addShutterSpeed("1/13s", 1.0 / 13, 11);
		addShutterSpeed("1/15s", 1.0 / 15, 12);
		addShutterSpeed("1/20s", 1.0 / 20, 13);
		addShutterSpeed("1/25s", 1.0 / 25, 14);
		addShutterSpeed("1/30s", 1.0 / 30, 15);
		addShutterSpeed("1/40s", 1.0 / 40, 16);
		addShutterSpeed("1/50s", 1.0 / 50, 17);
		addShutterSpeed("1/60s", 1.0 / 60, 18);
		addShutterSpeed("1/80s", 1.0 / 80, 19);
		addShutterSpeed("1/100s", 1.0 / 100, 20);
		addShutterSpeed("1/125s", 1.0 / 125, 21);
		addShutterSpeed("1/160s", 1.0 / 160, 22);
		addShutterSpeed("1/200s", 1.0 / 200, 23);
		addShutterSpeed("1/250s", 1.0 / 250, 24);
		addShutterSpeed("1/320s", 1.0 / 320, 25);
		addShutterSpeed("1/400s", 1.0 / 400, 26);
		addShutterSpeed("1/500s", 1.0 / 500, 27);
		addShutterSpeed("1/640s", 1.0 / 640, 28);
		addShutterSpeed("1/800s", 1.0 / 800, 29);
		addShutterSpeed("1/1000s", 1.0 / 1000, 30);
		addShutterSpeed("1/1250s", 1.0 / 1250, 31);
		addShutterSpeed("1/1600s", 1.0 / 1600, 32);
		addShutterSpeed("1/2000s", 1.0 / 2000, 33);
		addShutterSpeed("1/2500s", 1.0 / 2500, 34);
		addShutterSpeed("1/3200s", 1.0 / 3200, 35);
		addShutterSpeed("1/4000s", 1.0 / 4000, 36);

		// Values for iso (where iso 100/21° == 0)
		addIso("25/15°", 25, -6);
		addIso("32/16°", 32, -5);
		addIso("40/17°", 40, -4);
		addIso("50/18°", 50, -3);
		addIso("64/19°", 64, -2);
		addIso("80/20°", 80, -1);
		addIso("100/21°", 100, 0);
		addIso("125/22°", 125, 1);
		addIso("160/23°", 160, 2);
		addIso("200/24°", 200, 3);
		addIso("250/25°", 250, 4);
		addIso("320/26°", 320, 5);
		addIso("400/27°", 400, 6);
		addIso("500/28°", 500, 7);
		addIso("640/29°", 640, 8);
		addIso("800/30°", 800, 9);
		addIso("1000/31°", 1000, 10);
		addIso("1250/32°", 1250, 11);
		addIso("1600/33°", 1600, 12);
		addIso("2000/34°", 2000, 13);
		addIso("2500/35°", 2500, 14);
		addIso("3200/36°", 3200, 15);
		addIso("4000/37°", 4000, 16);
		addIso("5000/38°", 5000, 17);
		addIso("6400/39°", 6400, 18);
	}


	CameraExposureSettings::~CameraExposureSettings()
	{
		settingsAperture.clear();
		settingsShutterSpeed.clear();
		settingsIso.clear();
	}


	const CameraExposureSettingsItem *CameraExposureSettings::getSettingsAperture(const unsigned int index) const
	{
		const unsigned int max = (unsigned int) settingsAperture.size() - 1;
		return settingsAperture[index < 0 ? 0 : index > max ? max : index];
	}


	const CameraExposureSettingsItem *CameraExposureSettings::getSettingsShutterSpeed(const unsigned int index) const
	{
		const unsigned int max = (unsigned int) settingsShutterSpeed.size() - 1;
		return settingsShutterSpeed[index < 0 ? 0 : index > max ? max : index];
	}


	const CameraExposureSettingsItem *CameraExposureSettings::getSettingsIso(const unsigned int index) const
	{
		const unsigned int max = (unsigned int) settingsIso.size() - 1;
		return settingsIso[index < 0 ? 0 : index > max ? max : index];
	}


	const std::vector<const CameraExposureSettingsItem *> &CameraExposureSettings::getSettingsAperture() const
	{
		return settingsAperture;
	}


	const std::vector<const CameraExposureSettingsItem *> &CameraExposureSettings::getSettingsShutterSpeed() const
	{
		return settingsShutterSpeed;
	}


	const std::vector<const CameraExposureSettingsItem *> &CameraExposureSettings::getSettingsIso() const
	{
		return settingsIso;
	}


	void CameraExposureSettings::addAperture(const QString &label, const double value, const int i)
	{
		// Check if value is in the supported range (both in range as in stops)
		if (value >= apertureMin && value <= apertureMax) {
			double even = fmod((i / 3.0) * stopsAperture, 1);
			if (even == 0) {

				// Grab values for exposure matrix:
				// - Index: Index of the item in array
				// - Label: Label of the item as can be seen on the camera
				// - Value: Value of the item as can be seen on the camera
				// - Precise: Precise value of the item (handy for HDR merges)
				// - V: The The AV/EV/DIN value for the exposure matrix
				// - VI: The pre-calculated V value with stop correction
				const auto index = (unsigned int) settingsAperture.size();
				const auto n = (int) std::round((i / 3.0) * stopsAperture);
				const double precise = getAperture(n);
				const double v = getApertureValue(precise);
				const auto vi = (int) std::round(v * stopsAperture);
				settingsAperture.push_back(new CameraExposureSettingsItem(index, label, value, precise, v, vi));
			}
		}
	}


	void CameraExposureSettings::addShutterSpeed(const QString &label, const double value, const int i)
	{
		// Check if value is in the supported range (both in range as in stops)
		if (value <= shutterSpeedMin && value >= shutterSpeedMax) {
			double even = fmod((i / 3.0) * stopsShutterSpeed, 1);
			if (even == 0) {

				// Grab values for exposure matrix:
				// - Index: Index of the item in array
				// - Label: Label of the item as can be seen on the camera
				// - Value: Value of the item as can be seen on the camera
				// - Precise: Precise value of the item (handy for HDR merges)
				// - V: The AV/EV/DIN value for the exposure matrix
				// - VI: The pre-calculated V value with stop correction
				const auto index = (unsigned int) settingsShutterSpeed.size();
				const auto n = (int) std::round((i / 3.0) * stopsShutterSpeed);
				const double precise = getShutterSpeed(n);
				const double v = getShutterSpeedValue(precise);
				const auto vi = (int) std::round(v * stopsShutterSpeed);
				settingsShutterSpeed.push_back(new CameraExposureSettingsItem(index, label, value, precise, v, vi));
			}
		}
	}


	void CameraExposureSettings::addIso(const QString &label, const double value, const int i)
	{
		// Check if value is in the supported range (both in range as in stops)
		if (value >= isoMin && value <= isoMax) {
			double even = fmod((i / 3.0) * stopsIso, 1);
			if (even == 0) {

				// Grab values for exposure matrix:
				// - Index: Index of the item in array
				// - Label: Label of the item as can be seen on the camera
				// - Value: Value of the item as can be seen on the camera
				// - Precise: Precise value of the item (handy for HDR merges)
				// - V: The AV/EV/DIN value for the exposure matrix
				// - VI: The pre-calculated V value with stop correction
				const auto index = (unsigned int) settingsIso.size();
				const auto n = (int) std::round((i / 3.0) * stopsIso);
				const double precise = getIso(n);
				const double v = getIsoValue(value);
				const auto vi = (int) std::round(v * 3.0);
				settingsIso.push_back(new CameraExposureSettingsItem(index, label, value, precise, v, vi));
			}
		}
	}


	double CameraExposureSettings::getAperture(const int i) const
	{
		// AV
		const double pow = i / stopsAperture * 0.5;
		return std::pow(2.0, pow);
	}


	double CameraExposureSettings::getShutterSpeed(const int i) const
	{
		// EV
		const double pow = -i / stopsShutterSpeed;
		return std::pow(2.0, pow);
	}


	double CameraExposureSettings::getIso(const int i) const
	{
		// Return ASA ISO value from DIN:
		// https://en.wikipedia.org/wiki/Film_speed
		const double din = 21.0 + (i * (3.0 / stopsIso));
		return std::pow(10.0, (din - 1.0) / 10.0);
	}


	double CameraExposureSettings::getApertureValue(const double aperture) const
	{
		return std::log2(aperture * aperture);
	}


	double CameraExposureSettings::getShutterSpeedValue(const double shutter) const
	{
		return std::log2(1.0 / shutter);
	}


	double CameraExposureSettings::getIsoValue(const double iso) const
	{
		return std::log2(iso / 100.0);
	}
}
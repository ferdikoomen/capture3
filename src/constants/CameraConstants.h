#ifndef CAPTURE3_CAMERA_CONSTANTS_H
#define CAPTURE3_CAMERA_CONSTANTS_H


#include <QtCore/QString>


namespace Capture3
{

	static const QString CAMERA_CONNECTION_MODEL = "Nikon DSC D3300";
	static const QString CAMERA_CONNECTION_PORT = "usb:";


	static const QString CAMERA_KEY_SHUTTER_SPEED = "shutterspeed";
	static const QString CAMERA_KEY_SHUTTER_SPEED2 = "shutterspeed2";
	static const QString CAMERA_KEY_APERTURE = "f-number";
	static const QString CAMERA_KEY_ISO = "iso";
	static const QString CAMERA_KEY_ISO_AUTO = "isoauto";
	static const QString CAMERA_KEY_WHITE_BALANCE = "whitebalance";
	static const QString CAMERA_KEY_COLOR_SPACE = "colorspace";
	static const QString CAMERA_KEY_EXPOSURE_COMPENSATION = "exposurecompensation";
	static const QString CAMERA_KEY_IMAGE_SIZE = "imagesize";
	static const QString CAMERA_KEY_IMAGE_QUALITY = "imagequality";
	static const QString CAMERA_KEY_DYNAMIC_LIGHTING = "dlighting";
	static const QString CAMERA_KEY_LONG_EXPOSURE = "longexpnr";
	static const QString CAMERA_KEY_ASSIST_LIGHT = "assistlight";
	static const QString CAMERA_KEY_FLASH_MODE = "flashmode";
	static const QString CAMERA_KEY_FOCUS_METER_MODE = "focusmetermode";
	static const QString CAMERA_KEY_EXPOSURE_METER_MODE = "exposuremetermode";
	static const QString CAMERA_KEY_FOCUS_MODE = "focusmode2";
	static const QString CAMERA_KEY_FOCUS_MODE_LIVE_VIEW = "liveviewafmode";
	static const QString CAMERA_KEY_FOCUS_AREA = "changeafarea";
	static const QString CAMERA_KEY_AUTO_FOCUS_DRIVE = "autofocusdrive";
	static const QString CAMERA_KEY_MANUAL_FOCUS_DRIVE = "manualfocusdrive";
	static const QString CAMERA_KEY_FOCAL_LENGTH_MIN = "minfocallength";
	static const QString CAMERA_KEY_FOCAL_LENGTH_MAX = "maxfocallength";
	static const QString CAMERA_KEY_EXPOSURE_PROGRAM = "expprogram";
	static const QString CAMERA_KEY_CAPUTURE_MODE = "capturemode";
	static const QString CAMERA_KEY_RECORDING_MEDIA = "recordingmedia";
	static const QString CAMERA_KEY_CAPTURE_TARGET = "capturetarget";
	static const QString CAMERA_KEY_BATTERY_LEVEL = "batterylevel";


	static const QString CAMERA_DEFAULT_SHUTTER_SPEED = "0.0080s";
	static const QString CAMERA_DEFAULT_SHUTTER_SPEED2 = "1/250";
	static const QString CAMERA_DEFAULT_APERTURE = "f/8.0";
	static const QString CAMERA_DEFAULT_ISO = "100";
	static const QString CAMERA_DEFAULT_ISO_AUTO = "Off";
	static const QString CAMERA_DEFAULT_WHITE_BALANCE = "Daylight";
	static const QString CAMERA_DEFAULT_COLOR_SPACE = "sRGB";
	static const QString CAMERA_DEFAULT_EXPOSURE_COMPENSATION = "0";
	static const QString CAMERA_DEFAULT_IMAGE_SIZE = "6000x4000";
	static const QString CAMERA_DEFAULT_IMAGE_QUALITY = "NEF (Raw)";
	static const QString CAMERA_DEFAULT_DYNAMIC_LIGHTING = "Extra high";
	static const QString CAMERA_DEFAULT_LONG_EXPOSURE = "Off";
	static const QString CAMERA_DEFAULT_ASSIST_LIGHT = "On"; // Means off...
	static const QString CAMERA_DEFAULT_FLASH_MODE = "Auto";
	static const QString CAMERA_DEFAULT_FOCUS_METER_MODE = "Single Area";
	static const QString CAMERA_DEFAULT_EXPOSURE_METER_MODE = "Center Weighted";
	static const QString CAMERA_DEFAULT_FOCUS_MODE = "AF-S";
	static const QString CAMERA_DEFAULT_FOCUS_MODE_LIVE_VIEW = "Normal-area AF";
	static const QString CAMERA_DEFAULT_EXPOSURE_PROGRAM = "M";
	static const QString CAMERA_DEFAULT_CAPUTURE_MODE = "Single Shot";
	static const QString CAMERA_DEFAULT_RECORDING_MEDIA = "Card"; // "SDRAM";
	static const QString CAMERA_DEFAULT_CAPTURE_TARGET = "Memory card"; // "Internal RAM";


	static const double CAMERA_SETTING_APERTURE_MIN = 1.4;
	static const double CAMERA_SETTING_APERTURE_MAX = 16;
	static const double CAMERA_SETTING_SHUTTER_SPEED_MIN = 30;
	static const double CAMERA_SETTING_SHUTTER_SPEED_MAX = 1 / 4000;
	static const double CAMERA_SETTING_ISO_MIN = 100;
	static const double CAMERA_SETTING_ISO_MAX = 1600;
	static const unsigned int CAMERA_SETTING_STOPS_APERTURE = 3;
	static const unsigned int CAMERA_SETTING_STOPS_SHUTTER_SPEED = 3;
	static const unsigned int CAMERA_SETTING_STOPS_ISO = 1;
	static const unsigned int CAMERA_SETTING_FOCUS_NEAR = 40;
	static const unsigned int CAMERA_SETTING_FOCUS_FAR = 40;
	static const int CAMERA_SETTING_FOCUS_MULTIPLIER = 128;


	static const int CAMERA_INDEX_SHUTTER_SPEED = 39;
	static const int CAMERA_INDEX_APERTURE = 15;
	static const int CAMERA_INDEX_ISO = 0;
	static const int CAMERA_INDEX_SHOTS = 0;
	static const int CAMERA_INDEX_RANGE = 0;
	static const int CAMERA_INDEX_STEP = 0;
	static const int CAMERA_INDEX_MERGE_SHOTS = 0;
	static const int CAMERA_INDEX_MERGE_RANGE = 0;


	static const QString CAMERA_SETTING_MERGE_MEAN = "Mean";
	static const QString CAMERA_SETTING_MERGE_MEDIAN = "Median";
	static const QString CAMERA_SETTING_MERGE_EXPOSURE_FUSION = "Exposure Fusion";


	static const int CAMERA_UPDATE_PREVIEW = 100;
	static const int CAMERA_UPDATE_BATTERY_LEVEL = 5000;


	static const unsigned int CAMERA_PREVIEW_WIDTH = 640;
	static const unsigned int CAMERA_PREVIEW_HEIGHT = 424;
	static const unsigned int CAMERA_IMAGE_WIDTH = 6016;
	static const unsigned int CAMERA_IMAGE_HEIGHT = 4016;
	static const unsigned int CAMERA_RAW_WIDTH = 3008;
	static const unsigned int CAMERA_RAW_HEIGHT = 2008;


}

#endif // CAPTURE3_CAMERA_CONSTANTS_H

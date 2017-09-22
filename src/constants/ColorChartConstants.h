#ifndef CAPTURE3_COLOR_CHART_CONSTANTS_H
#define CAPTURE3_COLOR_CHART_CONSTANTS_H


#include <QtCore/QString>


namespace Capture3
{

	static const unsigned int COLOR_CHART_COLS = 14;
	static const unsigned int COLOR_CHART_ROWS = 10;
	static const unsigned int COLOR_CHART_COUNT = 140;


	static const unsigned int COLOR_CHART_PATCH_OFFSET_X = 165;
	static const unsigned int COLOR_CHART_PATCH_OFFSET_Y = 108;
	static const unsigned int COLOR_CHART_PATCH_HEIGHT = 100;
	static const unsigned int COLOR_CHART_PATCH_WIDTH = 100;
	static const unsigned int COLOR_CHART_PATCH_PADDING = 30;


	static const unsigned int COLOR_CHART_OUTSIDE_WIDTH = 2120;
	static const unsigned int COLOR_CHART_OUTSIDE_HEIGHT = 1486;
	static const unsigned int COLOR_CHART_INSIDE_WIDTH = 1790;
	static const unsigned int COLOR_CHART_INSIDE_HEIGHT = 1270;


	static const double COLOR_CHART_DETECT_AREA_MIN = 50 * 50;
	static const double COLOR_CHART_DETECT_AREA_MAX = 500 * 500;
	static const double COLOR_CHART_DETECT_RATIO_MIN = 0.8;
	static const double COLOR_CHART_DETECT_RATIO_MAX = 1.2;
	static const double COLOR_CHART_DETECT_THRESOLD_MIN = 0.8;
	static const double COLOR_CHART_DETECT_THRESOLD_MAX = 1.2;

}


#endif // CAPTURE3_COLOR_CHART_CONSTANTS_H

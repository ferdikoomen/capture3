#ifndef CAPTURE3_METAMORFOZE_CONSTANTS_H
#define CAPTURE3_METAMORFOZE_CONSTANTS_H


#include <QtCore/QString>


namespace Capture3
{

	static const unsigned int DELTA_E_MAX = 10; // CIE1976 distance
	static const unsigned int DELTA_C_MAX = 2; // Delta chroma
	static const unsigned int DELTA_L_MAX = 4; // Delta lightness
	static const unsigned int GAIN_MODULATION_MIN = 60; // Gain min = 80%
	static const unsigned int GAIN_MODULATION_MAX = 140; // Gain max = 108%

}


#endif // CAPTURE3_METAMORFOZE_CONSTANTS_H

#ifndef CAPTURE3_COLOR_CHART_PATCH_H
#define CAPTURE3_COLOR_CHART_PATCH_H


#include <string>
#include <vector>
#include <QtCore/QString>
#include <QtGui/QPixmap>


#include "../../../utils/ColorUtils.h"
#include "../../../utils/ColorSpaceUtils.h"


namespace Capture3
{

	class ColorChartPatch final
	{

		public:
			ColorChartPatch(
				const QString &label,
				const double l,
				const double a,
				const double b
			);

			virtual ~ColorChartPatch();

			void setRGB(const double r, const double g, const double b, const bool convert = true);

			void setHSB(const double h, const double s, const double b, const bool convert = true);

			void setXYZ(const double x, const double y, const double z, const bool convert = true);

			void setXYV(const double x, const double y, const double v, const bool convert = true);

			void setLAB(const double l, const double a, const double b, const bool convert = true);

			void update();

			const unsigned int *getRGB8() const;

			const double *getRGB() const;

			const double *getHSB() const;

			const double *getXYZ() const;

			const double *getXYV() const;

			const double *getLAB() const;

			QString getLabel() const;

			QPixmap getPreview() const;

		private:
			const QString label;
			unsigned int rgb8[3];
			double rgb[3];
			double hsb[3];
			double xyz[3];
			double xyv[3];
			double lab[3];

	};
}

#endif // CAPTURE3_COLOR_CHART_PATCH_H

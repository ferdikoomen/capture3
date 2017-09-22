#ifndef CAPTURE3_COLOR_CHART_VISUAL_UTILS_H
#define CAPTURE3_COLOR_CHART_VISUAL_UTILS_H


#include <string>
#include <vector>
#include <omp.h>
#include <QtCore/QString>
#include <QtGui/QImage>
#include <QtGui/QPixmap>
#include <QtGui/QPainter>
#include <QtGui/QColor>
#include <QtGui/QFont>


#include "../engine/objects/colorProfile/ColorProfileChart.h"
#include "../constants/ColorChartConstants.h"


namespace Capture3
{

	static QImage generate(const ColorProfileChart &chart, const int pixelRatio)
	{
		// Sizes we need to generate the image
		const int patchWidth = 75;
		const int patchHeight = 70;
		const int chartCols = COLOR_CHART_COLS;
		const int chartRows = COLOR_CHART_ROWS;
		const int chartWidth = patchWidth * chartCols;
		const int chartHeight = patchHeight * chartRows;

		// Create a new image and set pixel ratio so all painter calls are 'scaled'
		QImage image(chartWidth * pixelRatio, chartHeight * pixelRatio, QImage::Format_ARGB32_Premultiplied);
		image.setDevicePixelRatio(pixelRatio);

		// Font for labels
		const QFont font("Lucida Grande", 9, QFont::Bold);

		// Create new painter
		QPainter painter;
		painter.begin(&image);
		painter.setRenderHint(QPainter::Antialiasing, true);
		painter.setFont(font);

		// Get patches
		const std::vector<const ColorProfileChartPatch *> &patches = chart.getPatches();

		// Iterate over patches
		for (unsigned int row = 0; row < COLOR_CHART_ROWS; row++) {
			for (unsigned int col = 0; col < COLOR_CHART_COLS; col++) {

				// Calculate position
				const unsigned int index = (COLOR_CHART_ROWS * col) + row;
				const unsigned int x = col * patchWidth;
				const unsigned int y = row * patchHeight;

				// Fetch patches
				const ColorProfileChartPatch *patch = patches[index];
				const ColorChartPatch *patchReference = patch->getPatchReference();
				const ColorChartPatch *patchDetected = patch->getPatchDetected();

				// Set colors
				const QColor colorReference(
					patchReference->getRGB8()[0],
					patchReference->getRGB8()[1],
					patchReference->getRGB8()[2]
				);
				const QColor colorDetected(
					patchDetected->getRGB8()[0],
					patchDetected->getRGB8()[1],
					patchDetected->getRGB8()[2]
				);

				// Set text color based on patch brightness
				const QColor colorText(
					patchReference->getLAB()[0] > 0.5 ? 0 : 255,
					patchReference->getLAB()[0] > 0.5 ? 0 : 255,
					patchReference->getLAB()[0] > 0.5 ? 0 : 255
				);

				// Create triangle shape
				QPainterPath triangle;
				triangle.moveTo(x + patchWidth, y);
				triangle.lineTo(x + patchWidth, y + patchHeight);
				triangle.lineTo(x, y + patchHeight);
				triangle.lineTo(x + patchWidth, y);

				// Draw rectangle and triangle
				painter.setPen(Qt::NoPen);
				painter.fillRect(x, y, patchWidth, patchHeight, colorReference);
				painter.setBrush(colorDetected);
				painter.drawPath(triangle);

				// Draw text
				painter.setBrush(Qt::NoBrush);
				painter.setPen(colorText);
				painter.drawText(x + 2, y + 10, patchReference->getLabel());
				painter.drawText(x + 2, y + 20, "ΔC " + QString::number(patch->getDeltaChroma(), 'f', 2));
				painter.drawText(x + 2, y + 30, "ΔL " + QString::number(patch->getDeltaLightness(), 'f', 2));
				painter.drawText(x + 2, y + 40, "ΔE " + QString::number(patch->getDeltaCIE1976(), 'f', 2));
				painter.drawText(x + 2, y + 50, "ΔE " + QString::number(patch->getDeltaCIE2000(), 'f', 2));
			}
		}

		painter.end();

		return image;
	}

}


#endif // CAPTURE3_COLOR_CHART_VISUAL_UTILS_H

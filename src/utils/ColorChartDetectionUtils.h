#ifndef CAPTURE3_COLOR_CHART_UTILS_H
#define CAPTURE3_COLOR_CHART_UTILS_H


#include <cmath>
#include <vector>
#include <omp.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>


#include "../engine/objects/colorChart/ColorChart.h"
#include "../engine/objects/colorChart/ColorChartPatch.h"
#include "../constants/ColorChartConstants.h"
#include "../constants/ResourceConstants.h"
#include "../engine/objects/image/Image.h"
#include "ColorUtils.h"


namespace Capture3
{

	static ColorChart *detectColorChart(const Image *image)
	{
		// Create profile
		auto *chart = new ColorChart();
		const std::vector<ColorChartPatch *> &patches = chart->getPatches();


		/**************************************************
		 * Then we iterate over the captured image and
		 * find the min and max values for each channel,
		 * these values are needed to apply auto-contrast.
		 **************************************************/


		// Fetch image size
		const double *imageData = image->getRGB().getData();
		const cv::Mat &imageMat = image->getRGB().getMat();
		const unsigned int imageWidth = image->getSize().getWidth();
		const unsigned int imageHeight = image->getSize().getHeight();
		const unsigned int imageArea = image->getSize().getArea();
		const cv::Size &imageSize = image->getSize().getSize();

		// Min and max values
		double valueMinR = 1;
		double valueMinG = 1;
		double valueMinB = 1;
		double valueMaxR = 0;
		double valueMaxG = 0;
		double valueMaxB = 0;

		// Find min and max values (for auto contrast)
		#pragma omp parallel for schedule(static) \
            reduction(min:valueMinR), \
            reduction(min:valueMinG), \
            reduction(min:valueMinB), \
            reduction(max:valueMaxR), \
            reduction(max:valueMaxG), \
            reduction(max:valueMaxB)
		for (unsigned int i = 0; i < imageArea; i++) {
			const unsigned int index = i * 3;
			const double colorR = imageData[index + 0];
			const double colorG = imageData[index + 1];
			const double colorB = imageData[index + 2];
			valueMinR = colorR < valueMinR ? colorR : valueMinR;
			valueMinG = colorG < valueMinG ? colorG : valueMinG;
			valueMinB = colorB < valueMinB ? colorB : valueMinB;
			valueMaxR = colorR > valueMaxR ? colorR : valueMaxR;
			valueMaxG = colorG > valueMaxG ? colorG : valueMaxG;
			valueMaxB = colorB > valueMaxB ? colorB : valueMaxB;
		}


		/**************************************************
		 * We create a greyscale image and detect the scene
		 * contours using Canny-Edge detection. After we
		 * found the contours, we filter out the color
		 * squares of the color chart
		 **************************************************/


		// Create greyscale image
		cv::Mat scene(imageSize, CV_8UC1, cv::Scalar(0));
		unsigned char *sceneData = scene.data;

		// Calculate greyscale image (auto contrast)
		#pragma omp parallel for schedule(static)
		for (unsigned int i = 0; i < imageArea; i++) {
			const unsigned int index = i * 3;
			const double colorR = (imageData[index + 0] - valueMinR) / (valueMaxR - valueMinR);
			const double colorG = (imageData[index + 1] - valueMinG) / (valueMaxG - valueMinG);
			const double colorB = (imageData[index + 2] - valueMinB) / (valueMaxB - valueMinB);
			const double luma = (0.2126 * colorR) + (0.7152 * colorG) + (0.0722 * colorB);
			sceneData[i] = (unsigned char) lround(luma * 255.0);
		}

		// Find contours from edges
		cv::GaussianBlur(scene, scene, cv::Size(3, 3), 0, 0);
		cv::Canny(scene, scene, 10, 30, 3);
		std::vector<std::vector<cv::Point> > contours;
		cv::findContours(scene, contours, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);
		scene.release();

		// Check if we found any contours
		const unsigned int contoursCount = (unsigned int) contours.size();
		if (contoursCount > 0) {

			// Array that will contain the matched rotated rectangles
			// and the original corner points of the contour. We will
			// need this data to calculate the position of the color chart.
			std::vector<cv::Point> points;
			std::vector<cv::RotatedRect> rectangles;
			double rectanglesArea = 0;
			double rectanglesRatio = 0;

			// Iterate over contours
			for (unsigned int i = 0; i < contoursCount; i++) {

				// Fetch contour, calculate perimeter
				const cv::Mat countour(contours[i]);
				const double contourLength = cv::arcLength(countour, true);

				// Approximate the contour to a polygon
				std::vector<cv::Point> approx;
				cv::approxPolyDP(countour, approx, contourLength * 0.02, true);

				// If the poly has 4 sides and is convex then it could be a match
				if (approx.size() == 4 && cv::isContourConvex(approx)) {

					// Fetch the rectangle area from the match
					const cv::RotatedRect rectangle = cv::minAreaRect(approx);
					const double rectangleArea = rectangle.size.width * rectangle.size.height;
					const double rectangleRatio = rectangle.size.width / rectangle.size.height;

					// Check if the shape is rectangular enough
					if (rectangleArea >= COLOR_CHART_DETECT_AREA_MIN &&
						rectangleArea <= COLOR_CHART_DETECT_AREA_MAX &&
						rectangleRatio >= COLOR_CHART_DETECT_RATIO_MIN &&
						rectangleRatio <= COLOR_CHART_DETECT_RATIO_MAX) {

						// Store rectangles points (need them later for area calculation)
						points.push_back(approx[0]);
						points.push_back(approx[1]);
						points.push_back(approx[2]);
						points.push_back(approx[3]);
						rectangles.push_back(rectangle);
						rectanglesArea += rectangleArea;
						rectanglesRatio += rectangleRatio;
					}
				}
			}

			// Check if we found any rectangles
			const unsigned int rectanglesCount = (unsigned int) rectangles.size();
			if (rectanglesCount > 0) {

				// Calculate thresholds
				const double rectangleAreaMin = (rectanglesArea / rectanglesCount) * COLOR_CHART_DETECT_THRESOLD_MIN;
				const double rectangleAreaMax = (rectanglesArea / rectanglesCount) * COLOR_CHART_DETECT_THRESOLD_MAX;
				const double rectangleRatioMin = (rectanglesRatio / rectanglesCount) * COLOR_CHART_DETECT_THRESOLD_MIN;
				const double rectangleRatioMax = (rectanglesRatio / rectanglesCount) * COLOR_CHART_DETECT_THRESOLD_MAX;

				// Final points
				std::vector<cv::Point> filtered;

				// Iterate over rectangles
				for (unsigned int i = 0; i < rectanglesCount; i++) {

					// Fetch rectangle and calculate size and ratio
					const cv::RotatedRect rectangle = rectangles[i];
					const double rectangleArea = rectangle.size.width * rectangle.size.height;
					const double rectangleRatio = rectangle.size.width / rectangle.size.height;

					// Check if the rectangle fits the average rectangle
					if (rectangleArea >= rectangleAreaMin &&
						rectangleArea <= rectangleAreaMax &&
						rectangleRatio >= rectangleRatioMin &&
						rectangleRatio <= rectangleRatioMax) {

						// If so, then add these points to the valid points list
						const unsigned int index = i * 4;
						filtered.push_back(points[index + 0]);
						filtered.push_back(points[index + 1]);
						filtered.push_back(points[index + 2]);
						filtered.push_back(points[index + 3]);
					}
				}


				/**************************************************
				 * At this point we have filtered the contours to
				 * a list of valid points that are the corners of
				 * the small color squares inside the color chart.
				 * In the next step we need to calculate the
				 * rectangle that forms the actual color chart area.
				 **************************************************/


				// Check if we found any final points
				const unsigned int filteredCount = (unsigned int) filtered.size();
				if (filteredCount > 0) {

					// Find the center point
					unsigned int totalX = 0;
					unsigned int totalY = 0;
					for (unsigned int i = 0; i < filteredCount; i++) {
						totalX += filtered[i].x;
						totalY += filtered[i].y;
					}
					const double centerX = (double) totalX / filteredCount;
					const double centerY = (double) totalY / filteredCount;
					const cv::Point center(
						(unsigned int) lround(centerX),
						(unsigned int) lround(centerY)
					);

					// Sort points based on distance from center (from far to near)
					std::sort(filtered.begin(), filtered.end(), [centerX, centerY](const cv::Point a, const cv::Point b) {
						const double distanceAX = centerX - a.x;
						const double distanceAY = centerY - a.y;
						const double distanceBX = centerX - b.x;
						const double distanceBY = centerY - b.y;
						const double distanceA = std::sqrt(distanceAX * distanceAX + distanceAY * distanceAY);
						const double distanceB = std::sqrt(distanceBX * distanceBX + distanceBY * distanceBY);
						return distanceA > distanceB;
					});

					// Create final corner points
					cv::Point pointA = center;
					cv::Point pointB = center;
					cv::Point pointC = center;
					cv::Point pointD = center;

					// Find corners
					for (unsigned int i = 0; i < filteredCount; i++) {
						const cv::Point point = filtered[i];
						if (point.x < pointA.x && point.y < pointA.y) pointA = point;
						if (point.x > pointB.x && point.y < pointB.y) pointB = point;
						if (point.x > pointC.x && point.y > pointC.y) pointC = point;
						if (point.x < pointD.x && point.y > pointD.y) pointD = point;
						// cv::circle(imageMat, cv::Point(filtered[i].x, filtered[i].y), 5, cv::Scalar(0, 1, 0), 2, 8);
					}

					// cv::circle(imageMat, pointA, 20, cv::Scalar(1, 0, 0), 2, 8);
					// cv::circle(imageMat, pointB, 20, cv::Scalar(1, 0, 0), 2, 8);
					// cv::circle(imageMat, pointC, 20, cv::Scalar(1, 0, 0), 2, 8);
					// cv::circle(imageMat, pointD, 20, cv::Scalar(1, 0, 0), 2, 8);
					// cv::circle(imageMat, center, 10, cv::Scalar(0, 0, 1), 2, 8);
					// cv::imshow("image", imageMat);
					// cv::waitKey(0);

					// Store corners
					const cv::Point2f corners[4] = {
						cv::Point2f(pointA.x, pointA.y),
						cv::Point2f(pointB.x, pointB.y),
						cv::Point2f(pointC.x, pointC.y),
						cv::Point2f(pointD.x, pointD.y)
					};

					// Store output size
					const cv::Size outputSize(COLOR_CHART_INSIDE_WIDTH, COLOR_CHART_INSIDE_HEIGHT);
					const cv::Point2f outputRect[4] = {
						cv::Point2f(0, 0),
						cv::Point2f(outputSize.width, 0),
						cv::Point2f(outputSize.width, outputSize.height),
						cv::Point2f(0, outputSize.height)
					};

					// Calculate and apply perspective transform
					cv::Mat output;
					cv::Mat transform = cv::getPerspectiveTransform(corners, outputRect);
					cv::warpPerspective(imageMat, output, transform, outputSize, cv::INTER_LINEAR, cv::BORDER_CONSTANT, 0);


					/**************************************************
					 * Right now we have a output image with the cropped
					 * color chart (inside area). Now we can iterate
					 * over the color squares and store the mean value.
					 **************************************************/


					// Iterate over patches
					for (unsigned int col = 0; col < COLOR_CHART_COLS; col++) {
						for (unsigned int row = 0; row < COLOR_CHART_ROWS; row++) {

							// Calculate position of patch
							const unsigned int x = col * (COLOR_CHART_PATCH_WIDTH + COLOR_CHART_PATCH_PADDING);
							const unsigned int y = row * (COLOR_CHART_PATCH_HEIGHT + COLOR_CHART_PATCH_PADDING);
							const unsigned int index = COLOR_CHART_ROWS * col + row;

							// Rectangle area of the patch
							const cv::Rect rect(
								x + 10,
								y + 10,
								COLOR_CHART_PATCH_WIDTH - 20,
								COLOR_CHART_PATCH_HEIGHT - 20
							);

							// Calculate mean color from area
							const cv::Scalar color = cv::mean(cv::Mat(output, rect));

							// Set color
							patches[index]->setRGB(
								color[0],
								color[1],
								color[2]
							);
						}
					}
				}
			}
		}

		return chart;
	}

}


#endif // CAPTURE3_COLOR_CHART_UTILS_H

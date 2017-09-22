#ifndef CAPTURE3_BOUNDING_BOX_UTILS_H
#define CAPTURE3_BOUNDING_BOX_UTILS_H


#include <cmath>
#include <vector>


namespace Capture3
{

	static void boundingBoxLine(
		const unsigned int index,
		std::vector<float> &vector,
		const float x1, const float y1, const float z1,
		const float x2, const float y2, const float z2
	)
	{
		vector[index + 0] = x1;
		vector[index + 1] = y1;
		vector[index + 2] = z1;
		vector[index + 3] = x2;
		vector[index + 4] = y2;
		vector[index + 5] = z2;
	}


	static void boundingBoxLines(
		const unsigned int index,
		std::vector<float> &vector
	)
	{
		// Draw bounding box
		boundingBoxLine(index + 0, vector, -0.5f, -0.5f, -0.5f, 0.5f, -0.5f, -0.5f);
		boundingBoxLine(index + 6, vector, -0.5f, -0.5f, -0.5f, -0.5f, 0.5f, -0.5f);
		boundingBoxLine(index + 12, vector, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, 0.5f);
		boundingBoxLine(index + 18, vector, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, -0.5f);
		boundingBoxLine(index + 24, vector, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f, 0.5f);
		boundingBoxLine(index + 30, vector, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f);
		boundingBoxLine(index + 36, vector, -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f);
		boundingBoxLine(index + 42, vector, -0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f);
		boundingBoxLine(index + 48, vector, -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f);
		boundingBoxLine(index + 54, vector, 0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f);
		boundingBoxLine(index + 60, vector, 0.5f, 0.5f, 0.5f, 0.5f, -0.5f, 0.5f);
		boundingBoxLine(index + 66, vector, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, -0.5f);
	}


	static void boundingBox(
		const unsigned int index,
		std::vector<float> &positionsRGB,
		std::vector<float> &positionsHSB,
		std::vector<float> &positionsXYZ,
		std::vector<float> &positionsXYV,
		std::vector<float> &positionsLAB,
		std::vector<float> &colors
	)
	{
		// Add positions
		boundingBoxLines(index, positionsRGB);
		boundingBoxLines(index, positionsHSB);
		boundingBoxLines(index, positionsXYZ);
		boundingBoxLines(index, positionsXYV);
		boundingBoxLines(index, positionsLAB);

		// Add colors for the bounding box
		// 72 = 12 lines * 2 points * 3 coordinates
		for (unsigned int i = 0; i < 72; i++) {
			colors[index + i] = 60.0f / 255.0f;
		}
	}

}


#endif // CAPTURE3_BOUNDING_BOX_UTILS_H

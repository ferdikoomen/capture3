#include "RawProcessor.h"


#include <QDebug>


namespace Capture3
{

	RawProcessor::RawProcessor() :
		files(),

		// Output size
		outputWidth(CAMERA_RAW_WIDTH),
		outputHeight(CAMERA_RAW_HEIGHT),
		outputArea(outputWidth * outputHeight),
		outputSize(outputWidth, outputHeight)
	{
		//
	}


	RawProcessor::~RawProcessor()
	{
		files.clear();
	}


	void RawProcessor::add(
		const unsigned int indexFocus,
		const unsigned int indexExposure,
		const unsigned int indexShot,
		RawFile *file)
	{
		// Allocate vectors (3 dimensions)
		if (files.size() <= indexFocus) {
			files.resize(indexFocus + 1);
		}
		if (files[indexFocus].size() <= indexExposure) {
			files[indexFocus].resize(indexExposure + 1);
		}
		if (files[indexFocus][indexExposure].size() <= indexShot) {
			files[indexFocus][indexExposure].resize(indexShot + 1);
		}

		// Store file
		files[indexFocus][indexExposure][indexShot] = file;
	}


	Image *RawProcessor::process(
		const unsigned int mergeShots,
		const unsigned int mergeRange
	)
	{
		// Reset output size
		outputWidth = CAMERA_RAW_WIDTH;
		outputHeight = CAMERA_RAW_HEIGHT;
		outputArea = outputWidth * outputHeight;
		outputSize.width = outputWidth;
		outputSize.height = outputHeight;

		// Final images
		std::vector<cv::Mat> images;

		// Open, align and stack files
		openImages(images, mergeShots, mergeRange);
		alignImages(images);
		return stackImages(images);
	}


	void RawProcessor::openImages(
		std::vector<cv::Mat> &images,
		const unsigned int mergeShots,
		const unsigned int mergeRange
	)
	{
		// Image lists for merge actions
		std::vector<cv::Mat> imagesRange;
		std::vector<cv::Mat> imagesShots;

		for (unsigned int indexFocus = 0; indexFocus < files.size(); indexFocus++) {
			for (unsigned int indexExposure = 0; indexExposure < files[indexFocus].size(); indexExposure++) {
				for (unsigned int indexShot = 0; indexShot < files[indexFocus][indexExposure].size(); indexShot++) {

					// Fetch file
					RawFile *file = files[indexFocus][indexExposure][indexShot];

					// Open the RAW file
					if (processor.open_file(file->getFilePath().toLatin1().constData()) == LIBRAW_SUCCESS) {
						processor.unpack();

						// Create new image
						cv::Mat image(outputSize, CV_64FC3, cv::Scalar(0));
						auto *imageData = (double *) image.data;

						// Fetch image information
						const unsigned short *raw = processor.imgdata.rawdata.raw_image;
						const unsigned int inputWidth = processor.imgdata.sizes.width;
						const unsigned int inputHeight = processor.imgdata.sizes.height;
						const unsigned int rangeMin = processor.imgdata.color.black;
						const unsigned int rangeMax = processor.imgdata.color.maximum;
						const unsigned int range = rangeMax - rangeMin;

						#pragma omp parallel for schedule(static) collapse(2)
						for (unsigned int y = 0; y < outputHeight; y++) {
							for (unsigned int x = 0; x < outputWidth; x++) {

								// Calculate position
								const unsigned int col = x * 2;
								const unsigned int row = y * 2;

								// Calculate Bayer positions:
								// Row 1: [R, G]
								// Row 2: [B, G]
								const unsigned int indexR = (inputWidth * row) + col;
								const unsigned int indexG1 = (inputWidth * row) + col + 1;
								const unsigned int indexG2 = (inputWidth * (row + 1)) + col;
								const unsigned int indexB = (inputWidth * (row + 1)) + col + 1;

								// Calculate output positions
								const unsigned int index = (y * outputWidth + x) * 3;

								// Fetch colors
								auto colorR = (double) raw[indexR];
								auto colorG1 = (double) raw[indexG1];
								auto colorG2 = (double) raw[indexG2];
								auto colorB = (double) raw[indexB];
								double colorG = (colorG1 + colorG2) / 2.0;

								// Map to 0-1 range
								colorR = (colorR - rangeMin) / range;
								colorG = (colorG - rangeMin) / range;
								colorB = (colorB - rangeMin) / range;

								// Cap to 0-1 range
								colorR = colorR < 0 ? 0 : colorR > 1 ? 1 : colorR;
								colorG = colorG < 0 ? 0 : colorG > 1 ? 1 : colorG;
								colorB = colorB < 0 ? 0 : colorB > 1 ? 1 : colorB;

								// Store values
								imageData[index + 0] = colorR;
								imageData[index + 1] = colorG;
								imageData[index + 2] = colorB;
							}
						}

						// Add image
						imagesShots.push_back(image);
					}

					// Free image
					processor.free_image();
					processor.recycle();
				}

				// Merge shots to one image using the supplied setting.
				// This result is input for the HDR step.
				// TODO: Just merge average here
				if (!imagesShots.empty()) {
					imagesRange.push_back(
						mergeImages(imagesShots, mergeShots)
					);
					imagesShots.clear();
				}
			}

			// Compose final image by blending the multiple exposures
			// The result is input for the focus stack step.
			if (!imagesRange.empty()) {
				images.push_back(
					mergeImages(imagesRange, mergeRange)
				);
				imagesRange.clear();
			}
		}

		// Cleanup
		files.clear();
	}


	cv::Mat RawProcessor::mergeImages(std::vector<cv::Mat> &images, const unsigned int type)
	{
		// Fetch image count
		const auto count = (unsigned int) images.size();

		// TODO: Optimize this (if there is one image we should not clone this)
		if (count == 1) {
			return images[0].clone();
		}

		cv::Mat output(outputSize, CV_64FC3, cv::Scalar(0));
		auto *outputData = (double *) output.data;

		// Check merge modes
		// - Type 0: Merge mean
		// - Type 1: Merge median
		// - Type 2: Merge exposure fusion
		if (type != 2) {

			// Iterate over pixels and merge images
			#pragma omp parallel for schedule(static)
			for (unsigned int i = 0; i < outputArea * 3; i++) {

				// Fetch pixels from each image
				std::vector<double> pixels(count, 0.0);
				for (unsigned int n = 0; n < count; n++) {
					pixels[n] = ((double *) images[n].data)[i];
				}

				if (type == 0) {
					outputData[i] = calculateMean(pixels);
				}
				if (type == 1) {
					outputData[i] = calculateMedian(pixels);
				}
			}

		} else {

			// Image weights
			std::vector<cv::Mat> weights(count);
			cv::Mat sum(outputSize, CV_64FC1, cv::Scalar(0));

			// Weight multipiers
			const double contrastMultiplier = 1.0;
			const double saturationMultiplier = 1.0;
			const double exposureMultiplier = 1.0;

			for (unsigned int i = 0; i < count; i++) {

				// Fetch image
				cv::Mat &image = images[i];

				// Create greyscale image
				cv::Mat greyscale(outputSize, CV_64FC1, cv::Scalar(0));
				toGreyscale(
					(double *) image.data,
					(double *) greyscale.data,
					outputArea
				);

				// Calculate contrast map (Laplacian edge detection)
				// cv::Mat contrast;
				// cv::Laplacian(greyscale, contrast, CV_64FC1, 1, 1, 0, cv::BORDER_DEFAULT);
				// contrast = cv::abs(contrast);

				cv::Mat gradientX(outputSize, CV_64FC1, cv::Scalar(0));
				cv::Mat gradientY(outputSize, CV_64FC1, cv::Scalar(0));
				cv::Sobel(greyscale, gradientX, CV_64FC1, 1, 0, 3, 1, 0, cv::BORDER_DEFAULT);
				cv::Sobel(greyscale, gradientY, CV_64FC1, 0, 1, 3, 1, 0, cv::BORDER_DEFAULT);
				gradientX = cv::abs(gradientX);
				gradientY = cv::abs(gradientY);
				cv::Mat contrast(outputSize, CV_64FC1, cv::Scalar(0));
				cv::addWeighted(gradientX, 0.5, gradientY, 0.5, 0, contrast, CV_64FC1);

				// Split image to channels
				std::vector<cv::Mat> channels(3);
				cv::split(image, channels);

				// Calculate mean of channels
				cv::Mat mean(outputSize, CV_64FC1, cv::Scalar(0));
				mean += channels[0];
				mean += channels[1];
				mean += channels[2];
				mean /= 3.0;

				// Calculate saturation map via standard deviation
				cv::Mat saturation(outputSize, CV_64FC1, cv::Scalar(0));
				for (unsigned int c = 0; c < 3; c++) {
					cv::Mat deviation = channels[c] - mean;
					cv::pow(deviation, 2.0, deviation);
					saturation += deviation;
				}
				cv::sqrt(saturation, saturation);

				// Calculate exposure map
				cv::Mat exposure(outputSize, CV_64FC1, double(1));
				for (unsigned int c = 0; c < 3; c++) {
					cv::Mat expo = channels[c] - 0.5;
					cv::pow(expo, 2.0, expo);
					expo = -expo / 0.08; // (2.0 * std::pow(2.0, 0.2))
					cv::exp(expo, expo);
					exposure = exposure.mul(expo);
				}

				// Apply weights on maps
				cv::pow(contrast, contrastMultiplier, contrast);
				cv::pow(saturation, saturationMultiplier, saturation);
				cv::pow(exposure, exposureMultiplier, exposure);

				// cv::imshow("image", image);
				// cv::waitKey(0);
				// cv::imshow("image", greyscale);
				// cv::waitKey(0);
				// cv::imshow("image", contrast);
				// cv::waitKey(0);
				// cv::imshow("image", saturation);
				// cv::waitKey(0);
				// cv::imshow("image", exposure);
				// cv::waitKey(0);

				// Calculate final weight
				cv::Mat weight(outputSize, CV_64FC1, double(1));
				weight = weight.mul(contrast);
				weight = weight.mul(saturation);
				weight = weight.mul(exposure);

				// cv::imshow("image", weight);
				// cv::waitKey(0);

				weight += 1e-12;
				weights[i] = weight;
				sum += weight;
			}

			// cv::imshow("image", sum);
			// cv::waitKey(0);

			// Create the vector holding the result pyramid
			auto maxLevel = static_cast<int>(std::log(std::min(outputWidth, outputHeight)) / std::log(2.0));

			// Allocate vectors for pyramids
			std::vector<cv::Mat> res_pyr((size_t) maxLevel + 1);

			// Iterate over the images and create pyramids
			for (unsigned int i = 0; i < count; i++) {

				// Fetch image and weight
				cv::Mat &image = images[i];
				cv::Mat &weight = weights[i];

				// Build the pyramid
				weight /= sum;

				// cv::imshow("image", weight);
				// cv::waitKey(0);

				std::vector<cv::Mat> imagePyramid;
				std::vector<cv::Mat> weightPyramid;
				cv::buildPyramid(image, imagePyramid, maxLevel);
				cv::buildPyramid(weight, weightPyramid, maxLevel);

				// Sample and blur pyramid
				for (int level = 0; level < maxLevel; level++) {
					cv::Mat up;
					cv::pyrUp(imagePyramid[level + 1], up, imagePyramid[level].size());
					imagePyramid[level] -= up;
				}

				// Merge weights (per channel)
				for (int level = 0; level <= maxLevel; level++) {
					std::vector<cv::Mat> channels(3);
					cv::split(imagePyramid[level], channels);
					channels[0] = channels[0].mul(weightPyramid[level]);
					channels[1] = channels[1].mul(weightPyramid[level]);
					channels[2] = channels[2].mul(weightPyramid[level]);

					cv::merge(channels, imagePyramid[level]);
					if (res_pyr[level].empty()) {
						res_pyr[level] = imagePyramid[level];
					} else {
						res_pyr[level] += imagePyramid[level];
					}
				}
			}

			// Merge the result pyramid
			for (int level = maxLevel; level > 0; level--) {
				cv::Mat up;
				cv::pyrUp(res_pyr[level], up, res_pyr[level - 1].size());
				res_pyr[level - 1] += up;
			}

			// cv::imshow("image", res_pyr[0]);
			// cv::waitKey(0);

			// Store final result
			res_pyr[0].copyTo(output);
		}

		return output;
	}


	void RawProcessor::alignImages(std::vector<cv::Mat> &images)
	{
		// Fetch image count
		const auto count = (unsigned int) images.size();

		// We need a minimum of two images to align
		if (count >= 2) {

			// Vector with greyscale images
			std::vector<cv::Mat> greyscales;

			// First calculate the greyscale images
			for (unsigned int i = 0; i < count; i++) {

				// Fetch image
				const cv::Mat &image = images[i];

				// Create greyscale image
				cv::Mat greyscale(outputSize, CV_64FC1, cv::Scalar(0));
				toGreyscale(
					(double *) image.data,
					(double *) greyscale.data,
					outputArea
				);

				// Blur image (this gives better results during alignment
				cv::GaussianBlur(greyscale, greyscale, cv::Size(5, 5), 0, 0);

				// Store image
				greyscales.push_back(greyscale);
			}

			// To find the best matching alignment we should scale the near image and
			// see if it matches the far image (by checking the difference in pixel values).
			// The best match would be the image with the least difference. Instead of
			// trying every possible fit, we work our way down a pyramid. Starting with
			// checking big offsets, then moving to pixel level changes.

			// First we calculate the pixel step for this iteration. This value
			// is the power of 2 (2, 4, 8, 16, 32, 128, etc..). We use this value
			// to reduce the width of the image. In the first iteration the image width
			// is reduced by 128 pixels, the last iteration this is just 2 pixels.

			// The pyramid always iterates over 3 options and continues by selecting
			// the best match from those 3, moving our way down to pixel level.
			// This can result in the following search windows
			// 8. 0 - 256 * 3
			// 7. 0 - 128 * 3
			// 6. 0 - 64 * 3
			// 5. 0 - 32 * 3
			// 4. 0 - 16 * 3
			// 3. 0 - 8 * 3
			// 2. 0 - 4 * 3
			// 1. 0 - 2 * 3

			// Final scale
			double scaleTotal = 0;
			double scaleMean = 0;

			#pragma omp parallel for schedule(static)
			for (unsigned int i = 0; i < count - 1; i++) {

				// Read image
				const cv::Mat &imageNear = greyscales[i];
				const cv::Mat &imageFar = greyscales[i + 1];

				// Search window
				unsigned int searchStart = 0;
				unsigned int searchEnd = 3;

				// Match information
				unsigned int matchIndex = 0;
				unsigned int matchStep = 0;
				unsigned int matchWidth = outputWidth;
				unsigned int matchHeight = outputHeight;
				unsigned int matchX = 0;
				unsigned int matchY = 0;
				double matchScale = 1;

				// Hashmap to cache matches
				QHash<unsigned int, double> cache;

				// Start at the power of 4 => 16 pixel difference
				for (unsigned int power = 4; power >= 1; power--) {

					// Step size in pixels and relative to image width
					const auto stepPixels = (unsigned int) std::pow(2, power);
					const auto stepScaled = (double) stepPixels / outputWidth;

					// Hold the current error value
					double prevError = 1;

					// We iterate over 4 options and find the best match.
					for (unsigned int n = searchStart; n < searchEnd; n++) {

						// Current step (scale in pixels), also index of cached results
						const unsigned int step = stepPixels * n;

						// Current step and scale for this iteration
						const double scale = 1.0 - (stepScaled * n);

						// Calculate current scale
						const auto regionWidth = (unsigned int) lround(outputWidth * scale);
						const auto regionHeight = (unsigned int) lround(outputHeight * scale);
						const auto regionX = (unsigned int) lround((outputWidth - regionWidth) / 2.0);
						const auto regionY = (unsigned int) lround((outputHeight - regionHeight) / 2.0);
						const cv::Rect regionRect(regionX, regionY, regionWidth, regionHeight);
						const cv::Size regionSize(regionWidth, regionHeight);

						if (!cache.contains(step)) {

							// Crop the far image, note that this does not copy any pixels,
							// but just creates a reference to the original data, with a
							// region of interest.
							cv::Mat region(imageFar, regionRect);

							// Resize the near image, since we don't want to modify the
							// original data, we need to create new cv::Mat object here.
							// We will dispose this object later. Note that a simple
							// linear scaling will do, since we are just interested in
							// rough differences. Later on we will crop using better
							// area scaling.
							cv::Mat temp;
							cv::resize(imageNear, temp, regionSize, scale, scale, cv::INTER_LINEAR);

							// Get the difference between the two, we can reuse the temp
							// array that we have created before, to save some memory allocation.
							cv::absdiff(region, temp, temp);

							// Fetch the mean value from the difference, when we have
							// a perfect match, the mean value should be 0.
							cache[step] = cv::mean(temp)[0];
						}

						// Fetch error
						const double error = cache[step];

						// If the current difference is lower then the current,
						// then store the current match data.
						if (error < prevError) {
							matchIndex = n;
							matchStep = step;
							matchWidth = regionWidth;
							matchHeight = regionHeight;
							matchX = regionX;
							matchY = regionY;
							matchScale = scale;
						}
						prevError = error;

						// If this is a perfect match, then break here
						if (error == 0) {
							break;
						}
					}

					// Return when done
					if (power == 1) {

						#pragma omp atomic update
						scaleTotal += matchScale;
						break;
					}

					// Calculate the new search window
					const int stepMatched = stepPixels * matchIndex;
					const auto stepNext = (int) std::pow(2, power - 1);
					const int stepStart = (stepMatched - stepNext) / stepNext;
					searchStart = (unsigned int) (stepStart < 0 ? 0 : stepStart);
					searchEnd = (unsigned int) (stepStart + 3);
				}
			}

			// Calculate mean and total scale
			scaleMean = scaleTotal / (count - 1);
			scaleTotal = std::pow(scaleMean, (count - 1));

			// Calculate final output size
			outputWidth = (unsigned int) lround(outputWidth * scaleTotal);
			outputHeight = (unsigned int) lround(outputHeight * scaleTotal);
			outputArea = outputWidth * outputHeight;
			outputSize.width = outputWidth;
			outputSize.height = outputHeight;

			// Scale and crop images to make sure they align
			#pragma omp parallel for schedule(static)
			for (unsigned int i = 1; i < count; i++) {

				// Calculate scaled size
				const double scale = std::pow(scaleMean, i);
				const auto scaleWidth = (unsigned int) lround(outputWidth * scale);
				const auto scaleHeight = (unsigned int) lround(outputHeight * scale);
				const cv::Size scaleSize(scaleWidth, scaleHeight);

				// Calculate cropped size
				const auto cropX = (unsigned int) lround((scaleWidth - outputWidth) / 2.0);
				const auto cropY = (unsigned int) lround((scaleHeight - outputHeight) / 2.0);
				const cv::Rect cropRect(cropX, cropY, outputWidth, outputHeight);

				// Fetch image
				cv::Mat &image = images[count - i - 1];

				// Scale and crop, note that cropping just returns a reference to the
				// original data with a region of interest, so we need to copy this
				// region to the original image, in order to crop the actual data
				cv::resize(image, image, scaleSize, scale, scale, cv::INTER_AREA);
				cv::Mat cropped(image, cropRect);
				cropped.copyTo(image);
				cropped.release();
			}
		}
	}


	/**************************************************
	 * In the third step we calculate gradients and
	 * find the areas of each image that are in focus.
	 * Finally we blend these area's to create one
	 * sharp output image from these different images.
	 **************************************************/
	Image *RawProcessor::stackImages(std::vector<cv::Mat> &images)
	{
		// Create new output image
		auto *output = new Image(outputWidth, outputHeight);
		double *outputData = output->getRGB().getData();

		// Fetch image count
		const auto count = (unsigned int) images.size();

		// First merge all images into one blended background
		for (unsigned int i = 0; i < count; i++) {

			// Fetch image
			const cv::Mat &image = images[i];
			const double *imageData = (double *) image.data;

			// Copy pixels
			#pragma omp parallel for schedule(static)
			for (unsigned int n = 0; n < outputArea; n++) {
				const unsigned int index = n * 3;
				const double colorR = imageData[index + 0] / count;
				const double colorG = imageData[index + 1] / count;
				const double colorB = imageData[index + 2] / count;
				outputData[index + 0] += colorR;
				outputData[index + 1] += colorG;
				outputData[index + 2] += colorB;
			}
		}

		// Then stack the images (if we have more then one image)
		if (count > 1) {

			// Vector with gradient images
			std::vector<cv::Mat> gradients;

			// Calculate gradients
			for (unsigned int i = 0; i < count; i++) {

				// Fetch image
				const cv::Mat &image = images[i];

				// Create greyscale image
				cv::Mat greyscale(outputSize, CV_64FC1, cv::Scalar(0));
				toGreyscale(
					(double *) image.data,
					(double *) greyscale.data,
					outputArea
				);

				// Create gradients
				cv::Mat gradientX(outputSize, CV_64FC1, cv::Scalar(0));
				cv::Mat gradientY(outputSize, CV_64FC1, cv::Scalar(0));
				cv::Sobel(greyscale, gradientX, CV_64FC1, 1, 0, 3, 1, 0, cv::BORDER_DEFAULT);
				cv::Sobel(greyscale, gradientY, CV_64FC1, 0, 1, 3, 1, 0, cv::BORDER_DEFAULT);
				gradientX = cv::abs(gradientX);
				gradientY = cv::abs(gradientY);
				cv::Mat gradient(outputSize, CV_64FC1, cv::Scalar(0));
				cv::addWeighted(gradientX, 0.5, gradientY, 0.5, 0, gradient, CV_64FC1);

				// Cleanup
				greyscale.release();
				gradientX.release();
				gradientY.release();

				// Store gradient
				gradients.push_back(gradient);
			}

			// TODO: Blend images via pyramid


		}

		// Convert RGB to other channels and return
		output->convertRGB();
		return output;
	}
}
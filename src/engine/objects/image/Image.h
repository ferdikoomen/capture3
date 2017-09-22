#ifndef CAPTURE3_IMAGE_H
#define CAPTURE3_IMAGE_H


#include "ImageSize.h"
#include "ImageChannel.h"
#include "ImageMeta.h"
#include "../../../utils/ColorSpaceUtils.h"
#include "../../../utils/ColorUtils.h"
#include "../../../utils/FileUtils.h"


namespace Capture3
{

	class Image final
	{

		public:
			Image(const unsigned int width, const unsigned int height);

			virtual ~Image();

			void read(const QString &path);

			void write(const QString &path);

			void gammaCorrection();

			void inverseGammaCorrection();

			void convertRGB(const bool gammaCorrected = false);

			void convertHSB(const bool gammaCorrected = false);

			void convertXYZ(const bool gammaCorrected = false);

			void convertXYV(const bool gammaCorrected = false);

			void convertLAB(const bool gammaCorrected = false);

			ImageChannel &getRGB();

			ImageChannel &getHSB();

			ImageChannel &getXYZ();

			ImageChannel &getXYV();

			ImageChannel &getLAB();

			ImageMeta &getMeta();

			const ImageSize &getSize() const;

			const ImageChannel &getRGB() const;

			const ImageChannel &getHSB() const;

			const ImageChannel &getXYZ() const;

			const ImageChannel &getXYV() const;

			const ImageChannel &getLAB() const;

			const ImageMeta &getMeta() const;

		private:
			ImageSize size;
			ImageChannel rgb;
			ImageChannel hsb;
			ImageChannel xyz;
			ImageChannel xyv;
			ImageChannel lab;
			ImageMeta meta;
	};
}

#endif // CAPTURE3_IMAGE_H

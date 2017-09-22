#ifndef CAPTURE3_IMAGE_VIEWER_COMPONENT_H
#define CAPTURE3_IMAGE_VIEWER_COMPONENT_H


#include <QtWidgets/QWidget>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QCheckbox>


#include "ImageViewerComponentDisplay.h"
#include "ImageViewerComponentMenu.h"
#include "../panelTab/PanelTabComponent.h"
#include "../../../engine/objects/image/Image.h"
#include "../../../utils/ImagePreviewUtils.h"


namespace Capture3
{
	class ImageViewerComponent final : public PanelTabComponent
	{
		Q_OBJECT

		public:
			ImageViewerComponent();

			virtual ~ImageViewerComponent();

			void show(const Image *image);

			void reset();

		private slots:

			void showImage();

			void showColor(const int x, const int y);

		private:
			ImageViewerComponentDisplay display;
			ImageViewerComponentMenu menu;
			const Image *image;
			int cursorX;
			int cursorY;
	};
}


#endif // CAPTURE3_IMAGE_VIEWER_COMPONENT_H

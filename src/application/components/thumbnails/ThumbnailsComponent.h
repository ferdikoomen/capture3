#ifndef CAPTURE3_THUMBNAILS_COMPONENT_H
#define CAPTURE3_THUMBNAILS_COMPONENT_H


#include <QtWidgets/QWidget>


#include "ThumbnailsComponentItem.h"
#include "../panelTab/PanelTabComponent.h"
#include "../../../engine/objects/image/Image.h"


namespace Capture3
{
	class ThumbnailsComponent final : public PanelTabComponent
	{
		Q_OBJECT

		public:
			ThumbnailsComponent();

			virtual ~ThumbnailsComponent();

			void add(const Image *image);

			void select(const Image *image);

			void remove(const Image *image);

			void reset();

		signals:

			void onSelectClicked(const Image *image);

			void onRemoveClicked(const Image *image);

			void onExportClicked(const Image *image);

		private:
			std::vector<ThumbnailsComponentItem *> items;
			ThumbnailsComponentItem *current;
	};
}


#endif // CAPTURE3_THUMBNAILS_COMPONENT_H

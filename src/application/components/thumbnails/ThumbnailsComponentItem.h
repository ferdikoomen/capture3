#ifndef CAPTURE3_THUMBNAILS_COMPONENT_ITEM_H
#define CAPTURE3_THUMBNAILS_COMPONENT_ITEM_H


#include <QtWidgets/QWidget>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QStyle>
#include <QtGui/QMouseEvent>


#include "../graphic/GraphicComponent.h"
#include "../../../engine/objects/image/Image.h"
#include "../../../utils/ImagePreviewUtils.h"


namespace Capture3
{
	class ThumbnailsComponentItem final : public QFrame
	{
		Q_OBJECT

		public:
			ThumbnailsComponentItem(const Image *image);

			virtual ~ThumbnailsComponentItem();

			const Image *getImage();

			void select();

			void deselect();

		signals:

			void onSelectClicked(const Image *image);

			void onExportClicked(const Image *image);

			void onRemoveClicked(const Image *image);

		protected:
			virtual void mouseReleaseEvent(QMouseEvent *event);

		private:
			const Image *image;
			QGridLayout layout;
			QPushButton buttonExport;
			QPushButton buttonRemove;
			GraphicComponent graphic;
			QLabel label;
	};
}


#endif // CAPTURE3_THUMBNAILS_COMPONENT_ITEM_H

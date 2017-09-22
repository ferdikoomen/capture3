#include "ThumbnailsComponentItem.h"


namespace Capture3
{

	ThumbnailsComponentItem::ThumbnailsComponentItem(const Image *image) :
		QFrame(),
		image(image),
		layout(),
		buttonExport("⇪", this),
		buttonRemove("✕", this),
		graphic(image->getSize().getWidth(), image->getSize().getHeight()),
		label(image->getMeta().fileName)
	{
		// Set image
		QImage preview = generatePreviewImage(image->getRGB(), false, false);
		QImage thumb = preview.scaledToWidth(150 * devicePixelRatio(), Qt::SmoothTransformation);
		thumb.setDevicePixelRatio(window()->devicePixelRatio());
		graphic.setBackgroundImage(thumb);

		// Styling names
		buttonExport.setObjectName("export");
		buttonRemove.setObjectName("remove");

		// Add items
		layout.setSpacing(0);
		layout.setMargin(0);
		layout.setContentsMargins(0, 0, 0, 0);
		layout.setAlignment(Qt::AlignTop | Qt::AlignLeft);
		layout.addWidget(&graphic);
		layout.addWidget(&label);
		setLayout(&layout);

		// Show buttons on top
		buttonExport.raise();
		buttonRemove.raise();

		// Connect button to signal
		QObject::connect(&buttonExport, &QPushButton::clicked, this, [this]() {
			emit onExportClicked(this->image);
		});

		// Connect button to signal
		QObject::connect(&buttonRemove, &QPushButton::clicked, this, [this]() {
			emit onRemoveClicked(this->image);
		});
	}


	ThumbnailsComponentItem::~ThumbnailsComponentItem()
	{
		QObject::disconnect(&buttonExport, nullptr, nullptr, nullptr);
		QObject::disconnect(&buttonRemove, nullptr, nullptr, nullptr);

		buttonExport.deleteLater();
		buttonRemove.deleteLater();
		graphic.deleteLater();
		label.deleteLater();
		layout.deleteLater();
		image = nullptr;
	}


	const Image *ThumbnailsComponentItem::getImage()
	{
		return image;
	}


	void ThumbnailsComponentItem::mouseReleaseEvent(QMouseEvent *event)
	{
		event->accept();
		emit onSelectClicked(image);
	}


	void ThumbnailsComponentItem::select()
	{
		setObjectName("selected");
		style()->unpolish(&graphic);
		style()->polish(&graphic);
		update();
	}


	void ThumbnailsComponentItem::deselect()
	{
		setObjectName("");
		style()->unpolish(&graphic);
		style()->polish(&graphic);
		update();
	}
}
#include "ThumbnailsComponent.h"


namespace Capture3
{

	ThumbnailsComponent::ThumbnailsComponent() :
		PanelTabComponent("Thumbnails"),
		items(),
		current(nullptr)
	{
		//
	}


	ThumbnailsComponent::~ThumbnailsComponent()
	{
		reset();
	}


	void ThumbnailsComponent::add(const Image *image)
	{
		// Add thumbnail
		auto *thumb = new ThumbnailsComponentItem(image);
		QObject::connect(thumb, &ThumbnailsComponentItem::onSelectClicked, this, &ThumbnailsComponent::onSelectClicked);
		QObject::connect(thumb, &ThumbnailsComponentItem::onExportClicked, this, &ThumbnailsComponent::onExportClicked);
		QObject::connect(thumb, &ThumbnailsComponentItem::onRemoveClicked, this, &ThumbnailsComponent::onRemoveClicked);
		items.push_back(thumb);
		addWidget(thumb);
	}


	void ThumbnailsComponent::select(const Image *image)
	{
		// Deselect current thumbnail
		if (current != nullptr) {
			current->deselect();
		}

		// Find matching thumbnail and select
		for (ThumbnailsComponentItem *item : items) {
			if (item->getImage() == image) {
				current = item;
				current->select();
				break;
			}
		}
	}


	void ThumbnailsComponent::remove(const Image *image)
	{
		// Clear current item if needed
		if (current != nullptr && current->getImage() == image) {
			current = nullptr;
		}

		// Find matching thumbnail
		for (unsigned int i = 0; i < items.size(); i++) {

			if (items[i]->getImage() == image) {

				// Delete component
				ThumbnailsComponentItem *thumb = items[i];
				QObject::disconnect(thumb, nullptr, nullptr, nullptr);
				removeWidget(thumb);
				thumb->deleteLater();

				// Remove from list
				items[i] = nullptr;
				items.erase(items.begin() + i);
				break;
			}
		}
	}


	void ThumbnailsComponent::reset()
	{
		// Remove all items
		for (ThumbnailsComponentItem *item : items) {
			QObject::disconnect(item, nullptr, nullptr, nullptr);
			removeWidget(item);
			item->deleteLater();
		}

		items.clear();
		current = nullptr;
	}

}
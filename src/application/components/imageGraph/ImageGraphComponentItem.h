#ifndef CAPTURE3_IMAGE_GRAPH_COMPONENT_ITEM_H
#define CAPTURE3_IMAGE_GRAPH_COMPONENT_ITEM_H


#include <vector>
#include <QtWidgets/QWidget>


#include "../render/RenderComponent.h"


namespace Capture3
{
	class ImageGraphComponentItem final : public RenderComponent
	{
		Q_OBJECT

		public:
			ImageGraphComponentItem();

			virtual ~ImageGraphComponentItem();

			void draw(
				const std::vector<float> &positions,
				const std::vector<float> &colors,
				const unsigned int countPoints,
				const unsigned int countLines
			);
	};
}


#endif // CAPTURE3_IMAGE_GRAPH_COMPONENT_ITEM_H

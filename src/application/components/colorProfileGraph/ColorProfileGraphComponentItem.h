#ifndef CAPTURE3_COLOR_PROFILE_GRAPH_COMPONENT_ITEM_H
#define CAPTURE3_COLOR_PROFILE_GRAPH_COMPONENT_ITEM_H


#include <QtWidgets/QWidget>


#include "../render/RenderComponent.h"


namespace Capture3
{
	class ColorProfileGraphComponentItem final : public RenderComponent
	{
		Q_OBJECT

		public:
			ColorProfileGraphComponentItem();

			virtual ~ColorProfileGraphComponentItem();

			void draw(
				const std::vector<float> &positions,
				const std::vector<float> &colors,
				const unsigned int countPoints,
				const unsigned int countLines
			);
	};
}


#endif // CAPTURE3_COLOR_PROFILE_GRAPH_COMPONENT_ITEM_H

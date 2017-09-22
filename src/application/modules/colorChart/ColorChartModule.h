#ifndef CAPTURE3_COLOR_CHART_MODULE_H
#define CAPTURE3_COLOR_CHART_MODULE_H


#include "../../components/module/ModuleComponent.h"
#include "../../../engine/Engine.h"


namespace Capture3
{
	class ColorChartModule final : public ModuleComponent
	{
		Q_OBJECT

		public:
			ColorChartModule(Engine &engine);

			virtual ~ColorChartModule();

	};
}


#endif // CAPTURE3_COLOR_CHART_MODULE_H

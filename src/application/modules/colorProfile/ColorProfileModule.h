#ifndef CAPTURE3_COLOR_PROFILE_MODULE_H
#define CAPTURE3_COLOR_PROFILE_MODULE_H


#include "../../components/module/ModuleComponent.h"
#include "../../../engine/Engine.h"


namespace Capture3
{
	class ColorProfileModule final : public ModuleComponent
	{
		Q_OBJECT

		public:
			ColorProfileModule(Engine &engine);

			virtual ~ColorProfileModule();

	};
}


#endif // CAPTURE3_COLOR_PROFILE_MODULE_H

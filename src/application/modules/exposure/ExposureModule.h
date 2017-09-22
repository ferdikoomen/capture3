#ifndef CAPTURE3_EXPOSURE_MODULE_H
#define CAPTURE3_EXPOSURE_MODULE_H


#include "../../components/module/ModuleComponent.h"
#include "../../../engine/Engine.h"


namespace Capture3
{
	class ExposureModule final : public ModuleComponent
	{
		Q_OBJECT

		public:
			ExposureModule(Engine &engine);

			virtual ~ExposureModule();
	};
}


#endif // CAPTURE3_EXPOSURE_MODULE_H

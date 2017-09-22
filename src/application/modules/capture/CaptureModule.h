#ifndef CAPTURE3_CAPTURE_MODULE_H
#define CAPTURE3_CAPTURE_MODULE_H


#include "../../components/module/ModuleComponent.h"
#include "../../../engine/Engine.h"


namespace Capture3
{
	class CaptureModule final : public ModuleComponent
	{
		Q_OBJECT

		public:
			CaptureModule(Engine &engine);

			virtual ~CaptureModule();

	};
}


#endif // CAPTURE3_CAPTURE_MODULE_H

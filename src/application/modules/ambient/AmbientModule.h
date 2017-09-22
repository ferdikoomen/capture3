#ifndef CAPTURE3_AMBIENT_MODULE_H
#define CAPTURE3_AMBIENT_MODULE_H


#include "../../components/module/ModuleComponent.h"
#include "../../../engine/Engine.h"


namespace Capture3
{
	class AmbientModule final : public ModuleComponent
	{
		Q_OBJECT

		public:
			AmbientModule(Engine &engine);

			virtual ~AmbientModule();

	};
}


#endif // CAPTURE3_AMBIENT_MODULE_H

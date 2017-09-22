#ifndef CAPTURE3_EXPORT_MODULE_H
#define CAPTURE3_EXPORT_MODULE_H


#include "../../components/module/ModuleComponent.h"
#include "../../../engine/Engine.h"


namespace Capture3
{
	class ExportModule final : public ModuleComponent
	{
		Q_OBJECT

		public:
			ExportModule(Engine &engine);

			virtual ~ExportModule();

	};
}


#endif // CAPTURE3_EXPORT_MODULE_H

#ifndef CAPTURE3_ENGINE_H
#define CAPTURE3_ENGINE_H


#include "objects/project/Project.h"
#include "objects/camera/Camera.h"


namespace Capture3
{
	class Engine final
	{
		public:
			Engine();

			virtual ~Engine();

			Project &getProject();

			Camera &getCamera();

		private:
			Project project;
			Camera camera;
	};
}


#endif // CAPTURE3_ENGINE_H

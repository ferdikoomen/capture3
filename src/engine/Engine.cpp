#include "Engine.h"


namespace Capture3
{

	Engine::Engine() :
		project(),
		camera(project)
	{
		//
	}


	Engine::~Engine()
	{
		//
	}


	Project &Engine::getProject()
	{
		return project;
	}


	Camera &Engine::getCamera()
	{
		return camera;
	}

}
#include <CoreHeader.h>
#include <Core/EntryPoint.h>

#include "AppLayer.h"

namespace App
{
	class App : public Core::Application
	{
	public:
		App()
		{
			PushLayer(new AppLayer());
		}

		~App()
		{

		}
	};
}

Core::Application* Core::CreateApplication()
{
	return new App::App();
}

#include <CoreHeader.h>
#include <Core/EntryPoint.h>

class App : public Core::Application
{
public:
	App()
	{
		PushOverlay(new Core::ImGuiLayer());
	}

	~App()
	{

	}
};

Core::Application* Core::CreateApplication()
{
	return new App();
}
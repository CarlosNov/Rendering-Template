#include "Core/Core.h"
#include "Core/Window.h"
#include "Platform/Windows/WindowsWindow.h"

namespace Core
{
	Window* Window::Create(const WindowProperties& properties)
	{
		switch (CORE_OPERATIVE_SYSTEM)
		{
		case Configuration::OperatingSystem::Windows: return new WindowsWindow(properties);
		case Configuration::OperatingSystem::Unknown: CORE_LOG_ERROR("Unknown OS"); return nullptr;
		}

		CORE_LOG_ERROR("No Window available!");
		return nullptr;
	}
}
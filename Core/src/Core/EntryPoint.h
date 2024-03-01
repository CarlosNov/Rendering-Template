#pragma once

#include "Events/Event.h"
#include "Events/KeyEvent.h"

#ifdef CORE_PLATFORM_WINDOWS

extern Core::Application* Core::CreateApplication();

int main(int argc, char** argv)
{
	Core::Log::Init();

	auto app = Core::CreateApplication();
	app->Run();
	delete app;
}

#endif
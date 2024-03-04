#pragma once

#ifdef CORE_PLATFORM_WINDOWS
	#ifdef CORE_BUILD_DLL
		#define CORE_API __declspec(dllexport)
	#else
		#define CORE_API __declspec(dllimport)
	#endif
#else
	#error Core only supports Windows!
#endif

#ifdef CORE_DEBUG
	#if defined(CORE_PLATFORM_WINDOWS)
		#define CORE_DEBUGBREAK() __debugbreak()
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
	#define CORE_ENABLE_ASSERTS
#else
	#define CORE_DEBUGBREAK()
#endif

#define DEFINE_BIT(x) (1 << x)

#define CORE_EXPAND_MACRO(x) x
#define CORE_STRINGIFY_MACRO(x) #x

#define CORE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
	
struct Configuration 
{
	enum class OperatingSystem 
	{
		Windows,
		MacOS,
		Linux,
		Unknown
	};

	enum class RendererAPI 
	{
		OpenGL,
		Vulkan,
		DirectX,
		Unknown
	};

	OperatingSystem os;
	RendererAPI renderingAPI;
};

#ifdef OPERATING_SYSTEM_WINDOWS
	constexpr Configuration::OperatingSystem CORE_OPERATIVE_SYSTEM = Configuration::OperatingSystem::Windows;
#elif defined(OPERATING_SYSTEM_MACOS)
	constexpr Configuration::OperatingSystem CORE_OPERATIVE_SYSTEM = Configuration::OperatingSystem::MacOS;
#elif defined(OPERATING_SYSTEM_LINUX)
	constexpr Configuration::OperatingSystem CORE_OPERATIVE_SYSTEM = Configuration::OperatingSystem::Linux;
#else
	constexpr Configuration::OperatingSystem CORE_OPERATIVE_SYSTEM = Configuration::OperatingSystem::Unknown;
#endif

#ifdef RENDERER_API_OPENGL
	constexpr Configuration::RendererAPI CORE_RENDERING_API = Configuration::RendererAPI::OpenGL;
#elif defined(RENDERER_API_VULKAN)
	constexpr Configuration::RendererAPI CORE_OPERATIVE_SYSTEM = Configuration::RendererAPI::Vulkan;
#elif defined(RENDERER_API_DIRECTX)
	constexpr Configuration::RendererAPI CORE_OPERATIVE_SYSTEM = Configuration::RendererAPI::DirectX;
#else
	constexpr Configuration::RendererAPI CORE_OPERATIVE_SYSTEM = Configuration::RendererAPI::Unknown;
#endif

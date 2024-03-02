#pragma once

#ifdef CORE_PLATFORM_WINDOWS
#if CORE_DYNAMIC_LINK
	#ifdef CORE_BUILD_DLL
		#define CORE_API __declspec(dllexport)
	#else
		#define CORE_API __declspec(dllimport)
	#endif
#else
	#define CORE_API
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

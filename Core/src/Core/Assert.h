#pragma once

#include "Core/Core.h"
#include "Core/Log.h"

#ifdef CORE_ENABLE_ASSERTS

	#define CORE_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { CORE##type##LOG_ERROR(msg); CORE_DEBUGBREAK(); } }
	#define CORE_INTERNAL_ASSERT_WITH_MSG(type, check, ...) CORE_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
	#define CORE_INTERNAL_ASSERT_WITHOUT_MSG(type, check) CORE_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", CORE_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

	// If there is only one argument, the macro expands to a call to CORE_INTERNAL_ASSERT_WITHOUT_MSG.
	// If there are two arguments, the macro expands to a call to CORE_INTERNAL_ASSERT_WITH_MSG.
	#define CORE_INTERNAL_ASSERT_GET_MACRO(arg1, arg2, macro, ...) macro
	#define CORE_INTERNAL_ASSERT__CHECK_MACRO(...) CORE_EXPAND_MACRO(CORE_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__, CORE_INTERNAL_ASSERT_WITH_MSG, CORE_INTERNAL_ASSERT_WITHOUT_MSG))

	#define CORE_ASSERT(...) CORE_EXPAND_MACRO(CORE_INTERNAL_ASSERT__CHECK_MACRO(__VA_ARGS__)(_, __VA_ARGS__))
	#define CORE_CORE_ASSERT(...) CORE_EXPAND_MACRO(CORE_INTERNAL_ASSERT__CHECK_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__))
#else
	#define CORE_ASSERT(...)
	#define CORE_CORE_ASSERT(...)
#endif
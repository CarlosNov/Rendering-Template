#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Core
{
	class CORE_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger;  }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

//Core Log Macros
#define CORE_CORE_LOG_TRACE(...)		::Core::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CORE_CORE_LOG_INFO(...)		::Core::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CORE_CORE_LOG_WARN(...)		::Core::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CORE_CORE_LOG_ERROR(...)		::Core::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CORE_CORE_LOG_CRITICAL(...)  ::Core::Log::GetCoreLogger()->critical(__VA_ARGS__)

//Client Log Macros
#define CORE_LOG_TRACE(...)			::Core::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CORE_LOG_INFO(...)			::Core::Log::GetClientLogger()->info(__VA_ARGS__)
#define CORE_LOG_WARN(...)			::Core::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CORE_LOG_ERROR(...)			::Core::Log::GetClientLogger()->error(__VA_ARGS__)
#define CORE_LOG_CRITICAL(...)		::Core::Log::GetClientLogger()->critical(__VA_ARGS__)
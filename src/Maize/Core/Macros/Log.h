#pragma once

#include <spdlog/spdlog.h>

namespace Maize
{
    class Log
    {
    public:
        static void Initialise();

        static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        static std::shared_ptr<spdlog::logger>& GetGameLogger() { return s_GameLogger; }

    private:
        inline static std::shared_ptr<spdlog::logger> s_CoreLogger;
        inline static std::shared_ptr<spdlog::logger> s_GameLogger;
    };
} // Maize


#ifdef ENABLE_LOGGING
#define CORE_LOG_TRACE(...)    ::Maize::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CORE_LOG_INFO(...)     ::Maize::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CORE_LOG_WARN(...)     ::Maize::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CORE_LOG_ERROR(...)    ::Maize::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CORE_LOG_CRITICAL(...) ::Maize::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define GAME_LOG_TRACE(...)    ::Maize::Log::GetGameLogger()->trace(__VA_ARGS__)
#define GAME_LOG_INFO(...)     ::Maize::Log::GetGameLogger()->info(__VA_ARGS__)
#define GAME_LOG_WARN(...)     ::Maize::Log::GetGameLogger()->warn(__VA_ARGS__)
#define GAME_LOG_ERROR(...)    ::Maize::Log::GetGameLogger()->error(__VA_ARGS__)
#define GAME_LOG_CRITICAL(...) ::Maize::Log::GetGameLogger()->critical(__VA_ARGS__)
#else
	#define CORE_LOG_TRACE(...)
	#define CORE_LOG_INFO(...)
	#define CORE_LOG_WARN(...)
	#define CORE_LOG_ERROR(...)
	#define CORE_LOG_CRITICAL(...)

	#define GAME_LOG_TRACE(...)
	#define GAME_LOG_INFO(...)
	#define GAME_LOG_WARN(...)
	#define GAME_LOG_ERROR(...)
	#define GAME_LOG_CRITICAL(...)
#endif
